#include "Parking.h"
#include "moveUtil.h"


Parking::Parking() //初期化
    : moveUtil()
 // leftWheel(PORT_C), rightWheel(PORT_B)
{
    /*
      speed = 15;
      pwm = (Motor::PWM_MAX)/6;
    */
}

void Parking::after_Block() //ブロック並べ後
{
    moveUtil.raiseArm(25, 20);
    moveUtil.straight(90);
    moveUtil.to_color(BLACK);
    moveUtil.straight(60);
    moveUtil.stop();
    moveUtil.to_color_turn(BLACK, 180, 0, 0);
    //moveUtil.turn(10);
    moveUtil.straight(600);

//moveUtil.to_color_turn(BLACK, 180, 30);
}

void Parking::after_AI() //AIアンサー後
{
    moveUtil.raiseArm(30, 20);
    moveUtil.to_color_turn(BLACK, 45, 45, 0);
    moveUtil.turn(-30);
    moveUtil.straight(100);
    moveUtil.to_color(BLACK);
    moveUtil.straight(350);
    moveUtil.turn(30);
}