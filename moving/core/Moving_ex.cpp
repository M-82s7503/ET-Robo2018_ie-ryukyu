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

