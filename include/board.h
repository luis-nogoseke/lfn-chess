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
  std::shared_ptr<PawnBitboard> white_pawns;
  std::shared_ptr<KnightBitboard> white_knights;
  std::shared_ptr<BishopBitboard> white_bishops;
  std::shared_ptr<RookBitboard> white_rooks;
  std::shared_ptr<QueenBitboard> white_queen;
  std::shared_ptr<KingBitboard> white_king;

  // Black
  std::shared_ptr<PawnBitboard> black_pawns;
  std::shared_ptr<KnightBitboard> black_knights;
  std::shared_ptr<BishopBitboard> black_bishops;
  std::shared_ptr<RookBitboard> black_rooks;
  std::shared_ptr<QueenBitboard> black_queen;
  std::shared_ptr<KingBitboard> black_king;

  std::vector<Piece> squares{64, Piece::None};

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
        white_pawns(std::make_shared<PawnBitboard>(Color::WHITE)),
        white_knights(std::make_shared<KnightBitboard>(Color::WHITE)),
        white_bishops(std::make_shared<BishopBitboard>(Color::WHITE)),
        white_rooks(std::make_shared<RookBitboard>(Color::WHITE)),
        white_queen(std::make_shared<QueenBitboard>(Color::WHITE)),
        white_king(std::make_shared<KingBitboard>(Color::WHITE)),
        black_pawns(std::make_shared<PawnBitboard>(Color::BLACK)),
        black_knights(std::make_shared<KnightBitboard>(Color::BLACK)),
        black_bishops(std::make_shared<BishopBitboard>(Color::BLACK)),
        black_rooks(std::make_shared<RookBitboard>(Color::BLACK)),
        black_queen(std::make_shared<QueenBitboard>(Color::BLACK)),
        black_king(std::make_shared<KingBitboard>(Color::BLACK)) {}

  std::string fen() {
    std::stringstream ss;
    // Pieces
    int empty;
    for (int j = 8; j > 0; --j) {
      empty = 0;
      for (int i = 8 * (j - 1); i < 8 * j; ++i) {
        if (squares[i] != Piece::None) {
          if (empty != 0) {
            ss << empty;
            empty = 0;
          }
          ss << piece_symbol.at(squares[i]);
        } else {
          ++empty;
        }
      }
      if (empty != 0) {
        ss << empty;
      }
      if (j != 1) {
        ss << "/";
      }
    }

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
    ss << " ";
    ss << bitboard_index_to_square.at(en_passant);

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
    int j = 1, i = 0, sq, column, row;
    char letter;

    // Clear the board
    for (sq = 0; sq < 64; ++sq) {
      squares[sq] = Piece::None;
    }

    while ((j <= 64) && (i <= tokens[0].length())) {
      letter = tokens[0].at(i);
      i++;

      column = 1 + ((j - 1) % 8);
      row = 8 - ((j - 1) / 8);
      sq = (((row - 1) * 8) + (column - 1));
      switch (letter) {
        case 'p':
          squares[sq] = Piece::Black_Pawn;
          break;
        case 'r':
          squares[sq] = Piece::Black_Rook;
          break;
        case 'n':
          squares[sq] = Piece::Black_Knight;
          break;
        case 'b':
          squares[sq] = Piece::Black_Bishop;
          break;
        case 'q':
          squares[sq] = Piece::Black_Queen;
          break;
        case 'k':
          squares[sq] = Piece::Black_King;
          break;
        case 'P':
          squares[sq] = Piece::White_Pawn;
          break;
        case 'R':
          squares[sq] = Piece::White_Rook;
          break;
        case 'N':
          squares[sq] = Piece::White_Knight;
          break;
        case 'B':
          squares[sq] = Piece::White_Bishop;
          break;
        case 'Q':
          squares[sq] = Piece::White_Queen;
          break;
        case 'K':
          squares[sq] = Piece::White_King;
          break;
        case '/':
          j--;
          break;
        case '1':
          break;
        case '2':
          j++;
          break;
        case '3':
          j += 2;
          break;
        case '4':
          j += 3;
          break;
        case '5':
          j += 4;
          break;
        case '6':
          j += 5;
          break;
        case '7':
          j += 6;
          break;
        case '8':
          j += 7;
          break;
        default:
          std::cerr << "Invalid FEN\n";
          return -1;
      }
      j++;
    }

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

    // Set up the other bitboards
    std::shared_ptr<Bitboard> bb;
    Piece p;
    for (sq = 0; sq < 64; ++sq) {
      switch (squares[sq]) {
        case Piece::White_Pawn:
          white_pawns->set_bit(sq);
          break;
        case Piece::White_Knight:
          white_knights->set_bit(sq);
          break;
        case Piece::White_Bishop:
          white_bishops->set_bit(sp);
          break;
        case Piece::White_Rook:
          white_rooks->set_bit(sp);
          break;
        case Piece::White_Queen:
          white_queen->set_bit(sp);
          break;
        case Piece::White_King:
          white_king->set_bit(sp);
          break;
        case Piece::Black_Pawn:
          black_pawns->set_bit(sq);
          break;
        case Piece::Black_Knight:
          black_knights->set_bit(sq);
          break;
        case Piece::Black_Bishop:
          black_bishops->set_bit(sp);
          break;
        case Piece::Black_Rook:
          black_rooks->set_bit(sp);
          break;
        case Piece::Black_Queen:
          black_queen->set_bit(sp);
          break;
        case Piece::Black_King:
          black_king->set_bit(sp);
          break;
        default:
          break;
      }
    }
    return 0;
  }
};

#endif /* H_BOARD_H */