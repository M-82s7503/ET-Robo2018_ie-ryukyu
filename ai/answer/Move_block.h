#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "clock.h"
//#include "Moveutil_ai_block.h"
#include "Moveutil.h"

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
    MoveUtil moveutil;
    Motor leftWheel;
    Motor rightWheel;
    ColorSensor colorSensor;
//    TouchSensor touchSensor;
    Clock clock;
    int8_t answer[2][3];

    //int answer[2][3] =    {{0, 1, 1},{0, 1 ,0}};
    //int j;
    const int duration = 1300;
    const int sens_dist = 60;

public:
    Move_block(int8_t analyze_result[2][3]);
    void by_turn();
    void turn_case(int j);
    void Decision_Left(int i);
    void Decision_Right(int i);
    void through();
};
