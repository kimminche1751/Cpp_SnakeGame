#include "ScoreBoard.h"

/*
[구현해야 할 것 - Rule #6]
- 현재 길이 / 최대 길이
- 성장 아이템 획득 수
- 독 아이템 획득 수
- 게이트 사용 횟수
- 미션 달성 여부
*/
ScoreBoard::ScoreBoard(int stage, int mapSize, int t_len, int t_grow, int t_poison, int t_gate) : map(mapSize, mapSize){
    currentStage = stage;
    currentLength = 3;
    maxLength = 3;
    growthCount = 0;
    poisonCount = 0;
    gateCount = 0;
    targetLength = t_len;
    targetGrowth = t_grow;
    targetPoison = t_poison;
    targetGate = t_gate;
}

void ScoreBoard::updateLength(int len){
    currentLength = len;
    if(len > maxLength){
        maxLength = len;
    }
    if(maxLength >= targetLength){
        completeLength = 'v';
    }
}
void ScoreBoard::recordGrowth(){
    growthCount++;
    if(growthCount >= targetGrowth){
        completeGrowth = 'v';
    }
}
void ScoreBoard::recordPoison(){
    poisonCount++;
    if(poisonCount >= targetPoison){
        completePoison = 'v';
    }
};
void ScoreBoard::recordGate(){
    gateCount++;
    if(gateCount >= targetGate){
        completeGate = 'v';
    }
};

bool ScoreBoard::ifClear(){
    if(completeLength == 'v' && completeGrowth == 'v' && completePoison == 'v' && completeGate =='v'){
        return true;
    }
    return false;
}

void ScoreBoard::print(){
    int y, x;
    y = 1;
    x = map.getWidth() + 5;
    WINDOW *win = subwin(stdscr, 20, 30, 1, x);
    box(win, 0, 0);
    mvwprintw(win, y, 1, "Stage: %d", currentStage);
    y += 2;
    mvwprintw(win, y, 1, "Score Board");
    y++;
    mvwprintw(win, y, 1, "B: %d / %d", currentLength, maxLength);
    y++;
    mvwprintw(win, y, 1, "+: %d", growthCount);
    y++;
    mvwprintw(win, y, 1, "-: %d", poisonCount);
    y++;
    mvwprintw(win, y, 1, "G: %d", gateCount);
    y += 2;
    mvwprintw(win, y, 1, "----------------------------");
    y += 2;
    mvwprintw(win, y, 1, "Mission");
    y++;
    mvwprintw(win, y, 1, "B: %d (%c)", targetLength, completeLength);
    y++;
    mvwprintw(win, y, 1, "+: %d (%c)", targetGrowth, completeGrowth);
    y++;
    mvwprintw(win, y, 1, "-: %d (%c)", targetPoison, completePoison);
    y++;
    mvwprintw(win, y, 1, "G: %d (%c)", targetGate, completeGate);
    
}; // ncurses로 출력
