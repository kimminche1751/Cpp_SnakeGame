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

    // 1. 일반 벽(WALL) 스캔 (Immune Wall은 제외) 
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (map.getCell(x, y) == WALL) { 
                wallList.push_back({y, x}); // Snake 좌표계 (y, x) 저장
            }
        }
    }

    // 2. 랜덤하게 2개 선택하여 게이트(7)로 설정
    if (wallList.size() >= 2) {
        int idx1 = rand() % wallList.size();
        int idx2 = rand() % wallList.size();
        while (idx1 == idx2) idx2 = rand() % wallList.size();

        gateA = wallList[idx1];
        gateB = wallList[idx2];

        map.setCell(gateA.second, gateA.first, GATE);
        map.setCell(gateB.second, gateB.first, GATE);
    }
}

Position Gate::teleport(Position currentHead, Direction currentDirection, Map& map) {
    int w = map.getWidth();
    int h = map.getHeight();

    // 1. 출구 게이트 결정
    Position exitGate = (currentHead.first == gateA.first && currentHead.second == gateA.second) ? gateB : gateA;

    int ey = exitGate.first;
    int ex = exitGate.second;

    // 2. 진출 방향 규칙 적용
    bool isEdge = (ey == 0 || ey == h - 1 || ex == 0 || ex == w - 1);

    if (isEdge) {
        // [규칙 4-1] 가장자리 벽: 무조건 안쪽 진출 
        if (ey == 0) currentDirection = DOWN;
        else if (ey == h - 1) currentDirection = UP;
        else if (ex == 0) currentDirection = RIGHT;
        else if (ex == w - 1) currentDirection = LEFT;
    } else {
        // [규칙 4-2] 내부 벽: 우선순위(직진->시계->반시계->반대) 적용 
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
    // [규칙 3] 뱀이 통과 중이면 게이트 소멸 방지 
    std::vector<Position> body = snake.getBody();
    for (const auto& pos : body) {
        if ((pos.first == gateA.first && pos.second == gateA.second) ||
            (pos.first == gateB.first && pos.second == gateB.second)) {
            return true;
        }
    }
    return false;
}

void Gate::remove(Map& map) {
    // 게이트를 다시 벽(1)으로 되돌리고 좌표 초기화
    if (gateA.first != -1) map.setCell(gateA.second, gateA.first, WALL);
    if (gateB.first != -1) map.setCell(gateB.second, gateB.first, WALL);
    gateA = {-1, -1};
    gateB = {-1, -1};
}