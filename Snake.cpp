#include "Snake.h"

// 생성자

Snake::Snake(Position start) {

    /*
    초기 Snake 형태

    [H][B][B]

    시작 방향:
    RIGHT
    */

    body.push_back(start);

    body.push_back({start.first, start.second - 1});

    body.push_back({start.first, start.second - 2});

    dir = RIGHT;

    gameOver = false;
}

// 방향 설정

void Snake::setDirection(Direction newDir) {

    /*
    Rule #1

    반대 방향 이동 시 게임오버
    */

    if ((dir == UP && newDir == DOWN) ||
        (dir == DOWN && newDir == UP) ||
        (dir == LEFT && newDir == RIGHT) ||
        (dir == RIGHT && newDir == LEFT)) {

        gameOver = true;

        return;
    }

    dir = newDir;
}


// 현재 방향 반환

Direction Snake::getDirection() const {
    return dir;
}

// 이동

void Snake::move() {

    /*
    이동 방식

    1. 현재 head 기준 새 head 생성
    2. vector 맨 앞에 삽입
    3. 마지막 tail 제거

    */

    Position head = body[0];

    Position newHead = head;

    switch (dir) {

        case UP:
            newHead.first--;
            break;

        case DOWN:
            newHead.first++;
            break;

        case LEFT:
            newHead.second--;
            break;

        case RIGHT:
            newHead.second++;
            break;
    }

    // 새 머리 추가
    body.insert(body.begin(), newHead);

    // 꼬리 제거
    body.pop_back();
}

// 성장

void Snake::grow() {

    /*
    마지막 tail 복사

    길이 +1
    */

    Position tail = body.back();

    body.push_back(tail);
}

// 감소

void Snake::shrink() {

    /*
    Poison Item 처리

    길이 감소

    길이가 3 미만이면 실패
    */

    body.pop_back();

    if (body.size() < 3) {
        gameOver = true;
    }
}


// 머리 반환

Position Snake::getHead() const {
    return body[0];
}


// 몸 전체 반환

const vector<Position>& Snake::getBody() const {
    return body;
}


// 자기 몸 충돌 검사

bool Snake::checkSelfCollision() {

    /*
    head와 body 비교

    충돌 시 게임오버
    */

    Position head = body[0];

    for (int i = 1; i < body.size(); i++) {

        if (head == body[i]) {

            gameOver = true;

            return true;
        }
    }

    return false;
}


// Gate 텔레포트

void Snake::teleportHead(Position newPos) {

    /*
    Gate 통과 시 사용

    head 좌표 강제 변경
    */

    body[0] = newPos;
}

// 게임오버 여부 반환

bool Snake::isGameOver() const {
    return gameOver;
}

// 꼬리 진행 방향 반환

Direction Snake::getTailDirection() const {

    /*
    tail 기준으로
    마지막 두 칸 비교

    body[n-2] -> body[n-1]
    방향 계산
    */

    int n = body.size();

    Position beforeTail = body[n - 2];

    Position tail = body[n - 1];

    // tail이 아래쪽
    if (tail.first > beforeTail.first)
        return DOWN;

    // tail이 위쪽
    if (tail.first < beforeTail.first)
        return UP;

    // tail이 오른쪽
    if (tail.second > beforeTail.second)
        return RIGHT;

    // tail이 왼쪽
    return LEFT;
}


//머리와 꼬리 Swap
void Snake::swapTailAndHead(){
    Direction tailDir = getTailDirection(); //꼬리의 현재 진행방향
    Direction newDir;
    reverse(body.begin(), body.end()); //snake 뒤집기
    if(tailDir == getDirection()){ //꼬리가 머리와 진행방향이 같으면 방향을 바로 180도 바꿀 수 없으므로 따로 처리
        switch (tailDir)
        {
        case UP:
            setDirection(RIGHT); //90도씩 머리 방향을 2회 돌림
            setDirection(DOWN);
            break;
        case DOWN:
            setDirection(LEFT);
            setDirection(UP);
            break;
        case RIGHT:
            setDirection(DOWN);
            setDirection(LEFT);
            break;
        case LEFT:
            setDirection(UP);
            setDirection(RIGHT);
            break;
        }
    }
    else{ //기존의 머리 방향과 꼬리 진행방향이 다르면 바로 방향을 180도 변경
        switch (tailDir)
        {
        case UP:
            setDirection(DOWN);
            break;
        case DOWN:
            setDirection(UP);
            break;
        case RIGHT:
            setDirection(LEFT);
            break;
        case LEFT:
            setDirection(RIGHT);
            break;
        }
    }
} 