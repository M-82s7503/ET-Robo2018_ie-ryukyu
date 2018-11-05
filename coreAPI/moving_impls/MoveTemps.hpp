#ifndef MOVE_TEMPS_H_
#define MOVE_TEMPS_H_

#include <cstdlib>
#include <math.h>

#include "Enums.h"
#include "DistMeasure.h"

#include "Move_Basic.hpp"
#include "Straight.h"
#include "Turn.h"
#include "Turn_oneSide.h"


using namespace ev3api;

class MoveTemps {
  public:
    //MoveTemps(Motor* l_Wheel, Motor* r_Wheel);
    MoveTemps(Pointers ptrs);
    MoveTemps(Pointers ptrs, int base_pwm);
    void setBase_PWM(int speed);

    //--  実行  --//
    // 線と、ロボの中心線を合わせる。
//    void ride_onLine(Enums::Directs ForB, Enums::Directs first_LorR, int dist, Enums::Colors line_c, Enums::Colors other_c);
//    int8_t searchColor(Enums::Colors color, Enums::Directs first_search_d, int deg, int nagare);

    // 目の前の線に、ちょうど垂直になるように回転する。
    bool ride_onLine_vertical(Enums::Colors in_c, Enums::Directs start_d);
    float getRCos() {
      return cos(halfDeg * 3.14 / 180);
    }

  private:
    Enums::Directs direct;
    int dist;
    DistMeasure distMeasure;
    int speed = 20;
    const int8_t divide_unit = 25;
    int halfDeg;

    ColorSensor* colorSensor;
    Clock clock;

    Move_Basic mv_basic;
    Straight mv_straight;
    Turn mv_turn;
};


#endif // MOVE_TEMPS_H_
