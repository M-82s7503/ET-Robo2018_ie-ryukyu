#include "Tracer.hpp"
//#include "MoveUtil.h"
#include "Move_Basic.hpp"
#include "TouchSensor.h"

using namespace ev3api;

class Run_RL {
  public:
    void calibration_L(Pointers* ptrs_p);
    int calibration_R(Pointers* ptrs_p);
    // Rコースの走行
    void run_R(Pointers* ptrs_p);
    // Lコースの走行
    void run_L(Pointers* ptrs_p);

    // Bluetooth の初期設定
    FILE* setup_Bluetooth(Clock clock);
    // PID の target の値を修正
    void setup_PID_target(FILE *bt, Clock clock);
    // Start  リモートスタート と タッチスタートの２種類
    void remote_start(FILE *bt, Clock clock, Pointers* ptrs_p);
    void touch_start(Clock clock, Pointers* ptrs_p);

  private:
    // 初期位置コードの桁数を入力する。
    const int8_t MESSAGE_LEN = 4;
    Clock clock;

};
