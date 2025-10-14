#include "player.h"

enum MovementOutput{
  kMovementOutput_BasicMove = 0,
  kMovementOutput_NoMove,
  kMovementOutput_Eat,
  kMovementOutput_Illegal,
  kMovementOutput_End
};

struct Parcheesi{
  static const int kMaxPlayers = 4;
  static const int kSafePoints = 12; 
  static const int kBoxNum = 68;

  static const int safePoint[kSafePoints];
  static const int startPoint[kMaxPlayers];
  static const int finishPoint[kMaxPlayers];
  
  int num_players_;
  int current_turn_;

  Colors current_player_;   
  PlayerData player_[kMaxPlayers];

  Parcheesi(int num_players);

  int CountPiecesOnBox(int box) const;
  void NextPlayer();
  void PlayTurn();
  MovementOutput ApplyMovement(int pieceIndex, int mov_num);
};

int DecideMovement(const Parcheesi& p) {
  p.CountPiecesOnBox(1);
  p.NextPlayer();
}

class Matrix {
  public:
    void Multiply(float v);
    bool IsSquared() const;

};

int globala = 0;

class Unit {
  float x, y, rotation;
  Matrix transform;
  mutable bool dirty;
  public:

  void ChangeDirection(float d) {
    rotation = d;
    dirty = true;
  }

  Matrix& GetMatrix();
  const Matrix& GetMatrix(Player&p ) const;
 
// 1 Afecta al tipo apuntado(Matrix)
// 2 Afecta al puntero(Matrix *)
// 3 Cambia this a const this

//  1             2                    3
  const Matrix* const GetTransform() const {
    int a = 1;
    globala = 1;
    a++;
    if(dirty) {
      dirty = false;
      this->transform.Multiply(rotation);
    }
    return &(this->transform);
  }


};

int bla() {
  const Unit u;
  Matrix transformn = u.GetTransform();
}

