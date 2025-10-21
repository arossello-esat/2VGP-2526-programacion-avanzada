#pragma once
#ifndef PARCHEESI_IPARCHEESI_H
#define PARCHEESI_IPARCHEESI_H

class IParcheesi {
  public:
    enum class Color {
      Yellow,
      Blue,
      Red,
      Green,
      None,
    };

    enum class Movement {
      Eat,
      End,
      ReachExit,
      Normal,
      NoMoves,
      IllegalPass,
      IllegalBridge,
      IllegalBoxFull,
      IllegalPastEnd,
      IllegalEntryBlocked,
      IllegalPieceAtHome,
      IllegalMustEnterPiece,
      IllegalMustBreakBridge,
    };

    const static int board_size = 68;
    const static int exit_size = 8;
    const static int null_piece = -1;

    virtual int EntryBox(int player_index) const = 0;
    virtual int ExitBox(int player_index) const = 0;
    virtual int PiecesAtHome(int player_index) const = 0;
    virtual int PiecesAtEnd(int player_index) const = 0;
    virtual bool IsBoxSafe(int box_index) const = 0;
    virtual Color ColorofPiece(int box_index, int piece_index) const = 0;

    virtual Movement ApplyMovement(int piece_index, int count) = 0;
    virtual void SendPieceHome(int piece_index) = 0;

    virtual ~IParcheesi() = default;
};

#endif // PARCHEESI_IPARCHEESI_H