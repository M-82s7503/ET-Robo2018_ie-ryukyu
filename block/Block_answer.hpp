#include "Map_Move.hpp"
#include "MoveUtil.h"
#include "Color_recognition.hpp"
#include "Code_Solve.hpp"

using namespace ev3api;

class Block_answer {
  public:
    void run();

  private:
    Map_Move map;
    MoveUtil tai;
    Color_recognition color;
    Code_Solve code;

    const int code_num = 84722;
    int solve_num[5];

};
