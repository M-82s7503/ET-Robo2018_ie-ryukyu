#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "clock.h"

#include "MoveUtil.h"

#define NONE 0    // 無し
#define BLACK 1   // 黒
#define BLUE 2    // 青
#define GREEN 3   // 緑
#define YELLOW 4  // 黄
#define RED 5     // 赤
#define WHITE 6   // 白

using namespace ev3api;


/* 駐車に関するクラス */
class Parking
{
public:
    Parking();
    void after_AI();
    void after_Block();

private:
    MoveUtil moveUtil;

};
