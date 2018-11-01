#include "Run_RL.hpp"


void Run_RL::calibration_L(Pointers* ptrs_p) {
    //###  Bluetooth を接続  ###//
    FILE *bt = setup_Bluetooth(clock);
    msg_f("-----<<<  Calibration  >>>-----",1);
    fprintf(bt, "-----<<<  Calibration  >>>-----\r\n");
        
    //###  PID ターゲット設定  ###//
    setup_PID_target(bt, clock);

    msg_clear();
    
    //###  リモートスタート  ###//
    remote_start(bt, clock, ptrs_p);
    //touch_start(clock, ptrs_p);
}


int Run_RL::calibration_R(Pointers* ptrs_p) {
    //###  Bluetooth を接続  ###//
    FILE *bt = setup_Bluetooth(clock);
    msg_f("-----<<<  Calibration  >>>-----",1);
    fprintf(bt, "-----<<<  Calibration  >>>-----\r\n");
        
    //###  PID ターゲット設定  ###//
    setup_PID_target(bt, clock);

    //###  初期位置コードを入力  ###//
    char message[MESSAGE_LEN + 1] = {0};
    char isInputComped = 'n';
    char ans_disp[64];
    while(1){
        // 受信
        // MESSAGE_LEN を超えないと、書き込まない仕組み。
        fprintf(bt, "\r\n初期位置コードを入力してください"); // エコーバック
        fprintf(bt, "\r\n入力しても表示されません。全部入力すると一括で表示されます。\r\n>>> "); // エコーバック
        int size = fread(message, 1, MESSAGE_LEN, bt);
        if(size > 0){
            fwrite(message, 1, size, bt); // エコーバック
        }
        msg_f(message, 3);

        msg_f("Is this code compleated ? waiting...", 4);
        fprintf(bt, "\r\n\r\nこれでいいですか (y/n)\r\n>>> "); // エコーバック
        // 受信
        isInputComped = (char) fgetc(bt);
        sprintf(ans_disp, " answer is : %c", isInputComped);
        msg_f(ans_disp, 5);
        if (isInputComped == 'y') {
            fprintf(bt, "\r\n初期位置コードを確定しました！\r\n\r\n "); // エコーバック
            break;
        }
    }
    msg_clear();
    
    //###  リモートスタート  ###//
    remote_start(bt, clock, ptrs_p);
    //touch_start(clock, ptrs_p);

    return atoi(message);
}


//###  Bluetooth を接続  ###//
FILE* Run_RL::setup_Bluetooth(Clock clock) {
    // 接続を確認（してなければスリープ）
    msg_f("Waiting for Bluetooth connecting ...",1);
    while(!ev3_bluetooth_is_connected()){
        clock.wait(300);
    }
    msg_f("Bluetooth connected !",1);
    // シリアルポートを開く
    FILE *bt = ev3_serial_open_file(EV3_SERIAL_BT);
    assert(bt != NULL);
    // Bluetooth仮想シリアルポートへの書き込むテスト
    fprintf(bt, "Bluetooth SPP ID: %d\r\n", EV3_SERIAL_BT);
    return bt;
}

//###  PID ターゲット設定  ###//
void Run_RL::setup_PID_target(FILE *bt, Clock clock) {

}

//###  アームの角度を初期化 → 調整  ###//
void Run_RL::remote_start(FILE *bt, Clock clock, Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    Move_Basic mv_basic(ptrs);
    mv_basic.resetArm();
    mv_basic.raiseArm(42, 30);
    msg_f("boot completed !",1);
    clock.wait(100);  //入れると安定した。

    //###  リモートスタート  ###//
    bool isStart = false;
    int8_t tmp_d;
    msg_f("-----  Waiting start ... -----", 1);
    fprintf(bt, "\r\n\r\n-----<<<  遠隔スタート  >>>-----");
    while(1) {
        msg_f(" input start (start : 1) : ", 3);
        fprintf(bt, "\r\n1：スタート\r\n>>>  ");
        // ここで入力されるまでブロックされるので注意
        tmp_d = fgetc(bt); // 受信
        switch(tmp_d) {
            case '1':
                isStart = true;
                break;
            default:
                break;
        }
        fputc(tmp_d, bt); // エコーバック
        if (isStart)
            break;
    }
    clock.wait(200);
    msg_clear();
    msg_f("     Start !", 3);
}

//###  タッチスタート  ###//
void Run_RL::touch_start(Clock clock, Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    TouchSensor* touchSensor = ptrs.getTouchSensor();
    while(1){
        if (touchSensor->isPressed()) {
            break;
        }
        clock.wait(10);
    }
    clock.wait(500);
}



void Run_RL::run_L(Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    Tracer tracer(ptrs);
    Move_Basic mv_basic(ptrs);
    // キャリブレーション
    tracer.calibration();
    // tracer のテスト
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2500);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 1500);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 1800);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 2000);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2300);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 1400);
    mv_basic.stop();
}


void Run_RL::run_R(Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    Tracer tracer(ptrs);
    Move_Basic mv_basic(ptrs);
    // キャリブレーション
    tracer.calibration();
    // tracer のテスト
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2150);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 5550);
    tracer.setParam(1);
    tracer.run(Enums::LEFT, 2300);
    tracer.setParam(0);
    tracer.run(Enums::LEFT, 2250);

    mv_basic.stop();

}
