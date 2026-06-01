#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Snake.h"
#include "Item.h"
#include "Gate.h"
#include "Map.h"
#include <ncurses.h>

class ScoreBoard {
private:
    int currentStage;
    int currentLength;
    int maxLength;
    int growthCount, poisonCount, swapCount, gateCount;
    int targetLength, targetGrowth, targetPoison, targetSwap, targetGate;
    char completeLength{' '}, completeGrowth{' '}, completePoison{' '}, completeSwap{' '}, completeGate{' '};
    Map map;

public:
    /*
    [구현해야 할 것 - Rule #6]
    - 현재 길이 / 최대 길이
    - 성장 아이템 획득 수
    - 독 아이템 획득 수
    - 게이트 사용 횟수
    - 미션 달성 여부
    */
    ScoreBoard(int stage, int mapSize, int t_len, int t_grow, int t_poison, int t_swap, int t_gate);

    void updateLength(int len);

    void recordGrowth();

    void recordPoison();
    
    void recordSwap();

    void recordGate();

    bool ifClear();

    void print(); // ncurses로 출력
};
#endif
