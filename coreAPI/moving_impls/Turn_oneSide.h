#include <cstdlib>

#include "Moving.h"
#include "To_Vector_IF.hpp"
#include "DistMeasure.h"

using namespace ev3api;

class Turn_oneSide : public Moving, public To_Vector_IF {
  public:
    //Turn_oneSide(Motor* l_Wheel, Motor* r_Wheel);
    Turn_oneSide(Pointers pt_s);
    Turn_oneSide(Pointers pt_s, int base_pwm);
    void setBase_PWM(int speed);
    // 走行
    void run(Enums::Directs direct, int distance);
    void setVector(Enums::Directs ForB, int distance); 


  protected:
    float decide_pwm_r();
    float decide_pwm_l();
    bool break_condition();

    //DistMeasure distMeasure;

  private:
    Enums::Directs which_Wheel;

    int speed = 20;
    //int32_t startDig;//開始時の角位置
    int startDig;
    int endDig;//終了時の角位置
};
