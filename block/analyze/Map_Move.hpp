#include "Enums.h"
#include <cstdlib>

#define N 4


/* Map関するクラス */
class Map_Move {
  public:
    Map_Move();
    void block_jud(int solove_num[5]);  // 暗号よりブロックの初期配置の計算                                           
    void priority_move(int* move_x,int* move_y,int block[N][N]); // 運ぶブロックの優先順位を決める
    void move_point(int block_color,int* move_x,int* move_y,int block[N][N]); // ブロックを移動させる座標を決定する

  public:
    /* mapに関する定数 */
    enum {
        NO_EXIST,
        BEFORE_MOVE_BLOCK,
        AFTER_MOVE_BLOCK
    };

    int block[N][N]; //block exist                                                                                    
    int map_color[N][N]; //map color                                                                                  
    int car_x,car_y;
    int move_x,move_y;
    int car_degree;

};
