#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <cstdlib>
#include "Map.h"
using namespace std;

class Item {
private:
    vector<Position> growthItems; //growth 아이템의 위치 목록
    vector<Position> poisonItems; //poison 아이템의 위치 목록
    vector<unsigned int> growthItemTime;//growth 아이템의 시간 목록
    vector<unsigned int> poisonItemTime;//poison 아이템의 시간 목록

public:
    /*
    [구현해야 할 것 - Rule #2]
    - Growth: 길이 +1
    - Poison: 길이 -1 (길이 3 미만이면 실패)
    - 아이템은 랜덤 위치 생성
    - 일정 시간 후 사라짐
    - 최대 3개 유지
    */

    void spawnGrowth(Map& map);
    void spawnPoison(Map& map);

    // 아이템 삭제 (시간 경과)
    void removeOldItems(Map& map);

    // Snake와 충돌 체크
    int checkCollision(Position head);
};

#endif