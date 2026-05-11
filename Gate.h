#ifndef GATE_H
#define GATE_H

#include <vector>
#include "map.h"   
#include "Snake.h"

class Gate {
private:
    Position gateA; // Position은 Snake.h에 정의된 (y, x) 형식을 따름 
    Position gateB;

public:
    Gate();

    //Gate 생성 
    void generate(Map& map);

    //이동 처리 및 방향 전환 
    Position teleport(Position currentHead, Direction& currentDirection, Map& map);
};

#endif
