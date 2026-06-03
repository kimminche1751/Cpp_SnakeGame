/*
현재 상태(점수)와 미션 달성 여부를 출력, 확인하는 클래스
- B: 현재 길이 / 최대 길이
- +: 성장 아이템 획득 수
- -: 독 아이템 획득 수
- S: 위치전환 아이템 획득 수
- 게이트 사용 횟수
- 미션 달성 여부
*/

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(int stage, int mapSize, int t_len, int t_grow, int t_poison, int t_swap, int t_gate) : map(mapSize, mapSize){
    currentStage = stage;
    currentLength = 3;
    maxLength = 3;
    growthCount = 0;
    poisonCount = 0;
    swapCount = 0;
    gateCount = 0;
    targetLength = t_len;
    targetGrowth = t_grow;
    targetPoison = t_poison;
    targetSwap = t_swap;
    targetGate = t_gate;
}

// 상태 업데이트, 미션 달성 여부 확인
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
void ScoreBoard::recordSwap(){
    swapCount++;
    if(swapCount >= targetSwap){
        completeSwap = 'v';
    }
};
void ScoreBoard::recordGate(){
    gateCount++;
    if(gateCount >= targetGate){
        completeGate = 'v';
    }
};

// 미션 전체 달성 여부 판정
bool ScoreBoard::ifClear(){
    if(completeLength == 'v' && completeGrowth == 'v' && completePoison == 'v' && completeSwap == 'v' && completeGate =='v'){
        return true;
    }
    return false;
}

void ScoreBoard::print(){
    int y, x;
    y = 1;
    x = map.getWidth() + 5;
    // 현재 상태창 그리기
    WINDOW *win = subwin(stdscr, 20, 30, 1, x);
    box(win, 0, 0);
    mvwprintw(win, y, 1, "Stage: %d", currentStage); // 현재 스테이지
    y += 2;
    mvwprintw(win, y, 1, "Score Board");
    y++;
    mvwprintw(win, y, 1, "B: %d / %d", currentLength, maxLength);
    y++;
    mvwprintw(win, y, 1, "+: %d", growthCount); // 획득한 Growth아이템 수
    y++;
    mvwprintw(win, y, 1, "-: %d", poisonCount); // 획득한 Poison아이템 수
    y++;
    mvwprintw(win, y, 1, "S: %d", swapCount); // 획득한 Swap아이템 수
    y++;
    mvwprintw(win, y, 1, "G: %d", gateCount); // 게이트 이용 횟수
    y += 2;
    mvwprintw(win, y, 1, "----------------------------");
    // 미션 달성창 그리기
    y += 2;
    mvwprintw(win, y, 1, "Mission");
    y++;
    mvwprintw(win, y, 1, "B: %d (%c)", targetLength, completeLength);
    y++;
    mvwprintw(win, y, 1, "+: %d (%c)", targetGrowth, completeGrowth);
    y++;
    mvwprintw(win, y, 1, "-: %d (%c)", targetPoison, completePoison);
    y++;
    mvwprintw(win, y, 1, "S: %d (%c)", targetSwap, completeSwap);
    y++;
    mvwprintw(win, y, 1, "G: %d (%c)", targetGate, completeGate);
    
}; // ncurses로 출력
