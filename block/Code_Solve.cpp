#include "Code_Solve.hpp"

Code_Solve::Code_Solve(){
  num = 0;
  count = 0;
}

void Code_Solve::Solve(int solve_num[5],int firstvalue){

  while(count < 5){
    if(firstvalue < num * pow(16,4-count)){
      solve_num[count] = num-1;
      firstvalue -= (num-1)*pow(16,4-count);
      num = 0;
      count++;
    }else{
      num++;
    }
  }

}
