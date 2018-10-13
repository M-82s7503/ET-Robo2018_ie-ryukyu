#include "Map_Move.hpp"

/* 初期化 */
Map_Move::Map_Move()
{
  car_x = 0;
  car_y = 2;
  car_degree = 0;

  int i,j;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      block[i][j] = NO_EXIST;
    }
  }
/**/
  map_color[0][0] = RED;
  map_color[0][1] = YELLOW;
  map_color[0][2] = BLUE;
  map_color[0][3] = GREEN;

  map_color[1][0] = BLUE;
  map_color[1][1] = GREEN;
  map_color[1][2] = RED;
  map_color[1][3] = YELLOW;

  map_color[2][0] = RED;
  map_color[2][1] = YELLOW;
  map_color[2][2] = BLUE;
  map_color[2][3] = GREEN;

  map_color[3][0] = BLUE;
  map_color[3][1] = GREEN;
  map_color[3][2] = RED;
  map_color[3][3] = YELLOW;

}

/* (暗号の解読結果から)ブロックの初期配置を計算する */
void Map_Move::block_jud(int code_solve[5])
{
  int count;
  int x,y;

  for(count = 0; count < N; count++){
    y = code_solve[count]/4;
    x = code_solve[count] - y * 4;
    block[y][x] = BEFORE_MOVE_BLOCK;
  }

}

/* 運ぶブロックの優先順位を決める */
void Map_Move::priority_move(int* move_x,int* move_y,int block[N][N])
{
  int i,j;
  int box,distance;

  distance = 100;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){

      if(block[i][j] == BEFORE_MOVE_BLOCK){
        box = abs(i - car_y)+ abs(j - car_x);
        if(distance > box){
          *move_y = i;
          *move_x = j;
          distance = box;
        }
      }

    }
  }

}

/* ブロックを移動させる座標を決定する */
void Map_Move::move_point(int block_color,int* move_x,int* move_y,int block[N][N]) {
  int i,j;
  int box,distance;

  distance = 100;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){

      if(map_color[i][j] == block_color){
        box = abs(i - car_y)+ abs(j - car_x);
        if(distance > box){
          *move_y = i;
          *move_x = j;
          distance = box;
        }
      }

    }
  }
}
