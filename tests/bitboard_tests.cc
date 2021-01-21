#include "bitboard.h"
#include "gtest/gtest.h"

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

TEST(BitboardBasic, SetBit) {
  Bitboard b;
  b.set_bit(1);
  EXPECT_TRUE(b.is_bit_set(1));
  b.set_bit(0);
  EXPECT_TRUE(b.is_bit_set(0));
  b.set_bit(63);
  EXPECT_TRUE(b.is_bit_set(63));
  b.set_bit(15);
  EXPECT_TRUE(b.is_bit_set(15));
}

TEST(PawnBitboardBasic, Pawns) {
  PawnBitboard b1(Color::WHITE);
  EXPECT_EQ(b1.population(), 8U);
  PawnBitboard b2(Color::BLACK);
  EXPECT_EQ(b2.population(), 8U);
}

TEST(KnightBitboardBasic, Knights) {
  KnightBitboard b1(Color::WHITE);
  EXPECT_EQ(b1.population(), 2U);
  KnightBitboard b2(Color::BLACK);
  EXPECT_EQ(b2.population(), 2U);
}

TEST(BishopBitboardBasic, Bishops) {
  BishopBitboard b1(Color::WHITE);
  EXPECT_EQ(b1.population(), 2U);
  BishopBitboard b2(Color::BLACK);
  EXPECT_EQ(b2.population(), 2U);
}

TEST(RookBitboardBasic, Rooks) {
  RookBitboard b1(Color::WHITE);
  EXPECT_EQ(b1.population(), 2U);
  RookBitboard b2(Color::BLACK);
  EXPECT_EQ(b2.population(), 2U);
}

TEST(QueenBitboardBasic, Queen) {
  QueenBitboard b1(Color::WHITE);
  EXPECT_EQ(b1.population(), 1U);
  QueenBitboard b2(Color::BLACK);
  EXPECT_EQ(b2.population(), 1U);
}

TEST(KingBitboardBasic, King) {
  KingBitboard b1(Color::WHITE);
  EXPECT_EQ(b1.population(), 1U);
  KingBitboard b2(Color::BLACK);
  EXPECT_EQ(b2.population(), 1U);
}
