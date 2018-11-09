#include "Tracer.hpp"
//#include "MoveUtil.h"
#include "Move_Basic.hpp"
#include "TouchSensor.h"

using namespace ev3api;

class Run_RL {
  public:
    void calibration_L(Pointers* ptrs_p);
    int calibration_R(Pointers* ptrs_p);
    void calibration_touch(Pointers* ptrs_p, bool isSetupPID);
    // Rコースの走行
    void run_R(Pointers* ptrs_p, bool isRemoteStart);
    // Lコースの走行
    void run_L(Pointers* ptrs_p, bool isRemoteStart);

  private:
    // Bluetooth の初期設定
    void setup_Bluetooth();
    // アームの初期設定
    void setup_Arm(Pointers ptrs);
    // PID の target の値を修正
    void setup_PID(Pointers ptrs);
    // Start：リモートスタート と タッチスタートの２種類
    void remote_start(Pointers ptrs);
    void touch_start(Pointers ptrs);
    // 初期位置コードの桁数を入力する。

    const int8_t MESSAGE_LEN = 5;
    Clock clock;
    int8_t white_val = -1, 
            black_val = -1;
    FILE *bt;
};
