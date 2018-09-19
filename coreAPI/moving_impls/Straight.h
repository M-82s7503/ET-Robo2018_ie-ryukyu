#include <cstdlib>

#include "Moving_ex.h"
#include "DistMeasure.h"

using namespace ev3api;

class Straight : public Moving_ex {
  public:
    //Straight(Motor* l_Wheel, Motor* r_Wheel);
    Straight(Pointers pt_s);
    Straight(Pointers pt_s, int base_pwm);
    void setBase_PWM(int speed);

  protected:
    float decide_pwm_r();
    float decide_pwm_l();
    bool break_condition();
    void setVector(Enums::Directs ForB, int distance); 

    DistMeasure distMeasure;

  private:
    int speed = 20;
    //int32_t startDig;//開始時の角位置
    int dist;//終了時の角位置
    Enums::Directs direct;
};
