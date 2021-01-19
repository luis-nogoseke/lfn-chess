#include <iostream>
#include <string>

#include "bitboard.h"
#include "board.h"
#include "gtest/gtest.h"

TEST(BoardBasic, InitialValues) {
  Board b;
  EXPECT_EQ(b.next_to_move(), Color::WHITE);
  EXPECT_TRUE(b.can_white_short_castle());
  EXPECT_TRUE(b.can_white_long_castle());
  EXPECT_TRUE(b.can_black_short_castle());
  EXPECT_TRUE(b.can_black_long_castle());

  EXPECT_EQ(b.get_pieces_score(Color::WHITE), 39U);
  EXPECT_EQ(b.get_pieces_score(Color::BLACK), 39U);
}

TEST(BoardBasic, FEN) {
  Board b;
  std::cout << b.fen() << std::endl;
}

TEST(BoardBasic, setFEN) {
  Board b;
  b.set_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e3 0 1");
}

// is game over
// is check
// is  checkmate
// is stalemate
// is insufficient material
