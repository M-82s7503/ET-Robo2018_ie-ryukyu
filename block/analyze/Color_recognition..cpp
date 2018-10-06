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
  box = colorSensor.getColorNumber(); 
  switch(box){
  case NONE:
    msg_f("None...", 1); // LCDに出力
    break;
  case BLACK:
    msg_f("Black!!", 1); // LCDに出力
    break;
  case BLUE:
    msg_f("Blue!!", 1); // LCDに出力
    break;
  case GREEN:
    msg_f("Greeeeeen!!", 1); // LCDに出力
    break;
  case YELLOW:
    msg_f("Yello!!", 1); // LCDに出力
    break;
  case RED:
    msg_f("Red!!", 1); // LCDに出力
    break;
  case WHITE:
    msg_f("White!!", 1); // LCDに出力
    break;
  default:
    break;
  }

  return box;

}
