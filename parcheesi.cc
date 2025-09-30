#include "parcheesi.h"

const int Parcheesi::safePoint[kSafePoints] = {5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68};
const int Parcheesi::startPoint[kMaxPlayers] = {5, 22, 39, 56};
const int Parcheesi::finishPoint[kMaxPlayers] = {68, 17, 34, 51};

Parcheesi::Parcheesi(int num_players)
  : num_players_{num_players}
  , current_turn_{0}
  , repeated_sixes_{0}
  , last_piece_{-1}
  , current_player_{kColor_Yellow}
  , player_{kColor_Yellow,kColor_Blue,kColor_Red,kColor_Green}{
}

const Player& Parcheesi::CurrentPlayer() const{
    return player_[static_cast<int>(current_player_)];
}

Player& Parcheesi::CurrentPlayer(){
    return player_[static_cast<int>(current_player_)];
}

int Parcheesi::CountPiecesOnBox(int box) const{
  int occupants = 0;
  for(int i = 0; i < num_players_; i++){
    occupants += player_[i].CountPiecesOnBox(box);
  }
  return occupants;
}

void Parcheesi::NextPlayer(){
  int num_player = static_cast<int>(current_player_);
  num_player = (num_player + 1) % num_players_;
  current_player_ = static_cast<Colors>(num_player);
}
