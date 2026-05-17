#include "Map.h"

Map::Map(int w, int h){
    width = w;
    height = h;
    grid.resize(height, vector<int>(width, 0));
};

// 맵 초기화 (벽, Immune Wall 배치)
void Map::initialize(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(i == 0 || i == height - 1 || j == 0 || j == width - 1)
                grid[i][j] = WALL;
        }
    }
    grid[0][0] = IMMUNE_WALL;
    grid[0][width - 1] = IMMUNE_WALL;
    grid[height - 1][0] = IMMUNE_WALL;
    grid[height - 1][width - 1] = IMMUNE_WALL;
};

// 특정 위치 값 가져오기
int Map::getCell(int x, int y){
    return grid[y][x];
};

// 특정 위치 값 설정
void Map::setCell(int x, int y, int value){
    grid[y][x] = value;
};

// 맵 범위 체크
bool Map::isInside(int x, int y){
    if(x >= 0 && x < width){
        if(y >= 0 && y < height)
            return true;
    }
    return false;
};

// 빈 공간인지 확인 (아이템 생성용)
bool Map::isEmpty(int x, int y){
    if(grid[y][x] == EMPTY)
        return true;
    return false;
};

// width, height 값 가져오기
int Map::getWidth(){
    return width;
};

int Map::getHeight(){
    return height;
};