#include "Gate.h"
#include <cstdlib>
#include <ctime>

Gate::Gate() {
    gateA = {-1, -1};
    gateB = {-1, -1};
    srand((unsigned int)time(NULL));
}

void Gate::generate(Map& map) {
    std::vector<Position> wallList;
    
    int w = map.getWidth();
    int h = map.getHeight();

    // 1. 일반 벽(WALL) 스캔
    // Map은 (x, y)를 쓰지만, Snake는 (y, x)를 쓰므로 (y, x) 형태로 변환해서 저장
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (map.getCell(x, y) == WALL) { 
                wallList.push_back({y, x});
            }
        }
    }

    // 2. 랜덤하게 2개를 뽑아 게이트로 변경
    if (wallList.size() >= 2) {
        int idx1 = rand() % wallList.size();
        int idx2 = rand() % wallList.size();
        while (idx1 == idx2) { // 겹치지 않게 처리
            idx2 = rand() % wallList.size();
        }

        gateA = wallList[idx1];
        gateB = wallList[idx2];

        // 맵에 적용할 때는 (x, y) 순서로 뒤집어서 세팅
        map.setCell(gateA.second, gateA.first, GATE);
        map.setCell(gateB.second, gateB.first, GATE);
    }
}

Position Gate::teleport(Position currentHead, Direction& currentDirection, Map& map) {
    int w = map.getWidth();
    int h = map.getHeight();

    // 1. 진출 게이트 결정
    Position exitGate;
    if (currentHead.first == gateA.first && currentHead.second == gateA.second) {
        exitGate = gateB;
    } else {
        exitGate = gateA;
    }

    int ey = exitGate.first;  // 출구의 y좌표
    int ex = exitGate.second; // 출구의 x좌표

    // 2. 가장자리 벽인지 확인
    bool isEdge = (ey == 0 || ey == h - 1 || ex == 0 || ex == w - 1);

    if (isEdge) {
        // [규칙 4] 가장자리: 무조건 안쪽으로 진출
        if (ey == 0) currentDirection = DOWN;
        else if (ey == h - 1) currentDirection = UP;
        else if (ex == 0) currentDirection = RIGHT;
        else if (ex == w - 1) currentDirection = LEFT;
    } else {
        // [규칙 4] 내부 벽: 진행방향, 시계, 반시계, 반대 순서 검사
        Direction priorities[4];
        priorities[0] = currentDirection;
        
        switch(currentDirection) {
            case UP:    priorities[1]=RIGHT; priorities[2]=LEFT;  priorities[3]=DOWN; break;
            case DOWN:  priorities[1]=LEFT;  priorities[2]=RIGHT; priorities[3]=UP;   break;
            case LEFT:  priorities[1]=UP;    priorities[2]=DOWN;  priorities[3]=RIGHT;break;
            case RIGHT: priorities[1]=DOWN;  priorities[2]=UP;    priorities[3]=LEFT; break;
        }

        for (int i = 0; i < 4; ++i) {
            Direction checkDir = priorities[i];
            int nx = ex, ny = ey;

            if (checkDir == UP) ny--;
            else if (checkDir == DOWN) ny++;
            else if (checkDir == LEFT) nx--;
            else if (checkDir == RIGHT) nx++;

            if (map.isInside(nx, ny)) {
                int cellValue = map.getCell(nx, ny);
                // 통과 가능한 공간(벽, 면역벽, 다른 게이트가 아님)인지 확인
                if (cellValue != WALL && cellValue != IMMUNE_WALL && cellValue != GATE) {
                    currentDirection = checkDir;
                    break;
                }
            }
        }
    }

    return exitGate; 
}

bool Gate::isSnakePassing(Map& map, Snake& snake) {
    // 뱀의 전체 몸통을 가져와서 현재 게이트 위치와 겹치는지 확인
    std::vector<Position> body = snake.getBody();

    for (int i = 0; i < body.size(); i++) {
        Position pos = body[i];
        if ((pos.first == gateA.first && pos.second == gateA.second) ||
            (pos.first == gateB.first && pos.second == gateB.second)) {
            return true; // 뱀이 게이트 위에 있음 (지우면 안됨)
        }
    }
    return false; // 뱀이 게이트를 완전히 빠져나왔음
}
