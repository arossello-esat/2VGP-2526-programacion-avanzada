#include "player.h"

const int Player::kPieceNum = 4;

Player::Player(Colors color)
  : color_{color}
  , piece_{0,0,0,0}{
}

bool Player::PiecesAtHome() const{
  if(CountPiecesOnBox(0) != 0){
    return true;
  }
  return false;
}

int Player::CountPiecesOnBox(int box) const{
  int occupants = 0;
  for(int i = 0; i < kPieceNum; i++){
    if(piece_[i].position == box){
      occupants++;
    }
  }
  return occupants;
}
