#include "ev3.h"
#include "app.h"
#include "util.h"

#include "Motor.h"
#include "Port.h"
#include "ColorSensor.h"

using namespace ev3api;

class MoveUtil{
private:
  Motor leftWheel;
  Motor rightWheel;
  Motor handWheel;
  ColorSensor colorSensor;
  int speed;
  int pwm;
  int32_t startDig;//開始時の角位置
  int32_t endDig;//終了角位置
  bool rightSearch;
public:
  MoveUtil();
  void turn(int degree);
  void turn(int degree,int side);
  void straight(int distance);
  void stop();
  void to_color(int color);
  int to_color_turn(int color);

  // ブロック並べ 用の動き
  void back(int distance); // mm戻るプログラム
  void purpose_move(int* car_x,int* car_y,int move_x,int move_y,int* car_degree,int block[4][4],int handdegree);
  void back_move(int car_degree,int* car_x,int* car_y);
};
