#include "Color_recognition.hpp"

/* 初期化 */  
Color_recognition::Color_recognition():
  colorSensor(PORT_2) // センサのポート指定
{
  box = colorSensor.getColorNumber(); // 色を取得
}

// 何の色かを判別
void Color_recognition::GetColor()
{
  box = colorSensor.getColorNumber(); // 色を取得
}

// 判別した色をLCDに表示
int Color_recognition::OutputColor()
{

  box = colorSensor.getColorNumber(); // 色を取得

  return box;

}
