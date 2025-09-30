#include "parcheesi.h"

#include <stdlib.h>
#include <time.h>

int RollDice(){
  static bool initialize = true;
  if(initialize)[[unlikely]]{
    srand(time(NULL));
    initialize=false;
  }
  return (rand() % 6) + 1;
}

int main(){
  Parcheesi parchis{4};
  int repeated_sixes = 0;
  int turn = 0;
  int last_piece = -1;
  const int reroll_result = 6;
  const int max_rerolls = 3;

  do{
      Player& cp = parchis.CurrentPlayer();
      int dice_roll = RollDice();
      if(dice_roll == reroll_result) {
        repeated_sixes++;
        if(repeated_sixes == max_rerolls) {
            repeated_sixes = 0;
            if(last_piece != -1){
              cp.piece_[last_piece] = {0,turn};
            }
            parchis.NextPlayer();
            continue;
        }
      }

      int piece_index = parchis.SelectMove(dice_roll);
      int result = parchis.ApplyMovement(piece_index,dice_roll);
      if(result != kMovementOutput_NoMove) {
        last_piece = piece_index;
      }
      if(dice_roll != reroll_result) parchis.NextPlayer();
  }while(!parchis.GameWon());

  return 0;
}
