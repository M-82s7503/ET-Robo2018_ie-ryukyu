#include <cstdlib>

#include "Moving.h"
#include "To_Vector_IF.hpp"
#include "To_Color_IF.hpp"
#include "DistMeasure.h"

using namespace ev3api;

class Turn : public Moving, public To_Vector_IF, public To_Color_IF {
  public:
    //Turn(Motor* l_Wheel, Motor* r_Wheel);
    Turn(Pointers pt_s);
    Turn(Pointers pt_s, int base_pwm);
    void setBase_PWM(int speed);
    // To Vector
    void run(Enums::Directs direct, int degree);
    void setVector(Enums::Directs LorR, int degree);
    // To Color
    void run(Enums::Directs LorR, Enums::Colors color);
    bool to_color_turn(Enums::Colors color, Enums::Directs LorR, int deg);
    void setToColor(Enums::Directs LorR, Enums::Colors color);


  protected:
    float decide_pwm_r();
    float decide_pwm_l();
    bool break_condition();

  private:
    int speed = 20;

    Enums::Directs direct;
    bool isToColor_mode = false;  // To Vector, Color の切り替えフラグ
    // To Vector系 の値の保管
    int deg;
    int startLeftDig, startRightDig;
    int endLeftDig, endRightDig;
    // To Vector系 の値の保管
    Enums::Colors till_color;

    // To Color Turn
    bool isToColorTurn_mode = false;
    bool isFoundColor = false;
};
