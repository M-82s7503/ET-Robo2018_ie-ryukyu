#include "Run_RL.hpp"


void Run_RL::calibration_L(Pointers* ptrs_p) {
    //###  Bluetooth を接続  ###//
    FILE *bt = setup_Bluetooth(clock);
    msg_f("-----<<<  Calibration  >>>-----",1);
    fprintf(bt, "\r\n\r\n-----<<<  Calibration  >>>-----\r\n");
        
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
        
    //###  初期位置コードを入力  ###//
    char message[MESSAGE_LEN + 1] = {0};
    char isInputComped = 'n';
    char ans_disp[64];
    while(1){
        // 受信
        // MESSAGE_LEN を超えないと、書き込まない仕組み。
        fprintf(bt, "\r\n初期位置コードを入力してください"); // エコーバック
        fprintf(bt, "\r\n(入力しても数字は表示されません。全部入力すると一括で表示されます。)\r\n>>> ");
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
            fprintf(bt, "\r\n初期位置コードを確定しました！\r\n"); // エコーバック
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
    fprintf(bt, "\r\nBluetooth SPP ID: %d\r\n", EV3_SERIAL_BT);
    return bt;
}

//###  PIDパラメータ のセットアップ  ###//
void Run_RL::setup_PID(Clock clock, Pointers ptrs) {
    msg_f("---<<<  Calibration PID  >>>---",1);
    //fprintf(bt, "\r\n\r\n-----<<<  Calibration PID  >>>-----\r\n");

    ColorSensor* colorSensor = ptrs.getColorSensor();
    msg_f("BLACK  ( <- Left Button )", 2);
    msg_f(black_val, 3);
    msg_f("WHITE  ( -> Right Button )", 4);
    msg_f(white_val, 5);
    msg_f("Enter  ( Enter Button )", 6);
    while (1) {
        if (ev3_button_is_pressed(LEFT_BUTTON)) {
            black_val = colorSensor->getBrightness();
            msg_f(black_val, 3);
            //fprintf(bt, "Black val : %d\r\n", black_val);
        } else if (ev3_button_is_pressed(RIGHT_BUTTON)) {
            white_val = colorSensor->getBrightness();
            msg_f(white_val, 5);
            //fprintf(bt, "White val : %d\r\n", white_val);
        }
        if ( ev3_button_is_pressed(ENTER_BUTTON) ) {
            break;
        }
        clock.wait(50);
    }
    
    // ライントレース の キャリブレーション
    //tracer.calibration(white_val, black_val);
    msg_clear();
}

//###  アームの角度を初期化 → 調整  ###//
//###  リモートスタート  ###//
void Run_RL::remote_start(FILE *bt, Clock clock, Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    Move_Basic mv_basic(ptrs);

    mv_basic.resetArm();
    mv_basic.raiseArm(42, 30);
    msg_f("boot completed !",1);
    clock.wait(100);

    //###  PID ターゲット設定  ###//
    setup_PID(clock, ptrs);
    clock.wait(200);  //入れると安定した。

    // 1 を押してスタート
    int8_t tmp_d;
    msg_f("-----  Waiting start ... -----", 1);
    fprintf(bt, "\r\n\r\n-----<<<  遠隔スタート  >>>-----");
    while(1) {
        msg_f(" input start (start : 1) : ", 3);
        fprintf(bt, "\r\n1：スタート\r\n>>>  ");
        // ここで入力されるまでブロックされるので注意
        tmp_d = fgetc(bt); // 受信
        msg_f(tmp_d, 4);
        fputc(tmp_d, bt); // エコーバック
        if (tmp_d == '1')
            break;
    }
    clock.wait(100);
    msg_clear();
    msg_f("     Start !", 3);
}

//###  タッチスタート  ###//
// 一応残してる。もしもの時のため。
void Run_RL::touch_start(Clock clock, Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    TouchSensor* touchSensor = ptrs.getTouchSensor();
    Move_Basic mv_basic(ptrs);

    mv_basic.resetArm();
    mv_basic.raiseArm(42, 30);
    msg_f("boot completed !",1);
    clock.wait(100);

    //###  PID ターゲット設定  ###//
    setup_PID(clock, ptrs);
    clock.wait(200);  //入れると安定した。

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
    tracer.calibration(white_val, black_val);
    // ライントレース
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
    tracer.run(Enums::LEFT, 1000);

    mv_basic.stop();
}


void Run_RL::run_R(Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    Tracer tracer(ptrs);
    Move_Basic mv_basic(ptrs);
    // キャリブレーション
    tracer.calibration(white_val, black_val);
    // ライントレース
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
