#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "item.h"
#include "map.h"
#include "Snake.h"

//#include "snake.h" //snake.h 파일이 완성되면 적용될 예정

#define OLDTIME 100 //item 지속시간

void Item::spawnGrowth(Map& map){ //Growth item spawning
    if(growthItems.size() + poisonItems.size() <= 3)//필드 내 동시에 존재 가능한 아이템은 3개로 제한되어 있으므로
    {
        int x, y;
        do{ 
            srand((unsigned int)time(NULL)); //time값으로 시드값 초기화
            //X, Y 랜덤 좌표 생성
            x = rand() % map.getWidth();
            y = rand() % map.getHeight();
        }
        while(!map.isInside(x, y) || !map.isEmpty(x, y));//올바른 좌표가 나올때까지 좌표 생성 반복

        map.setCell(x, y, 5); //맵의 해당 위치에 아이템 배치
        growthItems.push_back({y, x}); //growthItem 위치를 벡터에 추가
        growthItemTime.push_back((unsigned int)time(NULL)); //시간 정보 컨테이너에 생성 시간을 push
        return;
    }
}

void Item::spawnPoison(Map& map){
    if(growthItems.size() + poisonItems.size() <= 3)//필드 내 동시에 존재 가능한 아이템은 3개로 제한되어 있으므로
    {
        int x, y;
        do{ 
            srand((unsigned int)time(NULL)); //time값으로 시드값 초기화
            //X, Y 랜덤 좌표 생성
            x = rand() % map.getWidth();
            y = rand() % map.getHeight();
        }
        while(!map.isInside(x, y) || !map.isEmpty(x, y));//올바른 좌표가 나올때까지 좌표 생성 반복

        map.setCell(x, y, 6); //맵의 해당 위치에 아이템 배치
        poisonItems.push_back({y, x}); //growthItem 위치를 벡터에 추가
        poisonItemTime.push_back((unsigned int)time(NULL)); //시간 정보 컨테이너에 생성 시간을 push
        return;
    }
}
void Item::removeOldItems(Map& map){
    unsigned int now = (unsigned int)time(NULL);
    for(int i = 0; i != growthItems.size(); i++){ //for문으로 시간 정보 컨테이너를 순회하며
        if(now >= growthItemTime[i] + 5){ //생성 이후 5초가 지났는지를 체크(시간은 임의로 결정했으며, 이후 논의를 통해 )
            map.setCell(growthItems[i].first, growthItems[i].second, 0);//해당하는 아이템의 위치정보를 참조해 map에 접근해 아이템을 빈 공간으로 변경
            growthItems.erase(growthItems.begin() + i); //시간이 지난 아이템 위치정보 제거
            growthItemTime.erase(growthItemTime.begin() + i); //시간이 지난 아이템 시간정보 제거
            i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
        }
    }
    for(int i = 0; i != poisonItems.size(); i++){
        if(now >= poisonItemTime[i] + 5){
            map.setCell(growthItems[i].first, growthItems[i].second, 0);
            poisonItems.erase(poisonItems.begin() + i);
            poisonItemTime.erase(poisonItemTime.begin() + i);
            i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
        }
    }
}

// 뱀 머리의 위치를 받아 아이템과 충돌 시 해당하는 아이템 정보를 제거하고 해당하는 종류에 따라 숫자 반환
int Item::checkCollision(Position head){
    int y = head.first;
    int x = head.second;
    for(int i = 0; i != growthItems.size(); i++){ //for문으로 위치 정보 컨테이너를 순회하며
        if(head == growthItems[i]){//머리의 위치와 growth 아이템의 위치가 같으면
            growthItems.erase(growthItems.begin() + i); //충돌한 아이템 위치정보 제거
            growthItemTime.erase(growthItemTime.begin() + i); //중돌한 아이템 시간정보 제거
            i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
            return 5; //5(growth)를 반환
        }
    }
    for(int i = 0; i != poisonItems.size(); i++){
        if(head == poisonItems[i]){
            poisonItems.erase(poisonItems.begin() + i);
            poisonItemTime.erase(poisonItemTime.begin() + i);
            return 6; //poison은 6 반환
        }
    }
}
