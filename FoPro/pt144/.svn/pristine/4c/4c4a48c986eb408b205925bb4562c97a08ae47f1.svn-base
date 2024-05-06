// Copyright Paul Tröster

#include "./Snake.h"
#include <gtest/gtest.h>
#include <ncurses.h>

TEST(NcursesTest, CollidesWithBorder) {
  row = 0; // Edge of the top border
  column = 5;
  ASSERT_TRUE(collidesWithBorder());

  row = LINES - 1; // Edge of the bottom border
  column = 5;
  ASSERT_TRUE(collidesWithBorder());

  row = 5;
  column = 0; // Edge of the left border
  ASSERT_TRUE(collidesWithBorder());

  row = 5;
  column = COLS - 2; // Edge of the right border
  ASSERT_TRUE(collidesWithBorder());

  row = 5;
  column = 5;
  ASSERT_TRUE(collidesWithBorder());
}

TEST(NcursesTest, MoveSnake) {
  row = 5;
  column = 5;
  dx = 1;
  dy = 0;
  moveSnake();
  ASSERT_EQ(column, 6);
  ASSERT_EQ(row, 5);

  dx = 0;
  dy = 1;
  moveSnake();
  ASSERT_EQ(column, 6);
  ASSERT_EQ(row, 6);
}

TEST(NcursesTest, HandleKey) {
  dx = 1;
  dy = 0;                            // Moving right
  ASSERT_FALSE(handleKey(KEY_LEFT)); // Should ignore opposite direction key
  ASSERT_EQ(dx, 1);
  ASSERT_EQ(dy, 0);

  ASSERT_FALSE(handleKey(KEY_RIGHT)); // Change direction to right
  ASSERT_EQ(dx, 1);
  ASSERT_EQ(dy, 0);

  ASSERT_FALSE(handleKey(KEY_UP));
  ASSERT_EQ(dx, 0);
  ASSERT_EQ(dy, -1);

  ASSERT_TRUE(handleKey(27)); // ESC key should return true
}
