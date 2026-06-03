/*
    Item.h : Item 클래스 및 멤버변수, 멤버 함수 선언

    Item 클래스 : 아이템 생성 및 삭제, 아이템 접촉에 관한 처리

    생성자, 소멸자는 Compiler가 정의하는 Default 생성자, 소멸자 사용(멤버 변수에 값 초기화 불필요)
    복사 생성자, 할당 연산자 불필요(프로그램 실행 간 1개의 인스턴스만 사용)

    ---private member functions---
    spawnItem : 아이템 생성을 처리하는 내부 함수
    deleteItem : 아이템 삭제를 처리하는 내부 함수

    ---public member functions---
    spawn- 계열 함수 : 내부적으로 private 함수인 Item::spawnItem() 호출
    spawnGrowth : Growth 아이템을 생성하는 public 함수
    spawnPoison : Poison 아이템을 생성하는 public 함수
    spawnSwap : Swap 아이템을 생성하는 public 함수 (추가 아이템)
    removeOldItems, checkCollision 함수 : private 함수인 Item::deleteItem() 호출
    removeOldItems : 매 틱마다 호출되어, 시간정보를 1씩 늘려가며 시간정보가 50틱 이상인 아이템을 제거하는 public 함수
    checkCollision : 매 틱마다 호출되어, 스네이크의 head 위치와 아이템 위치를 비교해 동일한 위치에 있는 아이템 종류를 반환. (반환값에 따라 snake의 상태 변화 메서드들을 호출)

    [구현해야 할 것 - Rule #2]
    - Growth: 길이 +1 : Snake에서 구현
    - Poison: 길이 -1 (길이 3 미만이면 실패) : Snake에서 구현
    - 아이템은 랜덤 위치 생성 : spwanItem() 및 spawn- 계열 함수에서 구현
    - 일정 시간 후 사라짐 : removeOldItems()에서 구현
    - 최대 3개 유지 : spawnItem() 에서 조건문으로 판정
    - 추가 아이템 구현 (Swap 아이템(spawnSwap, Snake의 swapTailAndHead 메서드로 구현)
    */
#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <cstdlib>
#include "Map.h"
using namespace std;

class Item {
private:
    //item information containers
    vector<int> itemTypes; //아이템 종류 목록
    vector<Position> itemPositions; //아이템의 위치 목록
    vector<unsigned int> itemTimes; //아이템의 시간 목록

    //item 내부 처리 함수
    void spawnItem(Map& map, int type); //아이템 생성 처리
    void deleteItem(Map& map, int& i); //아이템 삭제 처리

public:

    //item spawning methods
    void spawnGrowth(Map& map);
    void spawnPoison(Map& map);
    void spawnSwap(Map& map);

    // 아이템 삭제 (시간 경과)
    void removeOldItems(Map& map);

    // Snake와 충돌 체크
    int checkCollision(const Position head, Map& map);

};

#endif