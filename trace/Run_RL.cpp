#include "Run_RL.hpp"


void Run_RL::calibration_L(Pointers* ptrs_p) {
    //###  Bluetooth を接続  ###//
    setup_Bluetooth();
    msg_f("-----<<<  Calibration  >>>-----",1);
    fprintf(bt, "\r\n\r\n-----<<<  Calibration  >>>-----\r\n");
    
    Pointers ptrs(ptrs_p);
    //###  アームの角度を初期化 → 調整  ###//
    setup_Arm(ptrs);
    clock.wait(200);
    //###  PID ターゲット設定  ###//
    setup_PID(ptrs);
    clock.wait(200);  //入れると安定した。
}


int Run_RL::calibration_R(Pointers* ptrs_p) {
    //###  Bluetooth を接続  ###//
    setup_Bluetooth();
    msg_f("-----<<<  Calibration  >>>-----",1);
    fprintf(bt, "-----<<<  Calibration  >>>-----\r\n");
        
    //###  初期位置コードを入力  ###//
    char message[MESSAGE_LEN + 1] = {0};
    char isInputComped = 'n';
    char ans_disp[64];
    while(1){
        // 受信
        // MESSAGE_LEN を超えるまで、書き込まない仕組み。
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

    Pointers ptrs(ptrs_p);
    //###  アームの角度を初期化 → 調整  ###//
    setup_Arm(ptrs);
    clock.wait(200);
    //###  PID ターゲット設定  ###//
    setup_PID(ptrs);
    clock.wait(200);  //入れると安定した。

    return atoi(message);
}


void Run_RL::calibration_touch(Pointers* ptrs_p, bool isSetupPID) {
    //msg_f("-----<<<  Calibration  >>>-----",1);
    Pointers ptrs(ptrs_p);
    //###  アームの角度を初期化 → 調整  ###//
    setup_Arm(ptrs);
    clock.wait(200);
    //###  PID ターゲット設定  ###//
    white_val = 20;
    black_val = 0;
    if (isSetupPID) {
        setup_PID(ptrs);
        clock.wait(200);  //入れると安定した。
    }
}

//###  Bluetooth を接続  ###//
void Run_RL::setup_Bluetooth() {
    // 接続を確認（してなければスリープ）
    msg_f("Waiting for Bluetooth connecting ...",1);
    while(!ev3_bluetooth_is_connected()){
        clock.wait(300);
    }
    msg_f("Bluetooth connected !",1);
    // シリアルポートを開く
    bt = ev3_serial_open_file(EV3_SERIAL_BT);
    assert(bt != NULL);
    // Bluetooth仮想シリアルポートへの書き込むテスト
    fprintf(bt, "\r\nBluetooth SPP ID: %d\r\n", EV3_SERIAL_BT);
}

//###  アームの角度を初期化 → 調整  ###//
void Run_RL::setup_Arm(Pointers ptrs) {
    Move_Basic mv_basic(ptrs);

    mv_basic.resetArm();
    mv_basic.raiseArm(42, 30);
}

//###  PIDパラメータ のセットアップ  ###//
void Run_RL::setup_PID(Pointers ptrs) {
    msg_f("---<<<  Calibration PID  >>>---",0);
    //fprintf(bt, "\r\n\r\n-----<<<  Calibration PID  >>>-----\r\n");

    ColorSensor* colorSensor = ptrs.getColorSensor();
    msg_f("BLACK  ( <- Left Button )", 1);
    msg_f(black_val, 3);
    msg_f("WHITE  ( -> Right Button )", 3);
    msg_f(white_val, 5);
    msg_f("Enter  ( Enter Button )", 5);
    while (1) {
        if (ev3_button_is_pressed(LEFT_BUTTON)) {
            black_val = colorSensor->getBrightness();
            msg_f(black_val, 2);
            //fprintf(bt, "Black val : %d\r\n", black_val);
        } else if (ev3_button_is_pressed(RIGHT_BUTTON)) {
            white_val = colorSensor->getBrightness();
            msg_f(white_val, 4);
            //fprintf(bt, "White val : %d\r\n", white_val);
        } else if (ev3_button_is_pressed(DOWN_BUTTON)) {
            int target_val = 11;
            float coefficient = Tracer::coefficient;
            float sensor_average = (white_val + black_val) /2;
            target_val = sensor_average * coefficient + target_val * (1- coefficient);
            msg_f(target_val, 6);
        }
        if ( ev3_button_is_pressed(ENTER_BUTTON) ) {
            break;
        }
        clock.wait(50);
    }
    msg_clear();
}


//###  リモートスタート  ###//
void Run_RL::remote_start(Pointers ptrs) {
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
void Run_RL::touch_start(Pointers ptrs) {
    TouchSensor* touchSensor = ptrs.getTouchSensor();
    msg_f("----  Waiting toutch start ... ----", 1);
    while(1){
        if (touchSensor->isPressed()) {
            break;
        }
        clock.wait(20);
    }
    clock.wait(500);
}



void Run_RL::run_L(Pointers* ptrs_p, bool isRemoteStart) {
    Pointers ptrs(ptrs_p);
    Move_Basic mv_basic(ptrs);
    Tracer tracer(ptrs);
    // キャリブレーション（計算）
    tracer.calibration(white_val, black_val);
    tracer.setLowpassValue();

    //###  スタート  ###//
    if (isRemoteStart) {
        remote_start(ptrs);  // リモート スタート
    } else {
        touch_start(ptrs);  // タッチ スタート
    }

    //###  ライントレース  ###//
/*
    tracer.setParam(Enums::PID::Fast);
    tracer.run(Enums::LEFT, 2500);
    tracer.setParam(Enums::PID::Midium);
    tracer.run(Enums::LEFT, 1500);
    tracer.setParam(Enums::PID::Fast);
    tracer.run(Enums::LEFT, 1800);
    tracer.setParam(Enums::PID::Midium);
    tracer.run(Enums::LEFT, 2000);
    tracer.setParam(Enums::PID::Fast);
    tracer.run(Enums::LEFT, 2300);
*/
    tracer.setParam(Enums::PID::Midium);
    tracer.run(Enums::LEFT, 1000);

/*
    tracer.setParam(Enums::PID::Slow);
    tracer.run(Enums::LEFT, 300);
*/
    mv_basic.stop();
}


void Run_RL::run_R(Pointers* ptrs_p, bool isRemoteStart) {
    Pointers ptrs(ptrs_p);
    Move_Basic mv_basic(ptrs);
    Tracer tracer(ptrs);
    // キャリブレーション（計算）
    tracer.calibration(white_val, black_val);
    tracer.setLowpassValue();

    //###  スタート  ###//
    if (isRemoteStart) {
        remote_start(ptrs);  // リモート スタート
    } else {
        touch_start(ptrs);  // タッチ スタート
    }

    //###  ライントレース  ###//
    tracer.setParam(Enums::PID::Fast);
    tracer.run(Enums::LEFT, 2150);
    tracer.setParam(Enums::PID::Midium);
    tracer.run(Enums::LEFT, 5550);
    tracer.setParam(Enums::PID::Fast);
    tracer.run(Enums::LEFT, 2300);
    tracer.setParam(Enums::PID::Midium);
    tracer.run(Enums::LEFT, 2250);

    mv_basic.stop();
}
