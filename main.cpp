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