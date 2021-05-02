#ifndef H_BITBOARD_H
#define H_BITBOARD_H

#include <cstdint>

#include "utils.h"

class Bitboard {
 protected:
  std::uint64_t bitboard;

 public:
  Bitboard() : bitboard(0U) {}

  explicit Bitboard(std::uint64_t position) : bitboard(position) {}

  inline bool operator==(const Bitboard &b) const{
    return this->bitboard == b.bitboard;
  }

  inline bool operator!=(const Bitboard &b) const{
    return !(this->bitboard == b.bitboard);
  }

  inline bool is_empty() const { return (this->bitboard == 0U); }

  inline bool is_single_pop() const {
    if (this->bitboard == 0U) {
      return false;
    }
    return ((this->bitboard & (this->bitboard - 1)) == 0);
  }

  inline uint8_t population() const {
    uint64_t x = this->bitboard;
    x = x - ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
    x = (x * 0x0101010101010101) >> 56;
    return static_cast<uint8_t>(x);
  }

  inline void set_bit(uint8_t square) { bitboard |= (2 ^ square); }

  inline bool is_bit_set(uint8_t square) const {
    return static_cast<bool>(bitboard && (square + 1));
  }
};

class PawnBitboard : public Bitboard {
 public:
  explicit PawnBitboard(Color color) {
    if (color == Color::WHITE) {
      this->bitboard = 0xFF00;
    } else {
      this->bitboard = 0xFF000000000000;
    }
  }
};

class RookBitboard : public Bitboard {
 public:
  explicit RookBitboard(Color color) {
    if (color == Color::WHITE) {
      this->bitboard = 0x81;
    } else {
      this->bitboard = 0x8100000000000000;
    }
  }
};

class KnightBitboard : public Bitboard {
 public:
  explicit KnightBitboard(Color color) {
    if (color == Color::WHITE) {
      this->bitboard = 0x42;
    } else {
      this->bitboard = 0x4200000000000000;
    }
  }
};

class BishopBitboard : public Bitboard {
 public:
  explicit BishopBitboard(Color color) {
    if (color == Color::WHITE) {
      this->bitboard = 0x24;
    } else {
      this->bitboard = 0x2400000000000000;
    }
  }
};

class QueenBitboard : public Bitboard {
 public:
  explicit QueenBitboard(Color color) {
    if (color == Color::WHITE) {
      this->bitboard = 0x8;
    } else {
      this->bitboard = 0x800000000000000;
    }
  }
};

class KingBitboard : public Bitboard {
 public:
  explicit KingBitboard(Color color) {
    if (color == Color::WHITE) {
      this->bitboard = 0x10;
    } else {
      this->bitboard = 0x1000000000000000;
    }
  }
};

#endif /* H_BITBOARD_H */