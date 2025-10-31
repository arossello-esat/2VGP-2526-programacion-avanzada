#include "mock_parcheesi.h"
#include "game.h"
#include "playerpaco.h"

int main(){
  MockParcheesi myp;

  MockPlayer player1;
  MockPlayer player2;
  PlayerPaco player3;
  
  const IPlayer* players[4]={&player1,nullptr,&player2,&player3};
  Game g{myp,players};

  while(g.IsGameOver() == IParcheesi::Color::None){
    g.PlayTurn();
  }

  return 0;
}

