#include <ncurses.h>
#include "Snake.h"

// 방향키 입력 처리
void processInput(Snake& snake) {

    int ch = getch();

    switch (ch) {

        case KEY_UP:
            snake.setDirection(UP);
            break;

        case KEY_DOWN:
            snake.setDirection(DOWN);
            break;

        case KEY_LEFT:
            snake.setDirection(LEFT);
            break;

        case KEY_RIGHT:
            snake.setDirection(RIGHT);
            break;
    }
}