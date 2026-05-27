#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <cstdlib>
#include "Map.h"
#include "snake.h"
using namespace std;

class Item {
private:
    //item information containers
    vector<int> itemTypes; //아이템 종류 목록
    vector<Position> itemPositions; //아이템의 위치 목록
    vector<unsigned int> itemTimes; //아이템의 시간 목록

    //item 내부 처리 함수
    void spawnItem(Map& map, int type); //아이템 생성 처리
    void deleteItem(Map& map, int& i); //아이템 삭제 처리

public:
    /*
    [구현해야 할 것 - Rule #2]
    - Growth: 길이 +1
    - Poison: 길이 -1 (길이 3 미만이면 실패)
    - 아이템은 랜덤 위치 생성
    - 일정 시간 후 사라짐
    - 최대 3개 유지
    - 추가 아이템 구현
    */

    //item spawning methods
    void spawnGrowth(Map& map);
    void spawnPoison(Map& map);
    void spawnSwap(Map& map);

    // 아이템 삭제 (시간 경과)
    void removeOldItems(Map& map);

    // Snake와 충돌 체크
    int checkCollision(const Position head, Map& map);

};

#endif