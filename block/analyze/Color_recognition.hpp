#include "ColorSensor.h"

#include "util.h"
#include "Enums.h"

using namespace ev3api;

/* 色に関するクラス */
class Color_recognition{
private:
  colorid_t box; // 色 
  ColorSensor colorSensor; // 色のセンサ
public:
  Color_recognition();
  void GetColor();
  int OutputColor();
};
