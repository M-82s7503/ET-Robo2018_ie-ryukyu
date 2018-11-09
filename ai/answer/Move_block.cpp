#include "Move_block.h"

/*
    Motor leftWheel;
    Motor rightWheel;
    ColorSensor colorSensor;
    TouchSensor touchSensor;
  
  ここまでMove_blockのヘッダーに書く


Pointers pt_s(&leftWheel, &rightWheel, &colorSensor, &touchSensor);
Tracer tracer(pt_s);
実際に使う時に書く

宣言できたら
tracer.run(Enum::LEFT, 350); これで実装できる
tracer.stop();
（線の左側を350の距離進む）
*/

/* 初期化 */
Move_block::Move_block(int8_t analyze_result[2][3])
    //:leftWheel(PORT_C),rightWheel(PORT_B),colorSensor(PORT_2)//,touchSensor(PORT_1)
{
    for (int i=0; i<2; i++) {
        for (int j=0; j<3; j++) {
            // ダミーデータでやるならコメントアウトする。
            answer[i][j] = analyze_result[i][j];
        }
    }
}


//<<<  上側が 1, 下側が 0  >>>//
// 読み取りの順序の関係で、
//      0:digital,  1:analog
// で実装してるので、逆になる。
// digital(0) なら 0 が 左(-), 1 が 右(+)
// analog(1) なら  1 が 左(-), 0 が 右(+)
//    =>  analog/digital と 値 が同じなら-、違うなら+。
void Move_block::shift_block(int8_t i_ad, int8_t i_place) {
    moveutil.setSpeed(8);
    moveutil.to_color( static_cast<int>(block_colors[i_ad][i_place]) );

    int8_t direct_sign = 1;
    if (i_ad == answer[i_ad][i_place]) {
        direct_sign = -1;
    }
    moveutil.turn(direct_sign*60);
    moveutil.raiseArm(90, 20);//アームを上に動かす
    //clock.sleep(duration);
    moveutil.turn(-direct_sign*60);
    moveutil.raiseArm(30, 20);//アームを下に動かす
    //clock.sleep(duration);

    moveutil.setSpeed(12);
    moveutil.straight(-70);
    moveutil.stop();
}
/*
void Move_block::Decision_Analog(int j)
{
	if(answer[0][j] == 0) {
        moveutil.turn(-45);
        moveutil.stop();
        moveutil.raiseArm(90, 20);//アームを上に動かす
        clock.sleep(duration);
        moveutil.turn(-45);
        moveutil.raiseArm(30, 20);//アームを下に動かす
        clock.sleep(duration);
        moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),180,0,40);

    } else if (answer[0][j] == 1) {
        moveutil.turn(45);
        moveutil.raiseArm(90, 10);//アームを上に動かす
        clock.sleep(duration);
        moveutil.turn(45);
        moveutil.raiseArm(30, 20);//アームを下に動かす
        clock.sleep(duration);
        moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),0,180,40);

    }
}

void Move_block::Decision_Digital(int j)
{
	if(answer[1][j] == 0)
    {
            moveutil.turn(60);
            moveutil.raiseArm(90, 20);//アームを上に動かす
            //clock.sleep(duration);
            moveutil.turn(-60);
            moveutil.raiseArm(30, 20);//アームを下に動かす
            //clock.sleep(duration);
            moveutil.straight(-70);

            moveutil.turn(90);
            moveutil.stop();
    }
        else if(answer[1][j] == 1)
        {
            moveutil.turn(-60);
            moveutil.raiseArm(90, 20);//アームを上に動かす
            clock.sleep(duration);
            moveutil.turn(60);
            moveutil.raiseArm(30, 20);//アームを下に動かす
            clock.sleep(duration);
        }
}*/

/*
void Move_block::turn_case(int j)
{
    switch(j)
    {
        case 0:
            moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),0,180,0);
            moveutil.stop();
            clock.sleep(duration);
            moveutil.straight(70);
            moveutil.turn(-90);
            moveutil.straight(30);
            moveutil.to_color(static_cast<int>( Enums::BLACK ));
            moveutil.straight(sensor_dist);
            moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),180,0,0);
            moveutil.stop();
            clock.sleep(duration);
            moveutil.to_color(BLUE);
            Decision_Digital(j);
            break;
        case 1:
            moveutil.straight(-70);
            moveutil.turn(90);
            moveutil.to_color(static_cast<int>( Enums::BLACK ));
            moveutil.stop();
            moveutil.straight(sensor_dist);
            moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),180,0,0);
            moveutil.stop();
            moveutil.to_color(static_cast<int>( Enums::YELLOW ));
            Decision_Digital(j);
            break;
        case 2:
            moveutil.straight(-70);
            moveutil.turn(90);
            moveutil.to_color(static_cast<int>( Enums::BLACK ));
            moveutil.stop();
            moveutil.straight(sensor_dist);
            moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),180,0,0);
            moveutil.stop();
            moveutil.to_color(static_cast<int>( Enums::RED ));
            Decision_Digital(j);
            break;       
    }
}*/


void Move_block::next_line(Pointers pt_s, Move_Basic mv_basic, Turn turn) {
    // 左回転して、黒じゃなければ繰り返す。
    while ( pt_s.getColorSensor()->getColorNumber() != static_cast<int>(Enums::Colors::BLACK)) {
        moveutil.to_color(static_cast<int>( Enums::BLACK ));
        mv_basic.stop();
        //================     追加した。未検証。検証必要。     ===================//
        moveutil.straight( line_width/3 );
        turn.run(Enums::Directs::LEFT, 10);
        mv_basic.stop();
        clock.wait(300);
    }
    turn.run(Enums::Directs::RIGHT, 10);
    // ＜曲がる動き＞
    moveutil.straight(sensor_dist+line_width*2/3+15);  //少しだけ前に出る
    moveutil.turn(-80);
    turn.run(Enums::Directs::LEFT, Enums::Colors::BLACK);
    mv_basic.stop();
}

// デジタル側のみ、移動させるパターン
void Move_block::by_turn(Pointers pt_s)
{
    // 永田のおかげで、試走会の時間内にはなんとか目処はたった！

    //Tracer tracer(pt_s);
    //tracer.setParam(Enums::PID::Midium);
    Turn_oneSide turn_oneSide(pt_s);
    Turn turn(pt_s);
    Move_Basic mv_basic(pt_s);
    MoveTemps moveTemps(pt_s);
    moveutil.setSpeed(15);
    
    // 数字画像（マットに出たところ） -> 最初の線
    moveutil.raiseArm(30, 20);
    //moveutil.to_color(Enums::WHITE);
    moveutil.straight(sensor_dist);
    moveutil.to_color(static_cast<int>( Enums::WHITE ));
    moveutil.straight(sensor_dist);
    mv_basic.stop();
    // 【最初の横線】
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    mv_basic.stop();
    clock.wait(1000);

    // ライントレースでデジタル側へ？
    // → 【中央縦線】
    moveutil.straight(180);  // 車体が入りきるスペースに入る
    moveutil.turn(-90);
    moveutil.stop();
    moveutil.to_color(static_cast<int>( Enums::BLACK ));  // 到着
    // 【digital 1つ目】の方向に向く
    //turn_oneSide.run(Enums::Directs::LEFT, 90);
    moveutil.straight( (sensor_dist+line_width)/2.3 );
    mv_basic.stop();
    moveTemps.ride_onLine_vertical(Enums::Colors::BLACK, Enums::Directs::LEFT);  // 垂直にする
    moveutil.stop();
    moveutil.straight( sensor_dist *moveTemps.getRCos() + 20 );
    turn.run(Enums::Directs::RIGHT, 85);

    // 【digital 1つ目】
    next_line(pt_s, mv_basic, turn);
    // ブロックの方向を向いた状態 → ブロックを移動後元の位置に戻る。
    shift_block(0, 0);
    moveutil.turn(90);
    moveutil.stop();

    // 【digital 2つ目】
/*    moveutil.to_color(static_cast<int>( Enums::WHITE ));
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.straight(line_width*2);*/
    next_line(pt_s, mv_basic, turn);
    // ブロックの方向を向いた状態 → ブロックを移動後元の位置に戻る。
    shift_block(0, 1);
    moveutil.turn(90);
    moveutil.stop();


    // 【digital 3つ目】
    next_line(pt_s, mv_basic, turn);
    // ブロックの方向を向いた状態 → ブロックを移動後元の位置に戻る。
    shift_block(0, 1);
    moveutil.straight(-50);  // 車体が入りきるスペースに入る(バック)
    moveutil.turn(90);
    moveutil.stop();

/* 
    // 線に着いた時点 → 次の線に移動する動作 まで
    moveutil.straight(sensor_dist);
    turn.to_color_turn(Enums::Colors::BLACK, Enums::Directs::LEFT, 90);
    tracer.run(Enums::RIGHT, block_colors[0][0]);
    Decision_Digital(0);
    tracer.run(Enums::LEFT, 70);
    moveutil.turn(-90);
    moveutil.stop();
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
*/
/*
    //turn_case(0);
    turn_case(1);
    turn_case(2);
    moveutil.straight(-130);
    moveutil.turn(90);
*/
}

// ブロックを移動せず、素通りするパターン
void Move_block::through()
{
    moveutil.raiseArm(30, 20);
    moveutil.to_color(static_cast<int>( Enums::WHITE ));
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.straight(sensor_dist);
    moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),0,180,0);
    moveutil.straight(30);
    moveutil.turn(-90);
    moveutil.straight(30);
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.straight(sensor_dist);
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.straight(sensor_dist);
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.turn(90);
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.straight(sensor_dist);
    moveutil.turn(-90);
    moveutil.straight(50);
}
