#include "MoveUtil.h"
#include "Enums.h"

/* 動きに関する宣言 */
#define DELTA_T 0.004
#define KP 1.34
#define KI 4.46
#define KD 0.167

class MoveUtil_Block : public MoveUtil {
  
public:
  MoveUtil_Block();
  // ブロック並べ 用の動き
  void purpose_move(int* car_x,int* car_y,int move_x,int move_y,int* car_degree,int block[4][4],int color[4][4],int handdegree);
  void back_move(int car_degree,int* car_x,int* car_y);
  float block_pid(int8_t sensor_val,int8_t target_val);
  void pid_straight(int distance);
  // 非推奨：MoveUtil で実装してしまった + ズレる可能性があるため、使わないように。
  void hand_move(int jud);
  void back(int distance); // mm戻るプログラム
  
private:
  Motor handWheel;    
  Clock clock;
  int diff[2];
  float intergral;
  int8_t target_val;
  int8_t sensor_val;
  int8_t control_speed;
  uint32_t E_time;
};
