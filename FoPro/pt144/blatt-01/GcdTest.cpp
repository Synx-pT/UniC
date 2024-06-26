
#include <gtest/gtest.h>

#include "./Gcd.cpp"

TEST(GcdTest, calc_gcd) {
  ASSERT_EQ(calc_gcd(18, 24), 6);
  ASSERT_EQ(calc_gcd(30, 600), 30);
  ASSERT_EQ(calc_gcd(21, 14), 7);
  ASSERT_EQ(calc_gcd(15, 5), 5);
  ASSERT_EQ(calc_gcd(101, 10), 1);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
