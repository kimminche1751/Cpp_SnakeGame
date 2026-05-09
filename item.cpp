#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "map.h"

//#include "snake.h" //snake.h 파일이 완성되면 적용될 예정

#define OLDTIME 100 //item 지속시간

using namespace std;

class Item{
    private:
    vector<Position> growthItems; //만약 queue로 구현 가능하다면 queue로 변경
    vector<Position> poisonItems; //queue로 변경 가능하다면 queue로 변경

    public:
    /*
    [구현해야 할 것 - Rule #2]
    - Growth: 길이 +1
    - Poison: 길이 -1 (길이 3 미만이면 실패)
    - 아이템은 랜덤 위치 생성
    - 일정 시간 후 사라짐
    - 최대 3개 유지
    */

    Item(){
        vector<Position> growthItems; //growth 아이템의 위치 목록
        vector<Position> poisonItems; //poison 아이템의 위치 목록
        /*각 아이템별 설치 시간에 관한 정보를 따로 관리할 수 있는 컨테이너가 있으면 좋을 듯
            vector<unsigned int> growthItemTime;
            vector<unsigned int> poisonItemTime;
        */
    }

    void spawnGrowth(Map& map);
    void spawnPoison(Map& map);

    // 아이템 삭제 (시간 경과)
    void removeOldItems();

    // Snake와 충돌 체크
    int checkCollision(Position head);

    void spawnGrowth(Map& map){ //Growth item spawning
        if(growthItems.size() + poisonItems.size() <= 3)//필드 내 동시에 존재 가능한 아이템 숫자가 3개로 제한되어 있으므로
        {
            do{ 
                srand((unsigned int)time(NULL)); //time값으로 시드값 초기화
                //X, Y 랜덤 좌표 생성
                int x = rand() % width; //map의 멤버변수 width와 height에 접근이 불가능해
                int y = rand() % height; //이를 참조할 수 있는 메서드가 있으면 좋겠음
            }
            while(!map.isInside(x, y) || !map.isEmpty(x, y));//올바른 좌표가 나올때까지 좌표 생성 반복

            map.setCell(x, y, 5); //맵의 해당 위치에 아이템 배치
            growthItems.push_back({x, y}); //growthItem 위치를 벡터에 추가(큐로 바뀔 경우 enqueue 형식으로 변경)
            /*시간 정보 컨테이너에 생성 시간을 push
            growthItemTime.push((unsigned int)time(NULL));
            */
            return;
        }
    }

    void spawnPoison(Map& map){
        //형식은 spawnGrowth와 동일하되 일부 변수명과 상수값 변경이 필요
    }
    void removeOldItems(){ //파라미터로 Map 타입의 &map을 받아 맵에 접근해야 아이템을 삭제할 수 있으므로 파라미터 변경에 대해 제안할 필요가 있음.
        unsigned int now = (unsigned int)time(NULL);
        for(int i = 0; i < 3; i++){ //for문으로 시간 정보 컨테이너를 순회하며
            if(now >= timeContainer[i] + 5){
                growthItems //시간이 지난 아이템 제거
            }
        }
    }

    int checkCollision(Position head){ //head는 뱀의 머리 위치임. snake의 move 구현에 따라 세부 구현을 확정짓고자 함.
        int x = head.first;
        int y = head.second;
        switch(Map::getCell(x, y)){
            case 4:
            case 5: //growth 아이템을 만난 경우
                snake::grow();
                Map::setCell(x, y, 3);
            case 6: //poison 아이템을 만난 경우
                snake::shrink();
                Map::setCell(x, y, 3);
            case 7:

        }
    }
}