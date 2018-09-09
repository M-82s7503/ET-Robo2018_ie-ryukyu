#include "Turn_oneSide.h"

/*
Turn_oneSide::Turn_oneSide(Motor* l_Wheel, Motor* r_Wheel):
  Moving_ex(l_Wheel, r_Wheel),
  distMeasure(l_Wheel, r_Wheel)
{}*/
Turn_oneSide::Turn_oneSide(Pointers pt_s):
  Moving_ex(pt_s)//,
  //distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
{}
Turn_oneSide::Turn_oneSide(Pointers pt_s, int base_pwm):
  Moving_ex(pt_s)//,
  //distMeasure(pt_s.getLeftWheel(), pt_s.getRightWheel())
{
    setBase_PWM(base_pwm);
}

void Turn_oneSide::setBase_PWM(int base_pwm) {
    speed = base_pwm;
}

void Turn_oneSide::setVector(Enums::Directs LorR, int deg) {
    //distMeasure.init();
    // 「どちらのタイヤを回すか」を指定
    which_Wheel = LorR;
    switch (which_Wheel) {
        case Enums::LEFT:
            startDig = leftWheel->getCount();
            break;
        case Enums::RIGHT:
            startDig = rightWheel->getCount();
            break;
        default:
            // 明らかにおかしいので、エラー処理
            msg_f("Turn_oneSide which_Wheel Error", 2);
            startDig =0;
          break;
    }
    endDig = deg * 3;
    speed = (deg / abs(deg)) * speed;

    // フラグを立てる。
    isToColor_mode = false;
}

void Turn_oneSide::setToColor(Enums::Directs LorR, Enums::Colors color) {
    // 「どちらのタイヤを回すか」を指定
    which_Wheel = LorR;
    switch (which_Wheel) {
        case Enums::LEFT:
            startDig = leftWheel->getCount();
            break;
        case Enums::RIGHT:
            startDig = rightWheel->getCount();
            break;
        default:
            // 明らかにおかしいので、エラー処理
            msg_f("Turn_oneSide which_Wheel Error", 2);
            startDig =0;
          break;
    }
    // １周回って見つからなかったら終了。
    endDig = 360;
    // 前向き固定で！
    speed = abs(speed);
    till_color = color;    
    // param の処理。何に使うかは未定。
    // フラグを立てる。
    isToColor_mode = true;
}


float Turn_oneSide::decide_pwm_r(){
    switch (which_Wheel) {
        case Enums::LEFT:
            return 0;
        case Enums::RIGHT:
            return speed;
        default:
            // 明らかにおかしいので、エラー処理
            msg_f("", 2);
            msg_f("Turn_oneSide which_Wheel Error", 2);
            return 20;
    }
}

float Turn_oneSide::decide_pwm_l(){
    switch (which_Wheel) {
        case Enums::LEFT:
            return speed;
        case Enums::RIGHT:
            return 0;
        default:
            // 明らかにおかしいので、エラー処理
            msg_f("", 2);
            msg_f("Turn_oneSide which_Wheel Error", 2);
            return 20;
    }
}

bool Turn_oneSide::break_condition(){
    msg_f(leftWheel->getCount(), 2);
    // break condition なので。
    if (isToColor_mode) {
        // break条件：色
        return colorSensor->getColorNumber() == static_cast<int>(till_color);
    } else {
        // break条件：距離
        switch (which_Wheel) {
            case Enums::LEFT:
                return abs(leftWheel->getCount() - startDig) >= endDig;
            case Enums::RIGHT:
                return abs(rightWheel->getCount() - startDig) >= endDig;
            default:
                // 明らかにおかしいので、エラー処理
                msg_f("", 2);
                msg_f("Turn_oneSide which_Wheel Error", 2);
                return true;
        }
    }

}

