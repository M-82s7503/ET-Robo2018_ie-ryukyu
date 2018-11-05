#ifndef To_Color_IF_H_
#define To_Color_IF_H_

//#include "Motor.h"
//using namespace ev3api;

#include "Enums.h"


class To_Color_IF {
  public:
    // 仮想デストラクタ(触らない。)
    virtual ~To_Color_IF(){}

    // 継承したら、必ず実装する。
    virtual void run(Enums::Directs LorR, Enums::Colors color) = 0;
    virtual void setToColor(Enums::Directs LorR, Enums::Colors color) = 0;

};

/*
＜使い方＞
  ↓ を、それぞれ追加・実装 する。
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
【クラス名】.h
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
  public:
    // 走行
    void run(Enums::Directs direct, Enums::Colors color);
    void setToColor(Enums::Directs LorR, Enums::Colors color);
  private:
    Enums::Colors till_color;
    bool isToColor_mode = false;
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
【クラス名】.cpp
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

// .run(【色】, 【制限など】) で一発で実行できるようにしたver.
void 【クラス名】::run(Enums::Directs LorR, Enums::Colors color) {
    setToColor(LorR, color);
    Moving::run();
}
// オーバーライドする。
void 【クラス名】::setToColor(Enums::Directs LorR, Enums::Colors color) {
    till_color = color;
    isToColor_mode = true;  // ToVector でフラグを戻すことを忘れない！
    // param の処理

    // break_condision() でフラグ処理する。
}


bool Tracer::break_condition() {
        ・・・

    // 【break条件】その他
    if (isToColor && colorSensor->getColorNumber() == static_cast<int>(till_color)) {
        return true;
    }
    // 続行
    return false;
}

〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
*/


#endif  // To_Color_IF_H_