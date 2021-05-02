#include <cstdint>
#include <string>

class Square {
 public:
  Square() : square_(255){};

  explicit constexpr Square(std::uint8_t square) : square_(square) {}

  constexpr Square(std::uint8_t row, std::uint8_t file)
      : square_(row * 8 + file) {}

  //   explict Square(std::string square)
  //   {
  //   }

  void set(std::uint8_t square) { square_ = square; }

  void set(std::uint8_t row, std::uint8_t file) { square_ = row * 8 + file; }

  int row() const { return square_ / 8; }

  int col() const { return square_ % 8; }

  static bool is_valid(int row, int file) {
    return row >= 0 && file >= 0 && row < 8 && file < 8;
  }

  bool operator==(const Square& other) const {
    return square_ == other.square_;
  }

  constexpr bool operator!=(const Square& other) const {
    return square_ != other.square_;
  }

  constexpr std::uint8_t to_int() const { return square_; }

  constexpr std::uint64_t to_board() const { return 1ULL << square_; }

  std::string to_string() const {
    return std::string(1, 'a' + col()) + std::string(1, '1' + row());
  }

 private:
  std::uint8_t square_;
};