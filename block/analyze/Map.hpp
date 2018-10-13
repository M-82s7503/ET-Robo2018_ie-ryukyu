#include "Enums.h"
#define N 4


/* Map関するクラス */
class Map {
  public:
    Map();
    void block_jud(int solove_num[5]);  // 暗号よりブロックの初期配置の計算     

  public:
    // 定数配列として初期化する場合。
    const int colors[N][N] = {
        {RED, YELLOW, BLUE, GREEN},
        {BLUE, GREEN, RED, YELLOW},
        {RED, YELLOW, BLUE, GREEN},
        {BLUE, GREEN, RED, YELLOW}
    };
    int blocks[N][N]; //block exist
};
