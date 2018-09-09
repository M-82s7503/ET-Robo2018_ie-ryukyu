#include "Moving_ex.h"


/**
 *  .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
 *  （抽象クラスなので）継承して使う。
 */



/*Moving_ex::Moving_ex(Motor* l_Wheel, Motor* r_Wheel):
  Moving(l_Wheel, r_Wheel)
{}*/

Moving_ex::Moving_ex(Pointers pt_s):
    Moving(pt_s)
{}


// .run(【方向】, 【距離など】) で一発で実行できるようにしたver.
void Moving_ex::run(Enums::Directs direct, int param) {
    setVector(direct, param);
    Moving::run();
}
// オーバーライドする。
void Moving_ex::setVector(Enums::Directs ForB, int distance) {
  /*distMeasure.init();
  // 「向き」を指定
  direct = ForB;
  dist = distance;
  */
}

// .run(【色】, 【制限など】) で一発で実行できるようにしたver.
void Moving_ex::run(Enums::Directs LorR, Enums::Colors color) {
    setToColor(LorR, color);
    Moving::run();
}
// オーバーライドする。
void Moving_ex::setToColor(Enums::Directs LorR, Enums::Colors color) {
    /*
    till_color = color;

    // param の処理

    // break_condision() でフラグ処理する。
    */
}

