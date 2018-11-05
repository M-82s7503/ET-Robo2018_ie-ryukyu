#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "clock.h"
//#include "Moveutil_ai_block.h"
#include "Moveutil.h"

#include "MoveTemps.hpp"
#include "Tracer.hpp"


#include "Enums.h"
/*
#define NONE 0    // 無し
#define BLACK 1   // 黒
#define BLUE 2    // 青
#define GREEN 3   // 緑
#define YELLOW 4  // 黄
#define RED 5     // 赤
#define WHITE 6   // 白
*/
using namespace ev3api;



/* ブロックを動かす*/
class Move_block
{
private:
/*    Motor leftWheel;
    Motor rightWheel;
    ColorSensor colorSensor;
//    TouchSensor touchSensor;
*/
    MoveUtil moveutil;
    Clock clock;
    // もしもの時のために、ダミーデータを用意？(笑)
    int8_t answer[2][3] = {
        {0, 1, 1},  // digital
        {0, 1 ,0}   // analog
    };

    const int duration = 600;
    const int sensor_dist = 35;

    // [0:digital, 1:analog][行数]
    const Enums::Colors block_colors[2][3] = {
        {Enums::Colors::BLUE, Enums::Colors::YELLOW, Enums::Colors::RED},
        {Enums::Colors::RED, Enums::Colors::GREEN, Enums::Colors::RED}
    };

    // 計測数値
    int8_t line_width = 20;  // 線の幅（2cm）

public:
    Move_block(int8_t analyze_result[2][3]);
    void by_turn(Pointers pt_s);
    void turn_case(int j);
    void Decision_Analog(int i);
    void Decision_Digital(int i);
    void through();
};
