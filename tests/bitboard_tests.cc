#include "gtest/gtest.h"

#include "bitboard.h"

TEST(BitboardBasic, Equality) {
  Bitboard b1, b2;
  EXPECT_TRUE(b1 == b2);
  EXPECT_FALSE(b1 != b2);

  Bitboard b3(3U);
  EXPECT_TRUE(b1 != b3);
  EXPECT_FALSE(b1 == b3);
}

TEST(BitboardBasic, Empty) {
  Bitboard b1;
  EXPECT_TRUE(b1.is_empty());

  Bitboard b2(3U);
  EXPECT_FALSE(b2.is_empty());
}

TEST(BitboardBasic, SinglePop) {
  Bitboard b1;
  EXPECT_FALSE(b1.is_single_pop());

  Bitboard b2(4U);
  EXPECT_TRUE(b2.is_single_pop());
}

TEST(BitboardBasic, Population) {
  Bitboard b1;
  EXPECT_EQ(b1.population(), 0U);

  Bitboard b2(0x210040000800420U);
  EXPECT_EQ(b2.population(), 6U);
}
