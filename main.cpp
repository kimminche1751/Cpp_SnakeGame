#include <ncurses.h>
#include "game.h"

int main(){
    initscr(); //Curses 모드 시작
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    
    Game game;

    while(1){
        erase();
        game.render(21, 21);

        //q키 누르면 종료
        int ch = getch();
        if(ch == 'q')
            break;
    }

    endwin();
    return 0;
}