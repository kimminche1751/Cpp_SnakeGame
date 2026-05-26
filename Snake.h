// Snake.h

#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <utility>

using namespace std;

// ==========================
// 기본 자료형
// ==========================

typedef pair<int, int> Position;

// 방향
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// ==========================
// Snake ADT
// ==========================

class Snake {
private:
    // body[0] = head
    vector<Position> body;

    // 현재 방향
    Direction dir;

    // 게임 오버 여부
    bool gameOver;

public:

    /*
    [기능]
    - Snake 이동
    - 방향 변경
    - 성장 / 감소
    - 자기 몸 충돌 검사
    - Gate 텔레포트 대응
    */

    // 생성자
    Snake(Position start);

    // 방향 설정
    // 반대 방향 입력 시 게임오버 처리
    void setDirection(Direction newDir);

    // 현재 방향 반환
    Direction getDirection() const;

    // 한 칸 이동
    void move();

    // 길이 증가
    void grow();

    // 길이 감소
    // 길이 3 미만이면 게임오버
    void shrink();

    // 머리 위치 반환
    Position getHead() const;

    // 전체 몸 반환
    const vector<Position>& getBody() const;

    // 자기 몸 충돌 검사
    bool checkSelfCollision();

    // Gate 통과 시 머리 위치 강제 변경
    void teleportHead(Position newPos);

    // 게임오버 여부 반환
    bool isGameOver() const;

    // 꼬리 위치 반환
    Position getTail() const;

    // 꼬리 진행 방향 반환
    Direction getTailDirection() const;
};

#endif