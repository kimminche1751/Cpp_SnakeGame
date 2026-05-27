#include <iostream>
#include <cstdlib>
#include <vector>
#include "Item.h"
#include "Map.h"
#include "Snake.h"

//item Spawning methods
void Item::spawnItem(Map& map, const int itemType){ //itemType값은 변경되지 않으므로 상수로 처리
    if(itemTypes.size()< 3)//아이템 개수제한 조건(3개) 판정
    {
        int x, y; //좌표 생성 과정에서 값을 변경해야 하므로 const 선언X
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

//아래 3개 메서드는 처음에 정해둔 인터페이스 유지를 위해 남겨둔 것으로, 실제 동작은 spawnItem에서 이뤄짐
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

void Item::removeOldItems(Map& map){ //매 틱마다 함수를 실행시켜 시간이 지난 아이템을 제거
    for(int i = 0; i != itemTypes.size(); i++){
        itemTimes[i]++; //매 틱마다 아이템의 시간을 1틱씩 추가
        if(itemTimes[i] >= 50){ //생성 이후 50틱이 지나면 아이템 삭제
            deleteItem(map, i);//아이템 삭제처리
        }
    }
}

//collision check(between snake and items)
int Item::checkCollision(const Position head, Map& map){ //뱀 머리와 아이템 충돌여부를 판정하여 아이템이 있는 경우 해당 아이템을 반환하고 삭제처리
    for(int i = 0; i != itemTypes.size(); i++){
        if(head == itemPositions[i]){//머리의 위치에 아이템이 있다면
            const int item = itemTypes[i]; //item은 한번 결정되면 그대로 반환되기 때문에 const로 선언
            deleteItem(map, i); //해당 아이템 삭제처리
            return item; //해당 위치에 있던 아이템 반환
        }
    }
    return 0; //뱀의 머리와 만난 아이템이 없다면 0 반환
}