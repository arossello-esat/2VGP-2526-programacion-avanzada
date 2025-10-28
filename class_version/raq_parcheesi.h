#pragma once
#ifndef MOCK_PARCHEESI_H
#define MOCK_PARCHEESI_H

#include "game.h"

class Piece{
  private:
    int position_;
    int turn_;
  public:
    Piece() : position_{0}, turn_{0} {} 
    void SetPosition(int pos){position_ = pos;}
    int GetPosition() const {return position_;}

    void SetTurn(int turn){turn_ = turn;}
    int GetTurn() const {return turn_;}
    ~Piece() = default;
};

class PlayerData{
  public:
    static const int kPieceNum = 4;     
    PlayerData() : color_{IParcheesi::Color::None}{}
    IParcheesi::Color color_;
    Piece piece_[kPieceNum];
    ~PlayerData() = default;
};


class RaqParcheesi : public IParcheesi {
  public:
  RaqParcheesi();

  // RaqParcheesi(const RaqParcheesi& other);
  static const int kMaxPlayers = 4;
  static const int kSafePoints = 12; 
  static const int kBoxNum = 68;
  
  static const int safePoint[kSafePoints];
  static const int startPoint[kMaxPlayers];
  static const int finishPoint[kMaxPlayers];
  
  int EntryBox(int player_index) const override;
  int ExitBox(int player_index) const override;
  int PiecesAtHome(int player_index) const override;
  int PiecesAtEnd(int player_index) const override;
  bool IsBoxSafe(int box_index) const override;
  Color ColorofPiece(int box_index, int box_piece_index) const override;
  
  Movement ApplyMovement(int piece_index, int player_index, int count) override;
  void SendPieceHome(int piece_index, int player_index) override;

  virtual RaqParcheesi* Clone() const;

  
  
  private:
   void MovePiece(int piecendex, int target_box, int player_index);
  void EatPiece(int pieceIndex, int target_box, int player_index);
  int AdjustPlayerPosition(int target_box, int current_box);
  void HandleFinalSectionEntry(int target_box, int pieceIndex, int player_index);
  int CountPiecesOnBox(int box) const;
  bool IsThereABridge(int* box_list) const;
  bool IsThereABridge(int current_box) const;
  bool ChooseNextPiece(int roll_dice, int player_index);
  
  int* ListMovementBoxes(int start, int count, int player_index) const;
  bool CanMove(int start, int count, int player_index) const;


  PlayerData player_[kMaxPlayers];

  mutable int boxlist[20];
};




class RaqPlayer : public IPlayer{
  virtual int DecideMove(const IParcheesi& parcheesi, int current_player_index, int dice_roll) const override;
};


#endif // MOCK_PARCHEESI_H