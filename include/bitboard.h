#include <cstdint>

const std::uint64_t k1 = 0x5555555555555555;
const std::uint64_t k2 = 0x3333333333333333;
const std::uint64_t k4 = 0x0f0f0f0f0f0f0f0f;
const std::uint64_t kf = 0x0101010101010101;

class Bitboard {
private:
  std::uint64_t bitboard;

public:
  Bitboard() : bitboard(0U){}

  explicit Bitboard(std::uint64_t position) : bitboard(position){}

  inline bool operator==(const Bitboard &b) {
    return this->bitboard == b.bitboard;
  }

  inline bool operator!=(const Bitboard &b) {
    return !(this->bitboard == b.bitboard);
  }

  inline bool is_empty() { return (this->bitboard == 0U); }

  inline bool is_single_pop() {
    if (this->bitboard == 0U) {
      return false;
    }
    return ((this->bitboard & (this->bitboard - 1)) == 0);
  }

  inline uint8_t population() {
    uint64_t x = this->bitboard;
    x = x - ((x >> 1) & k1);
    x = (x & k2) + ((x >> 2) & k2);
    x = (x + (x >> 4)) & k4;
    x = (x * kf) >> 56;
    return static_cast<uint8_t>(x);
  }
};
