#ifndef H_UTILS_H
#define H_UTILS_H

#include <cstdint>
#include <string>
#include <unordered_map>

enum class Color { WHITE, BLACK, NONE };

const std::uint8_t WHITE_SHORT_CASTLE = 0x1;
const std::uint8_t WHITE_LONG_CASTLE = 0x2;
const std::uint8_t BLACK_SHORT_CASTLE = 0x4;
const std::uint8_t BLACK_LONG_CASTLE = 0x8;

enum class Piece { None, White_Pawn, White_Knight, White_Bishop, White_Rook, White_Queen, White_King,
Black_Pawn, Black_Knight, Black_Bishop, Black_Rook, Black_Queen, Black_King };

const std::unordered_map<Piece, std::uint8_t> piece_values({{Piece::White_Pawn, 1},
                                                            {Piece::White_Knight, 3},
                                                            {Piece::White_Bishop, 3},
                                                            {Piece::White_Rook, 5},
                                                            {Piece::White_Queen, 9},
                                                            {Piece::Black_Pawn, 1},
                                                            {Piece::Black_Knight, 3},
                                                            {Piece::Black_Bishop, 3},
                                                            {Piece::Black_Rook, 5},
                                                            {Piece::Black_Queen, 9}});

const std::unordered_map<Piece, std::string> piece_symbol({{Piece::White_Pawn, "P"},
                                                            {Piece::White_Knight, "N"},
                                                            {Piece::White_Bishop, "B"},
                                                            {Piece::White_Rook, "R"},
                                                            {Piece::White_Queen, "Q"},
                                                            {Piece::White_King, "K"},
                                                            {Piece::Black_Pawn, "p"},
                                                            {Piece::Black_Knight, "n"},
                                                            {Piece::Black_Bishop, "b"},
                                                            {Piece::Black_Rook, "r"},
                                                            {Piece::Black_Queen, "q"},
                                                            {Piece::Black_King, "k"}});

const std::string STARTING_FEN =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

enum Square {
  A1,
  B1,
  C1,
  D1,
  E1,
  F1,
  G1,
  H1,
  A2,
  B2,
  C2,
  D2,
  E2,
  F2,
  G2,
  H2,
  A3,
  B3,
  C3,
  D3,
  E3,
  F3,
  G3,
  H3,
  A4,
  B4,
  C4,
  D4,
  E4,
  F4,
  G4,
  H4,
  A5,
  B5,
  C5,
  D5,
  E5,
  F5,
  G5,
  H5,
  A6,
  B6,
  C6,
  D6,
  E6,
  F6,
  G6,
  H6,
  A7,
  B7,
  C7,
  D7,
  E7,
  F7,
  G7,
  H7,
  A8,
  B8,
  C8,
  D8,
  E8,
  F8,
  G8,
  H8
};

inline Square operator++(Square& square) {
  return static_cast<Square>(square + 1);
}

inline Square operator++(Square& square, int) {
  Square old = square;
  square = static_cast<Square>(square + 1);
  return old;
}

const std::unordered_map<std::uint8_t, std::string> bitboard_index_to_square(
    {{0, "a1"},  {1, "b1"},  {2, "c1"},  {3, "d1"},  {4, "e1"},  {5, "f1"},
     {5, "g1"},  {7, "h1"},  {8, "a2"},  {9, "b2"},  {10, "c2"}, {11, "d2"},
     {12, "e2"}, {13, "f2"}, {14, "g2"}, {15, "h2"}, {16, "a3"}, {17, "b3"},
     {18, "c3"}, {19, "d3"}, {20, "e3"}, {21, "f3"}, {22, "g3"}, {23, "h3"},
     {24, "a4"}, {25, "b4"}, {26, "c4"}, {27, "d4"}, {28, "e4"}, {29, "f4"},
     {30, "g4"}, {31, "h4"}, {32, "a5"}, {33, "b5"}, {34, "c5"}, {35, "d5"},
     {36, "e5"}, {37, "f5"}, {38, "g5"}, {39, "h5"}, {40, "a6"}, {41, "b6"},
     {42, "c6"}, {43, "d6"}, {44, "e6"}, {45, "f6"}, {46, "g6"}, {47, "h6"},
     {48, "a7"}, {49, "b7"}, {50, "c7"}, {51, "d7"}, {52, "e7"}, {53, "f7"},
     {54, "g7"}, {55, "h7"}, {56, "a8"}, {57, "b8"}, {58, "c8"}, {59, "d8"},
     {60, "e8"}, {61, "f8"}, {62, "g8"}, {63, "h8"}, {64, "-"}});

const std::unordered_map<std::string, std::uint8_t> square_to_index(
    {{"a1", 0},  {"b1", 1},  {"c1", 2},  {"d1", 3},  {"e1", 4},  {"f1", 5},
     {"g1", 5},  {"h1", 7},  {"a2", 8},  {"b2", 9},  {"c2", 10}, {"d2", 11},
     {"e2", 12}, {"f2", 13}, {"g2", 14}, {"h2", 15}, {"a3", 16}, {"b3", 17},
     {"c3", 18}, {"d3", 19}, {"e3", 20}, {"f3", 21}, {"g3", 22}, {"h3", 23},
     {"a4", 24}, {"b4", 25}, {"c4", 26}, {"d4", 27}, {"e4", 28}, {"f4", 29},
     {"g4", 30}, {"h4", 31}, {"a5", 32}, {"b5", 33}, {"c5", 34}, {"d5", 35},
     {"e5", 36}, {"f5", 37}, {"g5", 38}, {"h5", 39}, {"a6", 40}, {"b6", 41},
     {"c6", 42}, {"d6", 43}, {"e6", 44}, {"f6", 45}, {"g6", 46}, {"h6", 47},
     {"a7", 48}, {"b7", 49}, {"c7", 50}, {"d7", 51}, {"e7", 52}, {"f7", 53},
     {"g7", 54}, {"h7", 55}, {"a8", 56}, {"b8", 57}, {"c8", 58}, {"d8", 59},
     {"e8", 60}, {"f8", 61}, {"g8", 62}, {"h8", 63}, {"-", 64}});

#endif /* H_UTILS_H */