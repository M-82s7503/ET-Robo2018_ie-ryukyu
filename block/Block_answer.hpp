#include "ColorSensor.h"

#include "Enums.h"
#include "MoveUtil.h"

//#include "Map.hpp"
#include "Map_Move.hpp"
#include "Code_Solve.hpp"

using namespace ev3api;

class Block_answer {
  public:
    Block_answer();
    void run();

  private:
    ColorSensor colorSensor; // 色のセンサ
    MoveUtil tai;
    Code_Solve code;

    const int code_num = 84722;
    int solve_num[5];

};
