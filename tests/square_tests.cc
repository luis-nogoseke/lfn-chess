#include "square.h"
#include "gtest/gtest.h"

TEST(SqaureBasic, Equality) {
  Square s1, s2, s3{3}, s4{0, 3};
  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s2 == s3);
  EXPECT_TRUE(s3 == s4);
  EXPECT_TRUE(s1 != s4);
}

TEST(SqaureBasic, Basic) {
  Square s1{0, 3};

  EXPECT_EQ(s1.to_int(), 3);
  EXPECT_EQ(s1.to_board(), 8);
  EXPECT_STREQ(s1.to_string().c_str(), "d1");
}
