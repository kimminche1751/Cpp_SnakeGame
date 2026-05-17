#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Snake.h"
//#include "Item.h"
#include "Gate.h"
#include <ncurses.h>
#include <unistd.h>

class Game {
private:
    Map map;
    Snake snake;
    //Item item;
    Gate gate;
    // ScoreBoard score;
    bool gameOver;
    bool gateExist;

public:
    /*
    [구현해야 할 것]
    - 전체 게임 루프 관리
    - 입력 처리 (방향키)
    - tick 기반 이동
    - 충돌 검사
    - 단계별 기능 구현 (1~5단계)
    */

    Game();

    // 초기화
    void init();

    // 게임 실행
    void run();

    // 입력 처리
    void processInput();

    // 상태 업데이트
    void update();

    // 화면 출력 (ncurses)
    void render(int w, int h);

    // 게임 종료 조건 체크
    bool isGameOver();
};

#endif