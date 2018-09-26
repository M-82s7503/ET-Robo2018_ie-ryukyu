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
Move_block::Move_block():
  speed(20),leftWheel(PORT_C),rightWheel(PORT_B),colorSensor(PORT_2),touchSensor(PORT_1)
{
}

int aaaa[2][3] =    {{0, 1, 1},{0, 1 ,0}};
int j;
const int duration = 2000;
const int a = 45;



void Move_block::Decision_Left(int i)
{
	if(aaaa[0][j] == 0)
    {
            moveutil.turn(-45);
            moveutil.stop();
            moveutil.raiseArm(90, 20);//アームを上に動かす
            clock.sleep(duration);
            moveutil.turn(-45);
            moveutil.raiseArm(30, 20);//アームを下に動かす
            clock.sleep(duration);
            moveutil.to_color_turn(BLACK,180,0,40);
    }
        else if(aaaa[0][j] == 1)
        {
            moveutil.turn(45);
            moveutil.raiseArm(90, 10);//アームを上に動かす
            clock.sleep(duration);
            moveutil.turn(45);
            moveutil.raiseArm(30, 20);//アームを下に動かす
            clock.sleep(duration);
            moveutil.to_color_turn(BLACK,0,180,40);
        }
}

void Move_block::Decision_Right(int i)
{
	if(aaaa[1][j] == 0)
    {
            moveutil.turn(60);
            moveutil.raiseArm(90, 20);//アームを上に動かす
            clock.sleep(duration);
            moveutil.turn(-60);
            moveutil.raiseArm(30, 20);//アームを下に動かす
            clock.sleep(duration);
    }
        else if(aaaa[1][j] == 1)
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
            moveutil.raiseArm(30, 20);
            //moveutil.to_color(WHITE);
            moveutil.to_color(BLACK);
            moveutil.straight(a);
            moveutil.to_color_turn(BLACK,0,180,0);
            moveutil.stop();
            clock.sleep(duration);
            moveutil.straight(70);
            moveutil.turn(-90);
            moveutil.straight(30);
            moveutil.to_color(BLACK);
            moveutil.straight(a);
            moveutil.to_color_turn(BLACK,180,0,0);
            moveutil.stop();
            clock.sleep(duration);
            moveutil.to_color(BLUE);
            Decision_Right(j);
            break;
        case 1:
            moveutil.straight(-70);
            moveutil.turn(90);
            moveutil.to_color(BLACK);
            moveutil.stop();
            moveutil.straight(a);
            moveutil.to_color_turn(BLACK,180,0,0);
            moveutil.stop();
            moveutil.to_color(YELLOW);
            Decision_Right(j);
            break;
        case 2:
            moveutil.straight(-70);
            moveutil.turn(90);
            moveutil.to_color(BLACK);
            moveutil.stop();
            moveutil.straight(a);
            moveutil.to_color_turn(BLACK,180,0,0);
            moveutil.stop();
            moveutil.to_color(RED);
            Decision_Right(j);
            break;       
    }
}


void Move_block::by_turn()
{
    turn_case(0);
    turn_case(1);
    turn_case(2);
    moveutil.straight(-130);
    moveutil.turn(90);
}

void Move_block::through()
{
Pointers pt_s(&leftWheel, &rightWheel, &colorSensor, &touchSensor);
Tracer tracer(pt_s);
    moveutil.raiseArm(30, 20);
    moveutil.to_color(WHITE);
    moveutil.to_color(BLACK);
    moveutil.straight(a);
    moveutil.to_color_turn(BLACK,0,180,0);
    moveutil.straight(30);
    moveutil.turn(-90);
    moveutil.straight(30);
    moveutil.to_color(BLACK);
    moveutil.straight(a);
    moveutil.to_color(BLACK);
    moveutil.straight(a);
    moveutil.to_color(BLACK);
    moveutil.turn(90);
    moveutil.to_color(BLACK);
    moveutil.straight(a);
    moveutil.turn(-90);
    moveutil.straight(50);
}
