#include "raq_parcheesi.h"
#include <cassert>

const int RaqParcheesi::safePoint[RaqParcheesi::kSafePoints] = 
{5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68};
const int RaqParcheesi::startPoint[RaqParcheesi::kMaxPlayers] = 
{5, 22, 39, 56};
const int RaqParcheesi::finishPoint[RaqParcheesi::kMaxPlayers] = 
{68, 17, 34, 51};


RaqParcheesi* RaqParcheesi::Clone() const {
  return new RaqParcheesi{*this};
}

RaqParcheesi::RaqParcheesi(){
}

int RaqParcheesi::EntryBox(int player_index) const{
  return safePoint[player_index];
}

int RaqParcheesi::ExitBox(int player_index) const {
  return finishPoint[player_index];
}

int RaqParcheesi::PiecesAtHome(int player_index) const{
  int occupants;
  for(int i=0; i<PlayerData::kPieceNum; i++){
    if(player_[player_index].piece_[i].GetPosition()==0){
      occupants++;
    }
  }
  return occupants;
}

int RaqParcheesi::PiecesAtEnd(int player_index) const{
  int occupants;
  for(int i=0; i<PlayerData::kPieceNum; i++){
    if(player_[player_index].piece_[i].GetPosition()==76){
      occupants++;
    }
  }
  return occupants;
}

bool RaqParcheesi::IsBoxSafe(int box_index) const{
  for(int i=0; i<kSafePoints; i++){
    if(safePoint[i]==box_index){
      return true;
    }
  }
  return false;
}

void RaqParcheesi::SendPieceHome(int piece_index, int player_index){
  player_[player_index].piece_[piece_index].SetPosition(0);
}

IParcheesi::Color RaqParcheesi::ColorofPiece(int box_index, int box_piece_index) const{
  int player_in_box[2] = {0,0};
  int piece_turn[2] = {0,0};
  for(int i=0; i<kMaxPlayers; i++){
    for(int j=0; j<PlayerData::kPieceNum; j++){
      if(player_[i].piece_[j].GetPosition()==box_index){
        if(player_in_box[0]==0){
          player_in_box[0] = i;
          piece_turn[0] = player_[i].piece_[j].GetTurn();
        }else{
          assert(player_in_box[1] == 0 && "ERROR: MAS DE DOS FICHAS EN UN BOX");
          player_in_box[1] = i;
          piece_turn[1] = player_[i].piece_[j].GetTurn();
        }
      }
    }
  }
  if(player_in_box[1]==0) return static_cast<IParcheesi::Color>(player_in_box[0]);
  if(piece_turn[0]>piece_turn[1]){
    int a = piece_turn[0];
    piece_turn[0] = piece_turn[1];
    piece_turn[1] = a;
    a = player_in_box[0];
    player_in_box[0] = player_in_box[1];
    player_in_box[1] = a;
  }
  IParcheesi::Color player_color = 
  static_cast<IParcheesi::Color>(player_in_box[box_piece_index]);
  return player_color;
}



//----------------------------------------------

/*
bool RaqParcheesi::ChooseNextPiece(int roll_dice){
  bool piece_moved = false;
  for(int i=0; i<player_[player_index].kPieceNum && !piece_moved; i++){
    MovementOutput result = ApplyMovement(i, roll_dice);
    if(result!=kMovementOutput_NoMove){
      piece_moved = true;
    }
  }
  return piece_moved;
}
*/


int RaqParcheesi::CountPiecesOnBox(int box) const{
  int occupants = 0;
  for(int i = 0; i < kMaxPlayers; i++){
    for(int j=0; j<PlayerData::kPieceNum; j++){
      if(player_[i].piece_[j].GetPosition() == box){
        occupants++;
      }
    }
  }
  return occupants;
}


void RaqParcheesi::MovePiece(int pieceIndex, int target_box, int player_index){
  player_[player_index].piece_[pieceIndex].SetPosition(target_box);
  int turn = player_[player_index].piece_[pieceIndex].GetTurn();
  player_[player_index].piece_[pieceIndex].SetTurn(turn++);
}


void RaqParcheesi::EatPiece(int pieceIndex, int target_box, int player_index){
  for(int i = 0; i < kMaxPlayers; i++){
    int current_player = static_cast<int>(player_index);
    if(i != current_player){
      for(int j=0; j<PlayerData::kPieceNum; j++){
        // Eat piece
        if(player_[i].piece_[j].GetPosition() == target_box){
          player_[i].piece_[j].SetPosition(0);
          MovePiece(pieceIndex, target_box, player_index);
          // Add +20 to the dice.
          //ChooseNextPiece(20);
          return;
        }
      }
    }
  }
}


// Wraps the player's position around the board if they pass box 68.
// Only applies if the player hasn't yet entered the final stretch (69-76).
// After entering the final stretch, no wrap occurs.
int RaqParcheesi::AdjustPlayerPosition(int target_box, int current_box){
  int yellow_finish = finishPoint[static_cast<int>(IParcheesi::Color::Yellow)];
  if(current_box < yellow_finish && target_box > yellow_finish){
    return (target_box - finishPoint[static_cast<int>(IParcheesi::Color::Yellow)]);
  }
  return target_box;
}


// With the exception of the coloryellow (path which should not be modified
// because its final point is 68), it's calculated whether the players have 
// come all the way around and are going to go through their final point.
// If the condition it's true, then this function is called.
void RaqParcheesi::HandleFinalSectionEntry(int target_box, int pieceIndex, int player_index){
  // It's calculated how many boxes it has advanced within the 
  // final section.
  int diff = target_box - finishPoint[static_cast<int>(player_index)];
  
  // The position will be 68 plus the remaining boxes that had been
  // advanced within the final section (diff)
  int new_pos = finishPoint[static_cast<int>(IParcheesi::Color::Yellow)] + diff;
  player_[player_index].piece_[pieceIndex].SetPosition(new_pos);

  int turn = player_[player_index].piece_[pieceIndex].GetTurn();
  player_[player_index].piece_[pieceIndex].SetTurn(turn++);
}


bool RaqParcheesi::IsThereABridge(int current_box) const {
    if(CountPiecesOnBox(current_box)!=2) return false;
    if(ColorofPiece(current_box,0) == ColorofPiece(current_box,1)) return true;
    return false;
}

bool RaqParcheesi::IsThereABridge(int* box_list) const {
  for(int i= 0; i <20 ; i++) {
    if(box_list[i] == -1) return false;
    if(IsThereABridge(box_list[i])) return true;
  }
  return false;
}


// Aqui creo que se mueven las fichas y hay que revisar

bool RaqParcheesi::ChooseNextPiece(int roll_dice, int player_index){
  bool piece_moved = false;
  for(int i=0; i<player_[player_index].kPieceNum && !piece_moved; i++){
    MovementOutput result = ApplyMovement(i, roll_dice);
    if(result!=kMovementOutput_NoMove){
      piece_moved = true;
    }
  }
  return piece_moved;
}


/*

IParcheesi::Movement RaqParcheesi::ApplyMovement(int pieceIndex, int player_index, int count){
  int current_box = player_[player_index].piece_[pieceIndex].GetPosition();
  int target_box = current_box + count;
  int finish_yellow_point = finishPoint[static_cast<int>(IParcheesi::Color::Yellow)];

  bool bridge = IsThereABridge(current_box, target_box, finish_yellow_point);
  if(bridge) return IParcheesi::Movement::IllegalBridge;

  // Wrap around the board if necessary
  if(static_cast<IParcheesi::Color>(player_index) != IParcheesi::Color::Yellow){
    target_box = AdjustPlayerPosition(target_box, current_box);
  }
  // Check if the piece enters the final section (69-76)
  if(static_cast<IParcheesi::Color>(player_index) != IParcheesi::Color::Yellow){
    if(current_box < startPoint[static_cast<int>(player_index)] && 
    current_box <= finishPoint[static_cast<int>(player_index)] &&
    target_box > finishPoint[static_cast<int>(player_index)]){
      HandleFinalSectionEntry(target_box, pieceIndex, player_index);
      return IParcheesi::Movement::Normal; 
    }
  }
  // Movement of pieces depending on whether they are in the final stage or not
  int next_box_pieces = CountPiecesOnBox(target_box);
  if(target_box > finish_yellow_point){
    if(target_box > 76){
      return IParcheesi::Movement::IllegalPastEnd;
    }else if(target_box == 76){
      MovePiece(pieceIndex, target_box, player_index);
      ChooseNextPiece(10);
      return IParcheesi::Movement::End;
    }else{
      MovePiece(pieceIndex, target_box, player_index);
      return IParcheesi::Movement::Normal;
    }
  }else{
    if(next_box_pieces == 0){
      MovePiece(pieceIndex, target_box, player_index);
      return IParcheesi::Movement::Normal;
    }else if(next_box_pieces == 1){
      // Check if the box is a safe point
      for(int i=0; i<kSafePoints; i++){
        if(target_box == safePoint[i]){
          MovePiece(pieceIndex, target_box, player_index);
          return IParcheesi::Movement::Normal;
        }
      }
      if(player_[player_index].CountPiecesOnBox(target_box)==1){
        // Current player's piece. Make bridge
        MovePiece(pieceIndex, target_box, player_index);
        return IParcheesi::Movement::Normal;
      }else{
        // Another player's piece. Eat.
        EatPiece(pieceIndex, target_box, player_index);
        return IParcheesi::Movement::Eat;
      }
    }else if(next_box_pieces==2){
      // There is a bridge, the player cannot pass
      return IParcheesi::Movement::IllegalBridge;
    }
  }
}
*/


int* RaqParcheesi::ListMovementBoxes(int start, int count, int player_index) const {
  for(int i = 0; i != 20 ; i++) {
      boxlist[i] = -1;
  }
  return boxlist;

  int current = start;
  int index = 0;
  while(count > 0) {

    if(current == 76) break;
    if( current == finishPoint[player_index]) {
      current = 69;
    } else if(current == 68) {// Damos vueltas en el tablero
      current = 1;
    } else {
          current++;
    }
    boxlist[index] = current;
    index++;
    count--;
  }
  return boxlist;
}

bool RaqParcheesi::CanMove(int position, int count, int player_index) const {
  if( position == 0 ) {
    int startp = startPoint[player_index];
    if(IsThereABridge(startp)) {
      if(static_cast<int>(ColorofPiece(startp,0)) == player_index) {
        return false;
      }
    }
    return count == 5;
  }

  ListMovementBoxes(position,count,player_index);

  


}


IParcheesi::Movement RaqParcheesi::ApplyMovement(int pieceIndex, int player_index, int count){
  int current_box = player_[player_index].piece_[pieceIndex].GetPosition();

  // 

  int* box = ListMovementBoxes(current_box,count,player_index);

  if(IsThereABridge(box)) {
        return Movement::IllegalBridge;
  }

  // Ficha en casa

  // Ficha fuera

  // Caja llena

  
  int current_box = player_[player_index].piece_[pieceIndex].GetPosition();
  int target_box = current_box + count;
  int finish_yellow_point = finishPoint[static_cast<int>(IParcheesi::Color::Yellow)];


  bool bridge = IsThereABridge(current_box, count);
  if(bridge) return IParcheesi::Movement::IllegalBridge;

  // Wrap around the board if necessary
  if(static_cast<IParcheesi::Color>(player_index) != IParcheesi::Color::Yellow){
    target_box = AdjustPlayerPosition(target_box, current_box);
  }
  // Check if the piece enters the final section (69-76)
  if(static_cast<IParcheesi::Color>(player_index) != IParcheesi::Color::Yellow){
    if(current_box < startPoint[static_cast<int>(player_index)] && 
    current_box <= finishPoint[static_cast<int>(player_index)] &&
    target_box > finishPoint[static_cast<int>(player_index)]){
      HandleFinalSectionEntry(target_box, pieceIndex, player_index);
      return IParcheesi::Movement::Normal; 
    }
  }
  // Movement of pieces depending on whether they are in the final stage or not
  int next_box_pieces = CountPiecesOnBox(target_box);
  if(target_box > finish_yellow_point){
    if(target_box > 76){
      return IParcheesi::Movement::IllegalPastEnd;
    }else if(target_box == 76){
      MovePiece(pieceIndex, target_box, player_index);
      //ChooseNextPiece(10);
      return IParcheesi::Movement::End;
    }else{
      MovePiece(pieceIndex, target_box, player_index);
      return IParcheesi::Movement::Normal;
    }
  }else{
    if(next_box_pieces == 0){
      MovePiece(pieceIndex, target_box, player_index);
      return IParcheesi::Movement::Normal;
    }else if(next_box_pieces == 1){
      // Check if the box is a safe point
      for(int i=0; i<kSafePoints; i++){
        if(target_box == safePoint[i]){
          MovePiece(pieceIndex, target_box, player_index);
          return IParcheesi::Movement::Normal;
        }
      }
      if(player_[player_index].CountPiecesOnBox(target_box)==1){
        // Current player's piece. Make bridge
        MovePiece(pieceIndex, target_box, player_index);
        return IParcheesi::Movement::Normal;
      }else{
        // Another player's piece. Eat.
        EatPiece(pieceIndex, target_box, player_index);
        return IParcheesi::Movement::Eat;
      }
    }else if(next_box_pieces==2){
      // There is a bridge, the player cannot pass
      return IParcheesi::Movement::IllegalBridge;
    }
  }
}



//-----------------------------------------








int RaqPlayer::DecideMove(const IParcheesi& parcheesi, int current_player_index, int dice_roll) const{
  
  //RaqParcheesi* copia = parcheesi->Clone();
  
  IParcheesi::Movement result[4] =  ApplyMovement();
}