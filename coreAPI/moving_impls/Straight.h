#include <cstdlib>

#include "Moving.h"
#include "To_Vector_IF.hpp"
#include "To_Color_IF.hpp"
#include "DistMeasure.h"

using namespace ev3api;

class Straight : public Moving, public To_Vector_IF//, public To_Color_IF 
{
  public:
    Straight(Pointers pt_s);
    Straight(Pointers pt_s, int base_pwm);
    void setBase_PWM(int speed);
    // 走行
    void run(Enums::Directs direct, int distance);
    void setVector(Enums::Directs ForB, int distance); 
    void run(Enums::Colors to_c, Enums::Directs ForB, int distance);  // run() を少し改良した。
    void setToColor(Enums::Directs LorR, Enums::Colors color);

  protected:
    float decide_pwm_r();
    float decide_pwm_l();
    bool break_condition();

  private:
    int dist;
    Enums::Directs direct;
    DistMeasure distMeasure;

    Enums::Colors till_color;
    bool isToColor_mode = false;
    bool isFoundColor = false;

    int speed = 20;
    //int32_t startDig;//開始時の角位置
};
