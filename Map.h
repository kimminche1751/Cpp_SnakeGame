#ifndef MAP_H
#define MAP_H

#include <vector>
#include <utility>
#include <ncurses.h>

using namespace std;

// ==========================
// 기본 자료형 정의
// ==========================

// 요소 정의
enum cellTypes{
    EMPTY = 0,
    WALL = 1,
    IMMUNE_WALL = 2,
    SNAKE_HEAD = 3,
    SNAKE_BODY = 4,
    GROWTH_ITEM = 5,
    POISON_ITEM = 6,
    SWAP_ITEM = 7,
    GATE = 8,
};

// 좌표 (Map에서 위치 표현)
typedef pair<int, int> Position;

class Map {
private:
    vector<vector<int>> grid; 
    int width, height;
    int stage;

public:
    /*
    [구현해야 할 것]
    - 2차원 배열로 맵 구성 (최소 21x21)
    - 각 요소 의미:
        0: 빈 공간
        1: Wall
        2: Immune Wall
        3: Snake Head
        4: Snake Body
        5: Growth Item
        6: Poison Item
        7: Gate
    */

    Map(int w, int h);

    // 맵 초기화 (벽, Immune Wall 배치)
    void initialize();

    // 스테이지 제작(내부 벽 배치)
    void makeStage(int stage);

    // 특정 위치 값 가져오기
    int getCell(int x, int y);

    // 특정 위치 값 설정
    void setCell(int x, int y, int value);

    // 맵 범위 체크
    bool isInside(int x, int y);

    // 빈 공간인지 확인 (아이템 생성용)
    bool isEmpty(int x, int y);

    // width, height 값 가져오기
    int getWidth();

    int getHeight();
};

#endif