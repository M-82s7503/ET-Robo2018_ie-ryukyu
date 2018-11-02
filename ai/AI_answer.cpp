#include "AI_answer.hpp"


AI_answer::AI_answer():
    clock()
{
    // アナログ数字の読み取り結果を保存する配列を初期化
    init_arr_all0(num_img_digital, 7);
    init_arr_all0(num_img_analog, 15);
}

void AI_answer::init_arr_all0(int* arr, int arr_size) {
    // sizeofで要素数を調べる
    if (arr_size <= 0) return;
    for(int i=0; i < arr_size; ++i){
      // 0で初期化
      arr[i] = 0;
    }
}
void AI_answer::init_arr_all0(float* arr, int arr_size) {
    // sizeofで要素数を調べる
    if (arr_size <= 0) return;
    for(int i=0; i < arr_size; ++i){
      // 0で初期化
      arr[i] = 0;
    }
}
void AI_answer::init() {
    init_f("AI_answer");
}
void AI_answer::terminate() {
    msg_f("AI_answer compleated.", 1);
}



// 【動き】 デジタル数字カード
void AI_answer::readImg_digital(Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);

    Move_Basic mv_basic(ptrs);
    Straight straight(ptrs);
    Turn_oneSide turn_oneSide(ptrs);
    Turn turn(ptrs);
    MoveTemps moveTemps(ptrs);

    float read_speed = 20;
    Reading_seg8 reading_digital(ptrs, read_speed, num_img_digital);

//    int whites[2] = {Enums::WHITE, Enums::GREY};

    // 数字画像まで移動
    mv_basic.raiseArm(30, 30);
    mv_basic.stop();
    straight.run(Enums::FRONT, until_greenMat);
    //msg_f("AI_answer to_color(Enums::WHITE);", 1);
    moveUtil.to_color( static_cast<int>(Enums::WHITE) );
//    straight.run(Enums::Colors::BLACK, Enums::Directs::FRONT, 500);

    //msg_f("AI_answer 8seg", 1);
    //###  8の字走行  ###//
    //--  <1> 横・上側  --//
    // 開始位置に移動
    moveUtil.turn(-90);
    // 位置合わせ：黒まで戻る。
    turn_oneSide.run(Enums::LEFT, 90);
    straight.setBase_PWM(10);
    straight.run(Enums::Directs::BACK, 80);
//    straight.run(Enums::Colors::BLACK, Enums::Directs::BACK, 10);
    mv_basic.stop();
    moveUtil.to_color( static_cast<int>(Enums::Colors::WHITE) );
//    mv_basic.stop();
    // テスト待ち
//    straight.run(Enums::Colors::BLACK, Enums::Directs::FRONT,30);

// 旧版
//    turn_oneSide.run(Enums::LEFT, -90);
//    straight.run(Enums::FRONT, tate_4-tire_dist+10);  // 数字の3分の1の長さ
//    turn_oneSide.run(Enums::LEFT, 90);
    // 読み取り実行
    reading_digital.run(0, yoko_2);
    reading_digital.run(1, yoko_2);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。

    //--  <2> 横・下側  --//
    // 開始位置に移動
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  // 一旦マットに出る。
    mv_basic.stop();
    straight.run(Enums::FRONT, sensor_dist);
    mv_basic.stop();
    turn_oneSide.run(Enums::RIGHT, 180);  // 白が見えるまで回転。
    mv_basic.stop();
    // (未テスト) ズレ調整
    straight.run(Enums::Directs::FRONT, 30);
    mv_basic.stop();
    moveTemps.ride_onLine_vertical(Enums::Colors::BLACK, Enums::Directs::LEFT);
    mv_basic.stop();
    // 読み取り実行
    reading_digital.run(2, yoko_2);
    reading_digital.run(3, yoko_2);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。


    //--  <3> 縦  --//
    // 開始位置に移動
    // 1回転
    moveUtil.setSpeed(10);
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  // 一旦マットに出る。
    mv_basic.stop();
//    moveUtil.turn(90+10);     // [確認] ズレように値を調整した。
    turn.run(Enums::Directs::RIGHT, 90);
    // 2回転
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );
    turn_oneSide.run(Enums::LEFT, 180);
    mv_basic.stop();
    straight.run(Enums::BACK, sensor_dist*1.5);
    //moveUtil.to_color( static_cast<int>(Enums::WHITE) );  // 多分、ここまでは行かない。
    moveTemps.ride_onLine_vertical(Enums::Colors::BLACK, Enums::Directs::RIGHT);

    // 読み取り実行
    reading_digital.run(4, img_size_tate*2/5);
    reading_digital.run(5, img_size_tate*1/5);
    reading_digital.run(6, img_size_tate*2/5);
    //straight.run(Enums::FRONT, img_size_tate);


    //--  <+α> digital で終わる場合  --//
    // カード上側
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  //一旦マットに出る
    straight.run(Enums::Directs::FRONT, sensor_dist-15);
    // カード上側 → カード左側
    turn.to_color_turn(Enums::Colors::WHITE, Enums::Directs::LEFT, 120);
    turn.run(Enums::LEFT, 5);  // 確実に、白の枠内に入る。
    mv_basic.stop();
    // カード左側（アナログもやる場合は、こっちもやる）
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  //一旦マットに出る
    straight.run(Enums::Directs::FRONT, sensor_dist-15);
    // カード左側 → カード下側
    turn.to_color_turn(Enums::Colors::WHITE, Enums::Directs::LEFT, 120);
    turn.run(Enums::LEFT, 5);  // 確実に、白の枠内に入る。
    mv_basic.stop();
    moveUtil.to_color(Enums::Colors::BLACK);

    // 右に黒を探しに行く。そこでズレ修正。
    turn.run(Enums::Directs::RIGHT, 100);
    moveUtil.to_color(Enums::Colors::BLACK);
    straight.run(Enums::Directs::FRONT, sensor_dist/2);
    moveTemps.ride_onLine_vertical(Enums::Colors::WHITE, Enums::LEFT);
    straight.run(Enums::Directs::BACK, sensor_dist/3);
    turn.run(Enums::Directs::LEFT, 90);
    // マットに出て終了。
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );
    straight.run(Enums::Directs::FRONT, sensor_dist/2);
    mv_basic.stop();

    //--  log 出力  --//
    reading_digital.f_write();

    //--  パターンマッチで、カードの数字を予想  --//
    PatternMatcher ptMatch;
    ptMatch.solve_D(num_img_digital);

    // 回答を 2進数に変換した上で、analyze_result に書き込む。
    int8_t divd_tmp = ptMatch.getAns_D();
    int8_t rank_tmp = -1;
    for (int8_t idx=2; idx>=0; idx--) {
        rank_tmp = divd_tmp % 2;
        // 2^0 の位は、一番奥（最後）なので、
        // 最初の余りは、配列の一番最後に入る。
        analyze_result[0][idx] = rank_tmp;
        divd_tmp /= 2;
    }

}




// 【動き】 アナログ数字カード
void AI_answer::readImg_analog(Pointers* ptrs_p) {
    Pointers ptrs(ptrs_p);
    
    Move_Basic mv_basic(ptrs);
    Straight straight(ptrs);
    Turn_oneSide turn_oneSide(ptrs);

    float read_speed = 20;
    Reading_return3 reading_analog(ptrs, read_speed, num_img_analog, analog_size_tate);
    

    // 数字画像まで移動
    // 一旦マットに出る。
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );
    //  ↘︎
    turn_oneSide.run(Enums::LEFT, -90);
    //  ← (アナログ画像のとこまで)
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  // デジタル画像 -> マット
    moveUtil.to_color( static_cast<int>(Enums::WHITE) );  // マット -> アナログ画像


    /**  3return 走行  **/
    //--  1 return  --//
    // 開始位置に移動
    straight.run(Enums::FRONT, sensor_dist);
    moveUtil.turn(90);
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );
    straight.run(Enums::FRONT, sensor_dist+10);
    moveUtil.turn(-90);
    moveUtil.to_color_turn(Enums::WHITE, 15, 15, 10);  // ズレを修正。回る向きは指定したい。
    straight.run(Enums::FRONT, img_yohaku_yoko + analog_size_yoko/6);  // 余白 上側
    moveUtil.turn(-90);
    straight.run(Enums::FRONT, img_yohaku_tate - sensor_dist);  // 余白 上側
    // 読み取り実行
    reading_analog.run(1);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。

// 未
    //--  <2> 横・下側  --//
    // 開始位置に移動
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  // 一旦マットに出る。
    turn_oneSide.run(Enums::RIGHT, 90);
    straight.run(Enums::FRONT, tate_4/2);  // ［確認］いらないかも？
    turn_oneSide.run(Enums::RIGHT, Enums::WHITE);  // 白が見えるまで回転。
    // 読み取り
    // 読み取り実行
    reading_analog.run(2);
    //straight.run(Enums::FRONT, img_size_yoko);  // 動きだけテスト で使う。


    //--  <3> 縦  --//
    // 開始位置に移動
    moveUtil.to_color( static_cast<int>(Enums::BLACK) );  // 一旦マットに出る。
    turn_oneSide.run(Enums::LEFT, 90);
    // ［確認］この辺で ライントレース入れる？
    straight.run(Enums::FRONT, tate_4*1.5);  // 数字の3分の1の長さ

    turn_oneSide.run(Enums::LEFT, 90);
    // ［確認］この辺で ライントレース入れる？
    straight.run(Enums::FRONT, img_size_yoko/2);

    turn_oneSide.run(Enums::LEFT, 90);
    moveUtil.to_color( static_cast<int>(Enums::WHITE) );

    // 読み取り実行
    reading_analog.run(3);
    straight.run(Enums::FRONT, img_size_tate);

    mv_basic.stop();


    reading_analog.f_write();

}





void AI_answer::answer_forBlock() {
    Move_block mv_block(analyze_result);
//    mv_block.through();
    mv_block.by_turn();
}



