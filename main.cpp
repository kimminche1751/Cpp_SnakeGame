#include <ncurses.h>
#include "Game.h"

int main(){
    initscr(); //Curses 모드 시작
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    
    keypad(stdscr, TRUE);

    // getch non-blocking
    nodelay(stdscr, TRUE);

    noecho();

    curs_set(0);

    Game game;

    game.run();

    endwin();
    return 0;
}