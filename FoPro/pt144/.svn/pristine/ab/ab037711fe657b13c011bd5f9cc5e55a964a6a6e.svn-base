// Copyright Paul Tröster

#include "./Snake.h"
#include <ncurses.h>
#include <unistd.h>

// ____________________________________________________________________________
int sec = 1'000'000;
int speed = 1;
int acceleration = 1;
int score;
int row, column;
int dx = 2; // Initial horizontal direction (right)
int dy = 0; // Initial vertical direction (none)

// ____________________________________________________________________________
void initTerminal() {
  initscr();
  curs_set(0);           // Invisible cursor
  noecho();              // Don't echo keypresses
  nodelay(stdscr, true); // Non-blocking input
  keypad(stdscr, true);  // Capture arrow keys
  start_color();         // Enable colors
  init_pair(1, COLOR_BLUE, COLOR_GREEN);
  init_pair(2, COLOR_YELLOW, COLOR_MAGENTA);
}

// ____________________________________________________________________________
void endGame() { endwin(); }

// ____________________________________________________________________________
void drawPixel(int row, int column, int color) {
  attron(COLOR_PAIR(color));
  mvprintw(row, column, "  ");
  attroff(COLOR_PAIR(color));
  refresh();
}

// ____________________________________________________________________________
void moveSnake() {
  // Clear the current position before moving
  mvprintw(row, column, "  ");

  column += dx;
  row += dy;
}

// ____________________________________________________________________________
void drawSnake(int color) {
  drawPixel(row, column, color);
  refresh();
}

// ____________________________________________________________________________
void drawBorder(int color) {
  for (int i = 0; i < LINES; i++) {
    attron(COLOR_PAIR(color));
    drawPixel(i, 0, color);
    drawPixel(i, COLS - 2, color);
    attroff(COLOR_PAIR(color));
  }

  for (int j = 0; j < COLS; j++) {
    attron(COLOR_PAIR(color));
    drawPixel(0, j, color);
    drawPixel(LINES - 1, j, color);
    attroff(COLOR_PAIR(color));
  }
}

// ____________________________________________________________________________
bool collidesWithBorder() {
  return row <= 0 || row >= LINES - 1 || column <= 1 || column >= COLS - 3;
}

// ____________________________________________________________________________
bool handleKey(int key) {
  int oldDx = dx;
  int oldDy = dy;

  switch (key) {
  case KEY_LEFT:
    if (dx == 0) {
      dx = -2;
      dy = 0;
    }
    break;
  case KEY_RIGHT:
    if (dx == 0) {
      dx = 2;
      dy = 0;
    }
    break;
  case KEY_UP:
    if (dy == 0) {
      dx = 0;
      dy = -1;
    }
    break;
  case KEY_DOWN:
    if (dy == 0) {
      dx = 0;
      dy = 1;
    }
    break;
  case 27: // ESC key
    return true;
  }
  return false;
}

// ____________________________________________________________________________
void initGame() {
  drawBorder(2);
  row = LINES / 2;
  column = COLS / 2;
  refresh();

  for (int i = 0; true; ++i) {
    int key = getch();
    bool exitGame = handleKey(key);

    if (exitGame)
      break;

    moveSnake();
    drawSnake(1);

    if (collidesWithBorder())
      break;

    score++;
    speed += acceleration;

    mvprintw(2, 3, "Score: %d", score);
    mvprintw(2, COLS - 17, "Speed: %d", (speed));

    if (speed >= 100)
      break;

    usleep(sec / speed);
  }

  if (speed >= 100) {
    mvprintw(LINES / 2, (COLS / 2) - 14, "You won the game, wooooow...");
    mvprintw((LINES / 2) + 2, (COLS / 2) - 14, "Press Esc to exit the game.");
    for (int i = 0; true; i++) {
      int key = getch();
      if (key == 27)
        break;
      usleep(1000);
    }
  } else {
    mvprintw(LINES / 2, (COLS / 2) - 10, "Your Score is: %d\n.", score);
    mvprintw((LINES / 2) + 2, (COLS / 2) - 14, "Press Esc to exit the game.");
    for (int i = 0; true; i++) {
      int key = getch();
      if (key == 27)
        break;
      usleep(1000);
    }
  }
}
