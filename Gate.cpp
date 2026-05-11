#include "Gate.h"
#include <cstdlib>
#include <ctime>

Gate::Gate() {
    gateA = { -1, -1 };
    gateB = { -1, -1 };
    srand((unsigned int)time(NULL));
}

void Gate::generate(Map& map) {
    std::vector<Position> wallList;

    // Map 클래스에 추가된 Getter 함수 사용
    int w = map.getWidth();
    int h = map.getHeight();

    // 1. 일반 벽(WALL) 위치 수집
    // Immune Wall(2)은 Gate가 될 수 없으므로 제외 
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (map.getCell(x, y) == WALL) { // 1번 값 
                wallList.push_back({ y, x }); // Snake 좌표계 (y, x)로 저장
            }
        }
    }

    // 2. 임의의 위치에 한 쌍의 Gate 생성 
    if (wallList.size() >= 2) {
        int idx1 = rand() % wallList.size();
        int idx2 = rand() % wallList.size();
        while (idx1 == idx2) {
            idx2 = rand() % wallList.size();
        }

        gateA = wallList[idx1];
        gateB = wallList[idx2];

        // Map 데이터 업데이트 (7번 값) 
        // map.setCell은 (x, y) 순서를 받으므로 순서 반전
        map.setCell(gateA.second, gateA.first, GATE);
        map.setCell(gateB.second, gateB.first, GATE);
    }
}

Position Gate::teleport(Position currentHead, Direction& currentDirection, Map& map) {
    int w = map.getWidth();
    int h = map.getHeight();

    // 1. 진출 게이트 결정 (A 진입 시 B로 진출) 
    Position exitGate;
    if (currentHead.first == gateA.first && currentHead.second == gateA.second) {
        exitGate = gateB;
    }
    else {
        exitGate = gateA;
    }

    int ey = exitGate.first;
    int ex = exitGate.second;

    // 2. 진출 방향 결정 규칙 적용 
    bool isEdge = (ey == 0 || ey == h - 1 || ex == 0 || ex == w - 1);

    if (isEdge) {
        // [규칙 4-1] 가장자리 벽: 무조건 맵 안쪽 방향 진출 
        if (ey == 0) currentDirection = DOWN;
        else if (ey == h - 1) currentDirection = UP;
        else if (ex == 0) currentDirection = RIGHT;
        else if (ex == w - 1) currentDirection = LEFT;
    }
    else {
        // [규칙 4-2] 내부 벽: 우선순위에 따른 방향 회전 
        Direction priorities[4];
        priorities[0] = currentDirection; // 1: 진입 방향 

        switch (currentDirection) {
        case UP:    priorities[1] = RIGHT; priorities[2] = LEFT;  priorities[3] = DOWN; break; // 시계 -> 반시계 -> 반대 
        case DOWN:  priorities[1] = LEFT;  priorities[2] = RIGHT; priorities[3] = UP;   break;
        case LEFT:  priorities[1] = UP;    priorities[2] = DOWN;  priorities[3] = RIGHT; break;
        case RIGHT: priorities[1] = DOWN;  priorities[2] = UP;    priorities[3] = LEFT; break;
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
                // 통과 가능한 공간인지 확인 (벽이 아니어야 함)
                if (cellValue != WALL && cellValue != IMMUNE_WALL && cellValue != GATE) {
                    currentDirection = checkDir;
                    break;
                }
            }
        }
    }

    return exitGate;
}