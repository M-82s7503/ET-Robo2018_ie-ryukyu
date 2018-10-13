#include "MoveUtil.h"
#include "Map.hpp"
#include <cstdlib>

#define N 4


/* Map関するクラス */
class Map_Move {
  public:
    Map_Move(Map* map_p);
    void priority_move(); // 移動させるブロックの優先順位を決める
    void move_point(int block_color); // ブロックを移動させる座標を決定する
    // ブロック並べ 用の動き
    void purpose_move(int deg);
    void purpose_move(int mv_x, int mv_y, int deg);
    void back_move();

  public:
    int car_x, car_y;
    int move_x, move_y;
    int car_degree;

  private:
    Map* map;
    MoveUtil mvUtil;
};
