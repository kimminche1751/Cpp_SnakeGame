/*
Item.cpp : 아이템 class의 메서드 구현

Item 클래스 : 아이템 생성 및 삭제, 아이템 접촉에 관한 처리

생성자, 소멸자는 Compiler가 정의하는 Default 생성자, 소멸자 사용(멤버 변수에 값 초기화 불필요)
복사 생성자, 할당 연산자 불필요(프로그램 실행 간 1개의 인스턴스만 사용)

---private member functions---
spawnItem : 아이템 생성을 처리하는 내부 함수
deleteItem : 아이템 삭제를 처리하는 내부 함수

---public member functions---
spawn-계열 함수 : 내부적으로 private 함수인 Item::spawnItem() 호출
spawnGrowth : Growth 아이템을 생성하는 public 함수
spawnPoison : Poison 아이템을 생성하는 public 함수
spawnSwap : Swap 아이템을 생성하는 public 함수 (추가 아이템)
removeOldItems, checkCollision 함수 : private 함수인 Item::deleteItem() 호출
removeOldItems : 매 틱마다 호출되어, 시간정보를 1씩 늘려가며 시간정보가 50틱 이상인 아이템을 제거하는 public 함수
checkCollision : 매 틱마다 호출되어, 스네이크의 head 위치와 아이템 위치를 비교해 동일한 위치에 있는 아이템 종류를 반환. (반환값에 따라 snake의 상태 변화 메서드들을 호출)

*/

#include <iostream>
#include <cstdlib> //rand()함수 사용
#include <vector> //벡터 자료구조의 메서드 사용
#include "Item.h" //아이템 헤더 파일
#include "Map.h" //Map 객체 및 객체의 메서드 사용

//item Spawning methods
void Item::spawnItem(Map& map, const int itemType){ //itemType값은 내부에서 변경되지 않으므로 const 선언
    if(itemTypes.size()< 3)//아이템 개수제한 조건(3개) 판정
    {
        int x, y; //좌표 생성을 1회 이상 하므로 const 선언하지 않음
        //X, Y 랜덤 좌표 생성
        do{
            x = rand() % map.getWidth();
            y = rand() % map.getHeight();
        }
        while(!map.isInside(x, y) || !map.isEmpty(x, y));//올바른 좌표 생성시까지 반복

        map.setCell(x, y, itemType); //맵의 해당 위치에 아이템 배치
        itemTypes.push_back(itemType);
        itemPositions.push_back({y, x}); //아이템 위치정보 추가
        itemTimes.push_back(0); //시간 컨테이너에 0 추가
        return;
    }
}

void Item::spawnGrowth(Map& map){ //Growth item spawning
    spawnItem(map, GROWTH_ITEM); 
}

void Item::spawnPoison(Map& map){ //Poison item spawning
    spawnItem(map, POISON_ITEM);
}

void Item::spawnSwap(Map& map){ //Swap item spawning
    spawnItem(map, SWAP_ITEM);
}

//item delete methods
void Item::deleteItem(Map& map, int& i){ //i와 map에 변화가 있으므로 const로 선언하지 않음
    map.setCell(itemPositions[i].second, itemPositions[i].first, 0);//해당 아이템을 빈 공간으로 변경해 삭제
    itemPositions.erase(itemPositions.begin() + i); //아이템 위치정보 제거
    itemTimes.erase(itemTimes.begin() + i); //아이템 시간정보 제거
    itemTypes.erase(itemTypes.begin() + i); //아이템 종류정보 제거
    i--;//erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
}

void Item::removeOldItems(Map& map){ //50틱이 지난 아이템 삭제
    for(int i = 0; i != itemTypes.size(); i++){
        itemTimes[i]++; //함수 실행 시마다(매 틱마다) 아이템의 시간을 1틱씩 추가
        if(itemTimes[i] >= 50){ //생성 이후 50틱이 지나면 아이템 삭제
            deleteItem(map, i);//아이템 삭제처리
        }
    }
}

//collision check(between snake and items)
int Item::checkCollision(const Position head, Map& map){ //뱀 머리와 아이템 충돌여부 판정
    for(int i = 0; i != itemTypes.size(); i++){
        if(head == itemPositions[i]){//머리 위치에 아이템 존재여부 판정
            const int item = itemTypes[i]; //item은 한번 결정된 값 그대로 반환되어 const 선언
            deleteItem(map, i); //충돌한 아이템을 맵에서 삭제
            return item; //해당 위치에 있던 아이템 종류 반환
        }
    }
    return 0; //뱀의 머리와 만난 아이템이 없다면 0 반환
}