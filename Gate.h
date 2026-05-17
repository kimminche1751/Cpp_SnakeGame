#ifndef GATE_H
#define GATE_H

#include <vector>
#include "Map.h"   // 팀원 파일명에 맞춤
#include "Snake.h"

class Gate {
private:
    Position gateA; // Snake 좌표계 (y, x) 기준 저장
    Position gateB;

public:
    Gate();
    
    // 1. 게이트 생성: 일반 벽 중 랜덤하게 2개를 골라 게이트(7)로 변경
    void generate(Map& map);
    
    // 2. 텔레포트: 출구 좌표를 반환하고 뱀의 진행 방향을 규칙에 맞게 수정
    Position teleport(Position currentHead, Direction currentDirection, Map& map);

    // 3. 통과 확인: 뱀의 몸통이 게이트 위에 있는지 확인 (소멸 방지용)
    bool isSnakePassing(Map& map, Snake& snake);

    // 4. 게이트 제거: 생성된 게이트를 다시 일반 벽(1)으로 되돌림
    void remove(Map& map);
};

#endif