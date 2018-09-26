#include <cstdlib>

#include "Enums.h"
#include "DistMeasure.h"
#include "Straight.h"
#include "Turn.h"
#include "Turn_oneSide.h"

using namespace ev3api;

class MoveTemps {
  public:
    //MoveTemps(Motor* l_Wheel, Motor* r_Wheel);
    MoveTemps(Pointers pt_s);
    MoveTemps(Pointers pt_s, int base_pwm);
    void setBase_PWM(int speed);

    // 実行
    // 線と、ロボの中心線を合わせる。
    void ride_onLine(Enums::Directs ForB, int dist, Enums::Colors line_c, Enums::Colors other_c);
    bool searchColor(Enums::Colors color, Enums::Directs first_search_d, int deg);


  private:
    Enums::Directs direct;
    int dist;
    DistMeasure distMeasure;
    int speed = 20;

    Straight mv_straight;
    Turn mv_turn;
};
