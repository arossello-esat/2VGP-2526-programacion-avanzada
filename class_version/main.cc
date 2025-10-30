#include "raq_parcheesi.h"
#include "game.h"

int main(){
  RaqParcheesi myp;

  RaqPlayer player1;
  RaqPlayer player2;
  RaqPlayer player3;
  RaqPlayer player4;

  const IPlayer* players[4]={&player1,&player2,&player3,&player4};
  Game g{myp,players};

  while(g.IsGameOver() == IParcheesi::Color::None){
    g.PlayTurn();
  }

  return 0;
}

