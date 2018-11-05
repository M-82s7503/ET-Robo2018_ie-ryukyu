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
Move_block::Move_block(int8_t analyze_result[2][3]):
  leftWheel(PORT_C),rightWheel(PORT_B),colorSensor(PORT_2)//,touchSensor(PORT_1)
{
    for (int i=0; i<2; i++) {
        for (int j=0; j<3; j++) {
            answer[i][j] = analyze_result[i][j];
        }
    }
}



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
            clock.sleep(duration);
            moveutil.turn(-60);
            moveutil.raiseArm(30, 20);//アームを下に動かす
            clock.sleep(duration);

            moveutil.turn(-180);
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
}

void Move_block::turn_case(int j)
{
    switch(j)
    {
        case 0:
            /*moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),0,180,0);
            moveutil.stop();
            clock.sleep(duration);
            moveutil.straight(70);
            moveutil.turn(-90);
            moveutil.straight(30);*/
            moveutil.to_color(static_cast<int>( Enums::BLACK ));
            moveutil.straight(sens_dist);
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
            moveutil.straight(sens_dist);
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
            moveutil.straight(sens_dist);
            moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),180,0,0);
            moveutil.stop();
            moveutil.to_color(static_cast<int>( Enums::RED ));
            Decision_Digital(j);
            break;       
    }
}


// デジタル側のみ、移動させるパターン
void Move_block::by_turn(Pointers pt_s)
{
    Tracer tracer(pt_s);
    tracer.setParam(Enums::PID::Midium);
    Turn_oneSide turn_oneSide(pt_s);
    Turn turn(pt_s);
    Move_Basic mv_basic(pt_s);
    moveutil.setSpeed(15);
    
    // 数字画像（マットに出たところ） -> 最初の線
    moveutil.raiseArm(30, 20);
    //moveutil.to_color(Enums::WHITE);
    moveutil.straight(sens_dist);
    moveutil.to_color(static_cast<int>( Enums::WHITE ));
    moveutil.straight(sens_dist);
    mv_basic.stop();
    clock.wait(1000);
    // 最初の太線
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    mv_basic.stop();
    clock.wait(1000);

    // ライントレースでデジタル側へ？
    //tracer.setParam(Enums::PID::Midium);
    //tracer.run(Enums::LEFT, );

    // to_color で行ってみる。
    moveutil.straight(sens_dist*2);
    moveutil.turn(-90);
    moveutil.stop();
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    turn_oneSide.run(Enums::Directs::LEFT, 90);
    mv_basic.stop();
    moveutil.to_color(static_cast<int>( Enums::BLACK ));

    // 線に着いた時点 → 次の線に移動する動作 まで
    moveutil.straight(sens_dist);
    turn.to_color_turn(Enums::Colors::BLACK, Enums::Directs::LEFT, 90);
    tracer.run(Enums::RIGHT, block_colors[0][0]);
    Decision_Digital(0);
    tracer.run(Enums::LEFT, 70);
    moveutil.turn(-90);
    moveutil.stop();
    moveutil.to_color(static_cast<int>( Enums::BLACK ));

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
    moveutil.straight(sens_dist);
    moveutil.to_color_turn(static_cast<int>( Enums::BLACK ),0,180,0);
    moveutil.straight(30);
    moveutil.turn(-90);
    moveutil.straight(30);
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.straight(sens_dist);
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.straight(sens_dist);
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.turn(90);
    moveutil.to_color(static_cast<int>( Enums::BLACK ));
    moveutil.straight(sens_dist);
    moveutil.turn(-90);
    moveutil.straight(50);
}
