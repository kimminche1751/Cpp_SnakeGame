/*
게임의 전체 동작을 관리하는 클래스
- 전체 게임 루프 관리
- 입력 처리 (방향키)
- tick 기반 이동
- 충돌 검사
- 게임오버 / 클리어 검사
- 맵 그리기
*/

#include "Game.h"

Game::Game(int stage, int mapSize, int spawnPos, int t_len, int t_grow, int t_poison, int t_swap, int t_gate) : map(mapSize, mapSize), snake({spawnPos, spawnPos}), score(stage, mapSize, t_len, t_grow, t_poison, t_swap, t_gate), gameOver(false), gateExist(false), itemTime(0){
    this->stage = stage;
    init(stage, mapSize);
};

// 초기화
void Game::init(int stage, int mapSize){
    map.initialize();
    map.makeStage(stage, mapSize);
};

// 게임 실행
int Game::run(){
    int gateTime = 0;
    // 게임오버 조건을 만족하거나 클리어 조건을 만족할 때까지 반복
    while(!isGameOver() && !score.ifClear()){
        // 5초마다 게이트 위치 변경 (통과중에는 변경 X)
        if(gateTime >= 50){
            if(!gate.isSnakePassing(map, snake)){
                gate.remove(map);
                gateExist = false;
                gateTime = 0;
            }
        }
        processInput();
        score.updateLength(snake.getBody().size());
        update();
        erase();
        render(map.getWidth(), map.getHeight());
        score.print();
        refresh();
        usleep(100000);
        gateTime++;
    }
    nodelay(stdscr, FALSE);
    // 게임오버시
    if(gameOver == true){
        printGameOver(10, 30); // 게임오버 창 출력
        char key;
        while(true){
            key = getch();
            if(key == 'R' || key == 'r'){
                nodelay(stdscr, TRUE);
                return 2; // 'R'키를 누르면 스테이지 재시작
            }
            else if(key == 'Q' || key == 'q'){
                return 0; // 'Q'키를 누르면 게임 종료
            }
        }
    }
    // 스테이지 클리어 시
    else{
        if(stage < 5){
            printStageClear(10, 30); // 스테이지 클리어 창 출력
            getch();
            nodelay(stdscr, TRUE);
            return 1; //다음 스테이지로
        }
        // 스테이지 5 클리어 시
        else{
            printGameClear(10, 30); // 게임 클리어 창 출력
            getch();
            nodelay(stdscr, TRUE);
            return 1;
        }
    }
};

// 입력 처리
void Game::processInput(){

    int ch;
    int last_ch = ERR;

    while((ch = getch()) != ERR){
        last_ch = ch;
    }

    if(last_ch == ERR){
        return;
    }

    switch (last_ch) {

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
};

// 상태 업데이트
void Game::update(){
    // 게이트 생성
    if(!gateExist){
        gate.generate(map);
        gateExist = true;
    }

    // 아이템 제거
        item.removeOldItems(map);

    // 아이템 생성(1초 주기)
    if(itemTime >= 10){
        // 아이템 생성
        int ram = rand() % 100;
        if(ram < 50){
            item.spawnGrowth(map);
        }
        else if(ram <75){
            item.spawnPoison(map);
        }
        else{
            item.spawnSwap(map);
        }
        itemTime = 0;
    }
    itemTime++;

    // 스네이크 이동
    snake.move();
    Position head = snake.getHead();

    int y = head.first;
    int x = head.second;


    if(!map.isInside(x, y)){
        gameOver = true;
        return;
    }

    int cell = map.getCell(x, y);

    // 충돌감지
    // 벽 충돌
    if(cell == WALL || cell == IMMUNE_WALL){
        gameOver = true;
        return;
    }

    // 게이트 충돌
    if(cell == GATE){
        Position newPos = gate.teleport(head, snake.getDirection(), map, snake);
        snake.teleportHead(newPos);
        score.recordGate();
    }

    // 아이템 충돌
    int itemCollision = item.checkCollision(head, map);
    if(itemCollision == GROWTH_ITEM){
        snake.grow();
        score.recordGrowth();
    }

    if(itemCollision == POISON_ITEM){
        snake.shrink();
        score.recordPoison();
    }
    
    if(itemCollision == SWAP_ITEM){
        snake.swapTailAndHead();
        score.recordSwap();
    }

    // 자기 몸 충돌
    if(snake.checkSelfCollision()){
        gameOver = true;
        return;
    }
};

// 화면 출력 (ncurses)
void Game::render(int w, int h){
    //맵 그리기
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int cell = map.getCell(j, i);
            chtype shape = ' ';
            int color = 0;
            switch(cell){
                case 0:
                    shape = ' ';
                    break;
                case 1:
                    shape = ACS_CKBOARD;
                    color = 1;
                    break;
                case 2:
                    shape = ACS_CKBOARD;
                    color = 2;
                    break;
                case 3:
                    shape = ACS_BLOCK;
                    color = 3;
                    break;
                case 4:
                    shape = ACS_BLOCK;
                    color = 4;
                    break;
                case 5:
                    shape = 'O';
                    color = 5;
                    break;
                case 6:
                    shape = 'O';
                    color = 6;
                    break;
                case 7:
                    shape = 'O';
                    color = 7;
                    break;
                case 8:
                    shape = ACS_DIAMOND;
                    color = 7;
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

    //Snake 그리기
    std::vector<Position> body = snake.getBody();
    for(int i = 0; i < body.size(); i++){
        int y = body[i].first;
        int x = body[i].second;

        chtype shape = ' ';
        int color = 3;

        if(i == 0){
            shape = ACS_BLOCK;
            color = 3;
        }
        else{
            shape = ACS_BLOCK;
            color = 4;
        }
        
        attron(COLOR_PAIR(color));
        mvaddch(y, x, shape);
        attroff(COLOR_PAIR(color));
    }

};

// 게임 종료 조건 체크
bool Game::isGameOver(){
//snake.isGameover() &  game.gameOver() 연동
    if (snake.isGameOver()) gameOver = true;
    
    return gameOver;
};

// 게임오버 화면 출력
void Game::printGameOver(int h, int w){
    int scr_h, scr_w;
    getmaxyx(stdscr, scr_h, scr_w);
    int start_y = (scr_h - h) / 2;
    int start_x = (scr_w - w) / 2;
    WINDOW *popup_win = newwin(h, w, start_y, start_x);
    box(popup_win, 0, 0);
    string msg1 = "Game Over!";
    string msg2 = "Press 'R' to retry.";
    string msg3 = "Press 'Q' to quit.";
    mvwprintw(popup_win, h / 2 - 1 , (w - msg1.length()) / 2, "%s", msg1.c_str());
    mvwprintw(popup_win, h / 2 , (w - msg2.length()) / 2, "%s", msg2.c_str());
    mvwprintw(popup_win, h / 2 + 1 , (w - msg3.length()) / 2, "%s", msg3.c_str());
    wrefresh(popup_win);
}

// 스테이지 클리어 화면 출력
void Game::printStageClear(int h, int w){
    int scr_h, scr_w;
    getmaxyx(stdscr, scr_h, scr_w);
    int start_y = (scr_h - h) / 2;
    int start_x = (scr_w - w) / 2;
    WINDOW *popup_win = newwin(h, w, start_y, start_x);
    box(popup_win, 0, 0);
    string msg1 = "Stage Clear!";
    string msg2 = "Press any key to continue.";
    mvwprintw(popup_win, h / 2 - 1 , (w - msg1.length()) / 2, "%s", msg1.c_str());
    mvwprintw(popup_win, h / 2 , (w - msg2.length()) / 2, "%s", msg2.c_str());
    wrefresh(popup_win);
}

// 게임 클리어 화면 출력
void Game::printGameClear(int h, int w){
    int scr_h, scr_w;
    getmaxyx(stdscr, scr_h, scr_w);
    int start_y = (scr_h - h) / 2;
    int start_x = (scr_w - w) / 2;
    WINDOW *popup_win = newwin(h, w, start_y, start_x);
    box(popup_win, 0, 0);
    string msg1 = "Game Clear!";
    string msg2 = "Press any key to quit.";
    mvwprintw(popup_win, h / 2 - 1 , (w - msg1.length()) / 2, "%s", msg1.c_str());
    mvwprintw(popup_win, h / 2 , (w - msg2.length()) / 2, "%s", msg2.c_str());
    wrefresh(popup_win);
}