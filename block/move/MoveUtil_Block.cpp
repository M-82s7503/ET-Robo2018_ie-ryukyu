#include "MoveUtil_Block.hpp"


//初期化
MoveUtil_Block::MoveUtil_Block():
    MoveUtil(), handWheel(PORT_A)
{
  // ブロック並べ pid 系の変数
  sensor_val = colorSensor.getBrightness();
  target_val = 11;
}


/**
 *  ブロック並べに必要な動き
 */

//指定の距離進む                                                                                                                                                       
void MoveUtil_Block::back(int distance){
  startLeftDig = leftWheel.getCount();
  endLeftDig = startLeftDig - (distance * 9 / 8);

  while (1) {
    msg_f("straight...", 1);
    leftWheel.setPWM(-speed);
    rightWheel.setPWM(-speed);

    //終了判定。前進しているか後進しているかで分岐
    if(distance >=0){
        if (leftWheel.getCount() <= endLeftDig){
          leftWheel.stop();
          rightWheel.stop();
          break;
        }
    }else{
        if (leftWheel.getCount() >= endLeftDig){
          leftWheel.stop();
          rightWheel.stop();
          break;
        }
    }
  }
}


/* ブロック並べの際のpid制御 */
float MoveUtil_Block::block_pid(int8_t sensor_val,int8_t target_val){
  float p, i, d;

  diff[0] = diff[1];
  diff[1] = sensor_val - target_val;
  intergral += (diff[1] + diff[0]) / 2.0*DELTA_T;

  p = KP * diff[1];
  i = KI * intergral;
  d = KD * (diff[1] - diff[0]) / DELTA_T;

  return p+d;
}

//指定の距離進む                                                                                                                                                                             
void MoveUtil_Block::pid_straight(int distance){
  E_time = distance * 4.7;
  clock.reset();

  while (1) {
    sensor_val = colorSensor.getBrightness();
    control_speed = block_pid(sensor_val,target_val);
    leftWheel.setPWM(speed+control_speed);
    rightWheel.setPWM(speed-control_speed);

    if (clock.now() >= E_time){
      leftWheel.stop();
      rightWheel.stop();
      break;
    }
  }
}


/* 引数によって機体のハンドを動かす */
void MoveUtil_Block::hand_move(int jud){

  while(1){
    if(jud != 0){
      if(jud == 1){
        handWheel.setPWM(2);
        if(handWheel.getCount() > 100){
          handWheel.stop();
          break;
        }
      }else if(jud == -1){
        handWheel.setPWM(-2);
        if(handWheel.getCount() < -10){
          handWheel.stop();
          break;
        }
      }
    }
  }
  
}
