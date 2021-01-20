#include <iostream>
#include <string>

#include "bitboard.h"
#include "board.h"
#include "utils.h"

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
  Board b, b1, b2, b3;
  b.set_fen(STARTING_FEN);
  EXPECT_STREQ(STARTING_FEN.c_str(), b.fen().c_str());

  b1.set_fen("2B5/8/3R1N1P/2p5/P2P2N1/1p1p4/P1n2Qp1/k5K1 w - - 0 1");
  EXPECT_STREQ("2B5/8/3R1N1P/2p5/P2P2N1/1p1p4/P1n2Qp1/k5K1 w - - 0 1", b1.fen().c_str());

  b2.set_fen("4nk2/P4p2/1pPp3q/2b5/7p/R1r4b/1K6/B3N3 w - - 0 1");
  EXPECT_STREQ("4nk2/P4p2/1pPp3q/2b5/7p/R1r4b/1K6/B3N3 w - - 0 1", b2.fen().c_str());

  b3.set_fen("b7/1Q1p2k1/2qr4/8/1Pp3PP/8/1KpRn2p/7R w - e3 0 1");
  EXPECT_STREQ("b7/1Q1p2k1/2qr4/8/1Pp3PP/8/1KpRn2p/7R w - e3 0 1", b3.fen().c_str());
}

// is game over
// is check
// is  checkmate
// is stalemate
// is insufficient material
