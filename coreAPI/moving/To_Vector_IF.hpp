#ifndef To_Vector_IF_H_
#define To_Vector_IF_H_

//#include "Motor.h"
//using namespace ev3api;

#include "Enums.h"


class To_Vector_IF {
  public:
    // 仮想デストラクタ(触らない。)
    virtual ~To_Vector_IF(){}

    // 継承したら、必ず実装する。
    virtual void run(Enums::Directs direct, int distance) = 0;
    virtual void setVector(Enums::Directs direct, int distance) = 0;

};



/*
＜使い方＞
  ↓ を、それぞれ追加・実装 する。
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
【クラス名】.h
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
  public:
    // 走行
    void run(Enums::Directs direct, int distance);
    void setVector(Enums::Directs LorR, int distance);
  private:
    Enums::Directs direct;   // 変数名は適当に
    int dist;
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜


〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
【クラス名】.cpp
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

// .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
void 【クラス名】::run(Enums::Directs dirt, int distance) {
    setVector(dirt, distance);
    Moving::run();
}
// オーバーライドする。
void 【クラス名】::setVector(Enums::Directs dirt, int distance) {
  // 「向き」を指定
  direct = dirt;
  dist = distance;
}

〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
*/

#endif  // To_Vector_IF_H_