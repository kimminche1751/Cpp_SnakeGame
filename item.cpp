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

/*
checkCollision 함수 구현 과정에서 이해가 되지 않는 부분이 있어 함수를 2가지로 구현을 진행하였음.

1번으로 구현하는 경우 아이템 충돌 이후 아이템의 효과 처리 및 아이템 위치정보와 시간정보 삭제 과정을
따로 구현해야하는 문제가 있음

2번으로 구현하는 경우 기존의 추상 자료형에 맞지 않는 부분이 있어 수정이 필요함
*/

//구현 1 : 뱀 머리의 위치를 받아 아이템과 충돌 시 해당하는 아이템 반환
int Item::checkCollision(Position head){
    int y = head.first;
    int x = head.second;
    for(int i = 0; i != growthItems.size(); i++){ //for문으로 위치 정보 컨테이너를 순회하며
        if(head == growthItems[i]){//머리의 위치와 growth 아이템의 위치가 같으면
            return 5; //5(growth)를 반환
        }
    }
    for(int i = 0; i != poisonItems.size(); i++){
        if(head == poisonItems[i]){
            return 6;
        }
    }
}

//구현 2 : Snake 객체를 받아 충돌 시 아이템
/*int Item::checkCollision(Snake &S){

    int y = S.getHead().first;
    int x = S.getHead().second;
    for(int i = 0; i != growthItems.size(); i++){ //for문으로 위치 정보 컨테이너를 순회하며
        if(head == growthItems[i]){//머리의 위치와 growth 아이템의 위치가 같으면
            S.grow(); //뱀의 길이를 1 증가시키고
            growthItems.erase(growthItems.begin() + i); //소멸된 아이템 위치정보 제거
            growthItemTime.erase(growthItemTime.begin() + i); //소멸된 아이템 시간정보 제거
            i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
        }
    }
    for(int i = 0; i != poisonItems.size(); i++){
        if(head == poisonItems[i]){
            S.shrink();
            poisonItems.erase(poisonItems.begin() + i);
            poisonItemTime.erase(poisonItemTime.begin() + i);
            i--;
        }
    }
}*/
