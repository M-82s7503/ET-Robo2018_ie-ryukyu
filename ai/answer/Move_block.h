#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "clock.h"
#include "Moveutil_ai_block.h"

#define NONE 0    // 無し
#define BLACK 1   // 黒
#define BLUE 2    // 青
#define GREEN 3   // 緑
#define YELLOW 4  // 黄
#define RED 5     // 赤
#define WHITE 6   // 白

using namespace ev3api;



/* ブロックを動かす*/
class Move_block
{
private:
    MoveUtil_ai_block moveutil;
    Motor leftWheel;
    Motor rightWheel;
    ColorSensor colorSensor;
    TouchSensor touchSensor;
    Clock clock;
    int speed;
public:
    Move_block();
    void by_turn();
    void turn_case(int j);
    void Decision_Left(int i);
    void Decision_Right(int i);
    void through();
};
