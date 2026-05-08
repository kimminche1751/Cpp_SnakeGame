#include "game.h"

/*
[구현해야 할 것]
- 전체 게임 루프 관리
- 입력 처리 (방향키)
- tick 기반 이동
- 충돌 검사
- 단계별 기능 구현 (1~5단계)
*/

Game::Game() : map(21,21){
    init();
};

// 초기화
void Game::init(){
    map.initialize();
};

// 게임 실행
void Game::run(){};

// 입력 처리
void Game::processInput(){};

// 상태 업데이트
void Game::update(){};

// 화면 출력 (ncurses)
void Game::render(int w, int h){
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int cell = map.getCell(j, i);
            char shape = '0';
            int color = 0;
            switch(cell){
                case 0:
                    shape = '0';
                    break;
                case 1:
                    shape = '1';
                    color = 1;
                    break;
                case 2:
                    shape = '2';
                    color = 2;
                    break;
                default:
                    shape = '?';
                    break;
            }
            attron(COLOR_PAIR(color));
            mvaddch(i, j, shape);
            attroff(COLOR_PAIR(color));
        }
    }
};

// 게임 종료 조건 체크
bool Game::isGameOver(){
    return false;
};