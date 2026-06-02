/*
ncurses를 이용하여 게임의 기본 세팅과 스테이지 관리, 종료를 담당하는 파일
- ncurses를 이용하여 게임의 기본 환경 세팅
- 스테이지 관리 -> Game에 스테이지의 기본 정보를 넘겨주고 실행
- 종료 조건이 만족되면 반복문이 종료되고 프로그램 종료
*/

#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Game.h"

int main(){
    initscr(); //Curses 모드 시작
    srand((unsigned int)time(NULL)); // 난수 형성
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    
    keypad(stdscr, TRUE);

    nodelay(stdscr, TRUE);

    noecho();

    curs_set(0);

    int stage = 0;

    while(stage < 5){
        int mapSize = 31 - stage * 2;
        int spawnPos = 3;
        int t_len = 5 + stage * 2;
        int t_grow = 2 + stage;
        int t_poison = 1 + stage;
        int t_swap = 1 + stage;
        int t_gate = 1 + stage / 2;
        Game game(stage + 1, mapSize, spawnPos, t_len, t_grow, t_poison, t_swap, t_gate);
        int gameResult = game.run();
        if(gameResult == 0){
            break;
        }
        else if(gameResult == 2){
            continue;
        }
        stage++;
    }
    
    endwin();
    return 0;
}