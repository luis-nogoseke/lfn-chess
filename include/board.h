#ifndef H_BOARD_H
#define H_BOARD_H

#include <cstdint>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "bitboard.h"
#include "utils.h"

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
  std::uint8_t castling_rights;
  uint8_t moves_50;
  uint8_t total_moves;
  uint8_t en_passant;

 public:
  Board()
      : next_move(Color::WHITE),
        white_short_castle(true),
        white_long_castle(true),
        black_short_castle(true),
        black_long_castle(true),
        moves_50(0U),
        total_moves(0U),
        castling_rights(15U),
        en_passant(64),
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
    if (!castling_rights) {
      ss << "-";
    } else {
      if (castling_rights & WHITE_SHORT_CASTLE) {
        ss << "K";
      }
      if (castling_rights & WHITE_LONG_CASTLE) {
        ss << "Q";
      }
      if (castling_rights & BLACK_SHORT_CASTLE) {
        ss << "k";
      }
      if (castling_rights & BLACK_LONG_CASTLE) {
        ss << "q";
      }
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
  inline bool can_white_short_castle() {
    return (castling_rights & WHITE_SHORT_CASTLE);
  }
  inline bool can_white_long_castle() {
    return (castling_rights & WHITE_LONG_CASTLE);
  }
  inline bool can_black_short_castle() {
    return (castling_rights & BLACK_SHORT_CASTLE);
  }
  inline bool can_black_long_castle() {
    return (castling_rights & BLACK_LONG_CASTLE);
  }
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

  int set_fen(const std::string &fen) {
    std::istringstream iss(fen);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};

    if (tokens.size() != 6) {
      std::cerr << "Invalid FEN\n";
      return -1;
    }
    // Piece positions
    // TODO

    // Next to play
    if (tokens[1] == "w") {
      next_move = Color::WHITE;
    } else {
      next_move = Color::BLACK;
    }

    // Castling rights
    castling_rights = 0U;
    for (char &i : tokens[2]) {
      if (i == '-') {
        break;
      }
      if (i == 'K') {
        castling_rights |= WHITE_SHORT_CASTLE;
      } else if (i == 'Q') {
        castling_rights |= WHITE_LONG_CASTLE;
      } else if (i == 'k') {
        castling_rights |= BLACK_SHORT_CASTLE;
      } else if (i == 'q') {
        castling_rights |= BLACK_LONG_CASTLE;
      }
    }

    // En passant
    en_passant = 64U;
    if (tokens[3] != "-") {
      en_passant = square_to_index.at(tokens[3]);
    }

    // Move count for 50 moves rule
    moves_50 = std::stoul(tokens[4]);

    // Total moves
    total_moves = std::stoul(tokens[5]);

    return 0;
  }
};

#endif /* H_BOARD_H */