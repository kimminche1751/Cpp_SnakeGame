#include <iostream>
#include <cstdlib>
#include <vector>
#include "Item.h"
#include "Map.h"
#include "Snake.h"

void Item::spawnGrowth(Map& map){ //Growth item spawning
    if(growthItems.size() + poisonItems.size() < 3)//필드 내 동시에 존재 가능한 아이템은 3개로 제한되어 있으므로
    {
        int x, y; //좌표 생성 과정에서 값을 변경해야 하므로 const 선언X
        do{ 
            //X, Y 랜덤 좌표 생성
            x = rand() % map.getWidth();
            y = rand() % map.getHeight();
        }
        while(!map.isInside(x, y) || !map.isEmpty(x, y));//올바른 좌표가 나올때까지 좌표 생성 반복

        map.setCell(x, y, 5); //맵의 해당 위치에 아이템 배치
        growthItems.push_back({y, x}); //growthItem 위치를 벡터에 추가
        growthItemTime.push_back(0); //시간 정보 컨테이너에 0을 push
        return;
    }
}

void Item::spawnPoison(Map& map){
    if(growthItems.size() + poisonItems.size() < 3)//필드 내 동시에 존재 가능한 아이템은 3개로 제한되어 있으므로 - 해당 부분 작동에 문제가 있는지 파악 필요
    {
        int x, y; //좌표 생성 과정에서 값을 변경해야 하므로 const 선언X
        do{ 
            //X, Y 랜덤 좌표 생성
            x = rand() % map.getWidth();
            y = rand() % map.getHeight();
        }
        while(!map.isInside(x, y) || !map.isEmpty(x, y));//올바른 좌표가 나올때까지 좌표 생성 반복

        map.setCell(x, y, 6); //맵의 해당 위치에 아이템 배치
        poisonItems.push_back({y, x}); //growthItem 위치를 벡터에 추가
        poisonItemTime.push_back(0); //시간 정보 컨테이너에 0을 push
        return;
    }
}
void Item::removeOldItems(Map& map){//본 함수가 매 틱마다 실시됨
    for(int i = 0; i != growthItems.size(); i++){ //for문으로 시간 정보 컨테이너를 순회하며
        growthItemTime[i]++; //매 틱마다 아이템의 시간을 1틱씩 추가
        if(growthItemTime[i] >= 50){ //생성 이후 5초가 지났는지를 체크(수정사항 : 틱 기반으로 변경)
            map.setCell(growthItems[i].second, growthItems[i].first, 0);//해당하는 아이템의 위치정보를 참조해 map에 접근해 아이템을 빈 공간으로 변경
            growthItems.erase(growthItems.begin() + i); //시간이 지난 아이템 위치정보 제거
            growthItemTime.erase(growthItemTime.begin() + i); //시간이 지난 아이템 시간정보 제거
            i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
        }
    }
    for(int i = 0; i != poisonItems.size(); i++){
        poisonItemTime[i]++;
        if(poisonItemTime[i] >= 50){
            map.setCell(poisonItems[i].second, poisonItems[i].first, 0);
            poisonItems.erase(poisonItems.begin() + i);
            poisonItemTime.erase(poisonItemTime.begin() + i);
            i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
        }
    }
}

// 뱀 머리의 위치를 받아 아이템과 충돌 시 해당하는 아이템 및 정보를 제거하고 해당하는 종류에 따라 숫자 반환
int Item::checkCollision(Position head, Map& map){ //수정사항 : 맵 상의 아이템 제거를 위해 Map 객체 참조 map을 파라미터로 추가
    const int y = head.first;
    const int x = head.second;
    for(int i = 0; i != growthItems.size(); i++){ //for문으로 위치 정보 컨테이너를 순회하며
        if(head == growthItems[i]){//머리의 위치와 growth 아이템의 위치가 같으면
            map.setCell(x, y, 0); //수정사항 : 해당 위치에 있던 아이템을 맵에서 제거하여 아이템 3개이상 생성 오류 및 아이템 접촉 후 미제거 오류 해결
            growthItems.erase(growthItems.begin() + i); //충돌한 아이템 위치정보 제거
            growthItemTime.erase(growthItemTime.begin() + i); //중돌한 아이템 시간정보 제거
            i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
            return 5; //5(growth)를 반환
        }
    }
    for(int i = 0; i != poisonItems.size(); i++){
        if(head == poisonItems[i]){
            map.setCell(x, y, 0); //수정사항 : 해당 위치에 있던 아이템을 맵에서 제거하여 아이템 3개이상 생성 오류 및 아이템 접촉 후 미제거 오류 해결
            poisonItems.erase(poisonItems.begin() + i);
            poisonItemTime.erase(poisonItemTime.begin() + i);
            return 6; //poison은 6 반환
        }
    }
    return 0;
}

//checkCollision 함수 수정 : 함수 내부 지역변수 x, y를 const로 선언, 내부에서 map.setCell 호출 시 파라미터를 각각  x, y 로 변경
//Position 구조체 타입 파라미터 head는 call by value이므로 별도로 const 선언은 하지 않았음.
