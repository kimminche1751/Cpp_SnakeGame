#ifndef GATE_H
#define GATE_H

#include <vector>
#include "map.h"
#include "Snake.h"

class Gate {
private:
    Position gateA; // Snake의 Position 기준인 (y, x)로 저장됨
    Position gateB;

public:
    Gate();
    
    // 1. 게이트 생성 함수
    void generate(Map& map);
    
    // 2. 텔레포트 및 진출 방향 결정 함수
    Position teleport(Position currentHead, Direction& currentDirection, Map& map);

    // 3. 뱀이 게이트를 통과 중인지 확인하는 함수 (소멸 방지용)
    bool isSnakePassing(Map& map, Snake& snake);
};

#endif
