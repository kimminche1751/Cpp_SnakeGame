#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> Position;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
private:
    vector<Position> body;
    Direction dir;

public:
    Snake(Position start);

    void setDirection(Direction newDir);

    Direction getDirection();

    void move();

    void grow();

    void shrink();

    Position getHead();

    vector<Position> getBody();

    bool checkSelfCollision();
};

#endif