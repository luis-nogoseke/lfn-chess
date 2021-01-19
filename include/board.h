#ifndef H_BOARD_H
#define H_BOARD_H

#include <memory>
#include <sstream>
#include <string>

#include "bitboard.h"

class Board {
 private:
  // White
  std::unique_ptr<PawnBitboard> white_pawns;
  std::unique_ptr<KnightBitboard> white_knights;
  std::unique_ptr<BishopBitboard> white_bishops;
  std::unique_ptr<RookBitboard> white_rooks;
  std::unique_ptr<QueenBitboard> white_queen;
  std::unique_ptr<KingBitboard> white_king;

  // Black
  std::unique_ptr<PawnBitboard> black_pawns;
  std::unique_ptr<KnightBitboard> black_knights;
  std::unique_ptr<BishopBitboard> black_bishops;
  std::unique_ptr<RookBitboard> black_rooks;
  std::unique_ptr<QueenBitboard> black_queen;
  std::unique_ptr<KingBitboard> black_king;

  Color next_move;
  bool white_short_castle;
  bool white_long_castle;
  bool black_short_castle;
  bool black_long_castle;
  uint8_t moves_50;
  uint8_t total_moves;

 public:
  Board()
      : next_move(Color::WHITE),
        white_short_castle(true),
        white_long_castle(true),
        black_short_castle(true),
        black_long_castle(true),
        moves_50(0U),
        total_moves(0U),
        white_pawns(std::make_unique<PawnBitboard>(Color::WHITE)),
        white_knights(std::make_unique<KnightBitboard>(Color::WHITE)),
        white_bishops(std::make_unique<BishopBitboard>(Color::WHITE)),
        white_rooks(std::make_unique<RookBitboard>(Color::WHITE)),
        white_queen(std::make_unique<QueenBitboard>(Color::WHITE)),
        white_king(std::make_unique<KingBitboard>(Color::WHITE)),
        black_pawns(std::make_unique<PawnBitboard>(Color::BLACK)),
        black_knights(std::make_unique<KnightBitboard>(Color::BLACK)),
        black_bishops(std::make_unique<BishopBitboard>(Color::BLACK)),
        black_rooks(std::make_unique<RookBitboard>(Color::BLACK)),
        black_queen(std::make_unique<QueenBitboard>(Color::BLACK)),
        black_king(std::make_unique<KingBitboard>(Color::BLACK)) {}

  std::string fen() {
    std::stringstream ss;
    // Pieces

    // next to play
    if (next_move == Color::WHITE) {
      ss << " w";
    } else {
      ss << " b";
    }

    // Castling
    ss << " ";
    if (white_short_castle) {
      ss << "K";
    }
    if (white_long_castle) {
      ss << "Q";
    }
    if (black_short_castle) {
      ss << "k";
    }
    if (black_long_castle) {
      ss << "q";
    }
    if (!(white_short_castle || white_long_castle || black_short_castle ||
          black_long_castle)) {
      ss << "-";
    }

    // en passant
    ss << " -";

    // move counter 50 moves rule
    ss << " ";
    ss << std::to_string(moves_50);

    // total moves
    ss << " ";
    ss << std::to_string(total_moves);

    return ss.str();
  };

  inline Color next_to_move() { return this->next_move; }
  inline bool can_white_short_castle() { return this->white_short_castle; }
  inline bool can_white_long_castle() { return this->white_long_castle; }
  inline bool can_black_short_castle() { return this->black_short_castle; }
  inline bool can_black_long_castle() { return this->black_long_castle; }
  inline uint8_t get_moves() { return this->moves_50; }
  inline uint8_t get_total_moves() { return this->total_moves; }

  uint8_t get_pieces_score(Color color) {
    if (color == Color::WHITE) {
      return white_pawns->population() + white_knights->population() * 3 +
             white_bishops->population() * 3 + white_rooks->population() * 5 +
             white_queen->population() * 9;
    } else {
      return black_pawns->population() + black_knights->population() * 3 +
             black_bishops->population() * 3 + black_rooks->population() * 5 +
             black_queen->population() * 9;
    }
  }
};

#endif /* H_BOARD_H */