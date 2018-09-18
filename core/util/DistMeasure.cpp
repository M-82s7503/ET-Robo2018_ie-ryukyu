#include "DistMeasure.h"


/**
 *  現在位置を、タイヤの回転数から計測するクラス。
 */


DistMeasure::DistMeasure(Motor* l_Wheel, Motor* r_Wheel)
{
  leftWheel = l_Wheel;
  rightWheel = r_Wheel;
  init();
}


void DistMeasure::init() {
  startDig_L = leftWheel->getCount();
  startDig_R = rightWheel->getCount();
}
void DistMeasure::resetDig() {
  leftWheel->setCount(0);
  rightWheel->setCount(0);
  startDig_L = leftWheel->getCount();
  startDig_R = rightWheel->getCount();
}

float DistMeasure::getNowDist(Enums::Directs whichWheel) {
  // 360° 回転する間に 320 進むらしいので、
  // 320/360 = 8/9 [mm/度]
  // よって、距離に変換したいなら、 8/9 をかければ良い。
  //msg_f("getNowDist()", 1);
  switch (whichWheel) {
    case Enums::LEFT :
      return abs(leftWheel->getCount() - startDig_L) * 8 / 9;
    case Enums::RIGHT :
      return abs(rightWheel->getCount() - startDig_R) * 8 / 9;
    case Enums::LR_AVG :
      // 両輪の平均値を取得
      return abs( ( (leftWheel->getCount()-startDig_L) + (rightWheel->getCount()-startDig_R) ) /2 ) * 8 / 9;
    default:
      msg_f("direct is not collect! (getNowDist())", 1);
      return 1;
  }
}

