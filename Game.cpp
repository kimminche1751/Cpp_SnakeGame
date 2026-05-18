#include "Game.h"

/*
[구현해야 할 것]
- 전체 게임 루프 관리
- 입력 처리 (방향키)
- tick 기반 이동
- 충돌 검사
- 단계별 기능 구현 (1~5단계)
*/

Game::Game() : map(21,21), snake({10, 10}), gameOver(false), gateExist(false), itemTime(0){
    init();
};

// 초기화
void Game::init(){
    map.initialize();
};

// 게임 실행
void Game::run(){
    int gateTime = 0;
    while(!isGameOver()){
        // 5초마다 게이트 위치 변경 (통과중에는 변경 X)
        if(gateTime >= 50){
            if(!gate.isSnakePassing(map, snake)){
                gate.remove(map);
                gateExist = false;
                gateTime = 0;
            }
        }
        processInput();
        update();
        erase();
        render(map.getWidth(), map.getHeight());
        refresh();
        usleep(100000);
        gateTime++;
    }
};

// 입력 처리
void Game::processInput(){

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
        if(rand() % 100 < 50){
            item.spawnGrowth(map);
        }
        else{
            item.spawnPoison(map);
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
        Position newPos = gate.teleport(head, snake.getDirection(), map);
        snake.teleportHead(newPos);
    }

    // 아이템 충돌
    int itemCollision = item.checkCollision(head);
    if(itemCollision == GROWTH_ITEM){
        snake.grow();
    }

    if(itemCollision == POISON_ITEM){
        snake.shrink();
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
                case 3:
                    shape = '3';
                    color = 3;
                    break;
                case 4:
                    shape = '4';
                    color = 4;
                    break;
                case 5:
                    shape = '5';
                    color = 5;
                    break;
                case 6:
                    shape = '6';
                    color = 6;
                    break;
                case 7:
                    shape = '7';
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

        char shape = '0';
        int color = 3;

        if(i == 0){
            shape = '3';
            color = 3;
        }
        else{
            shape = '4';
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
