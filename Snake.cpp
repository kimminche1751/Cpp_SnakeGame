#include "Snake.h"

Snake::Snake(Position start) {
    body.push_back(start);

    // 초기 몸통 3칸
    body.push_back({start.first, start.second - 1});
    body.push_back({start.first, start.second - 2});

    dir = RIGHT;
}

void Snake::setDirection(Direction newDir) {

    // 반대 방향 입력 금지
    if ((dir == UP && newDir == DOWN) ||
        (dir == DOWN && newDir == UP) ||
        (dir == LEFT && newDir == RIGHT) ||
        (dir == RIGHT && newDir == LEFT)) {
        return;
    }

    dir = newDir;
}

Direction Snake::getDirection() {
    return dir;
}

void Snake::move() {

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

    // 머리 추가
    body.insert(body.begin(), newHead);

    // 꼬리 제거
    body.pop_back();
}

void Snake::grow() {

    // 마지막 꼬리 복사
    Position tail = body.back();

    body.push_back(tail);
}

void Snake::shrink() {

    // 길이 최소 3 유지
    if (body.size() > 3) {
        body.pop_back();
    }
}

Position Snake::getHead() {
    return body[0];
}

vector<Position> Snake::getBody() {
    return body;
}

bool Snake::checkSelfCollision() {

    Position head = body[0];

    for (int i = 1; i < body.size(); i++) {

        if (head == body[i]) {
            return true;
        }
    }

    return false;
}

void Snake::teleportHead(Position newPos) {
    body[0] = newPos;
}