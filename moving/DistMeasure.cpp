#include "DistMeasure.h"


/**
 *  現在位置を、タイヤの回転数から計測するクラス。
 */


DistMeasure::DistMeasure():
  leftWheel(PORT_C), rightWheel(PORT_B)
{
  init();
}


void DistMeasure::init() {
  startDig_L = leftWheel.getCount();
  startDig_R = rightWheel.getCount();
}
void DistMeasure::resetDig() {
  leftWheel.setCount(0);
  rightWheel.setCount(0);
  startDig_L = leftWheel.getCount();
  startDig_R = rightWheel.getCount();
}

float DistMeasure::getNowDist(LR whichWheel) {
  // 360° 回転する間に 320 進んだので、
  // 320/360 = 8/9 [mm/度]
  // よって、距離に変換したいなら、 8/9 をかければ良い。
  if (whichWheel == LEFT) {
    return (startDig_L - leftWheel.getCount()) * 8 / 9;
  } else {
    return (startDig_R - rightWheel.getCount()) * 8 / 9;
  }
}

