#include <cstdlib>

#include "Moving_ex.h"
#include "DistMeasure.h"

using namespace ev3api;

class Turn_oneSide : public Moving_ex {
  public:
    //Turn_oneSide(Motor* l_Wheel, Motor* r_Wheel);
    Turn_oneSide(Pointers pt_s);
    Turn_oneSide(Pointers pt_s, int base_pwm);
    void setBase_PWM(int speed);

  protected:
    float decide_pwm_r();
    float decide_pwm_l();
    bool break_condition();
    void setVector(Enums::Directs ForB, int distance); 
    void setToColor(Enums::Directs LorR, Enums::Colors color);
    Enums::Colors till_color;
    bool isToColor_mode = false;

  private:
    int speed = 20;
    //int32_t startDig;//開始時の角位置
    int startDig;
    int endDig;//終了時の角位置
    Enums::Directs which_Wheel;

};
