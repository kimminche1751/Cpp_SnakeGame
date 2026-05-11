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
    vector<unsigned int> growthItemTime;
    vector<unsigned int> poisonItemTime;

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
    }

    void spawnGrowth(Map& map);
    void spawnPoison(Map& map);

    // 아이템 삭제 (시간 경과)
    void removeOldItems();

    // Snake와 충돌 체크
    int checkCollision(Position head);

    void spawnGrowth(Map& map){ //Growth item spawning
        if(growthItems.size() + poisonItems.size() <= 3)//필드 내 동시에 존재 가능한 아이템은 3개로 제한되어 있으므로
        {
            int x, y;
            do{ 
                srand((unsigned int)time(NULL)); //time값으로 시드값 초기화
                //X, Y 랜덤 좌표 생성
                x = rand() % map.getWidth();
                y = rand() % map.getHeight();
            }
            while(!map.isInside(x, y) || !map.isEmpty(x, y));//올바른 좌표가 나올때까지 좌표 생성 반복

            map.setCell(x, y, 5); //맵의 해당 위치에 아이템 배치
            growthItems.push_back({x, y}); //growthItem 위치를 벡터에 추가
            growthItemTime.push_back((unsigned int)time(NULL)); //시간 정보 컨테이너에 생성 시간을 push
            return;
        }
    }

    void spawnPoison(Map& map){
        //형식은 spawnGrowth와 동일하되 일부 변수명과 상수값 변경이 필요
    }
    void removeOldItems(Map& map){
        unsigned int now = (unsigned int)time(NULL);
        for(int i = 0; i != growthItems.size(); i++){ //for문으로 시간 정보 컨테이너를 순회하며
            if(now >= growthItemTime[i] + 5){
                //해당하는 아이템의 위치정보를 참조해 map에 접근해 아이템을 빈 공간으로 변경한다.
                growthItems.erase(growthItems.begin() + i); //시간이 지난 아이템 위치정보 제거
                growthItemTime.erase(growthItemTime.begin() + i); //시간이 지난 아이템 시간정보 제거
                i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
            }
        }
        for(int i = 0; i != poisonItems.size(); i++){
            if(now >= poisonItemTime[i] + 5){
                poisonItems.erase(poisonItems.begin() + i);
                poisonItemTime.erase(poisonItemTime.begin() + i);
                i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
            }
        }
    }

    int checkCollision(Position head){//move의 상세 구현에 따라 코드가 수정될 수 있음
        int x = head.first;
        int y = head.second;
        for(int i = 0; i != growthItems.size(); i++){ //for문으로 위치 정보 컨테이너를 순회하며
            if(head == growthItems[i]){//머리의 위치와 growth 아이템의 위치가 같으면
                snake::growth(); //뱀의 길이를 1 증가시키고
                growthItems.erase(growthItems.begin() + i); //소멸된 아이템 위치정보 제거
                growthItemTime.erase(growthItemTime.begin() + i); //소멸된 아이템 시간정보 제거
                i--; //erase()를 실행하면 뒤의 원소들이 한칸씩 당겨지므로 i를 1 감소시킴
            }
        }
        for(int i = 0; i != poisonItems.size(); i++){
            if(head == poisonItems[i]){
                snake::shrink();
                poisonItems.erase(poisonItems.begin() + i);
                poisonItemTime.erase(poisonItemTime.begin() + i);
                i--;
            }
        }
    }
};
