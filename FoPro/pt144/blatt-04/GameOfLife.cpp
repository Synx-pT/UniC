// Copyright Paul Tröster

#include "./GameOfLife.h"
#include <cstdlib>
#include <ncurses.h>

// ____________________________________________________________________________
int row;
int col;
int done_steps;
int alive_pixels;
bool game_state;
bool *stateArray;

// ____________________________________________________________________________
int numRows;
int numCols;
bool *pointer1;
bool pixels[MAX_NUM_PIXELS];

// ____________________________________________________________________________
bool *pointer2;
bool pixelsN[MAX_NUM_PIXELS];

// ____________________________________________________________________________
bool pressed_spacebar;

// ____________________________________________________________________________
void initTerminal() {
  initscr();
  curs_set(false);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
}

// ____________________________________________________________________________
void initGame() {
  numRows = LINES;
  numCols = COLS / 2;

  game_state = true;
  pressed_spacebar = false;
}

// ____________________________________________________________________________
int numAliveNeighbors(int row, int col, bool *pixels) {
  int counter = 0;

  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      // Skip the center cell
      if (i == row && j == col)
        continue;
      // Check for valid indices to avoid accessing out of bounds
      if (i >= 0 && i < numRows && j >= 0 && j < numCols) {
        if (pixels[i * numCols + j])
          counter++;
      }
    }
  }

  return counter;
}

// ____________________________________________________________________________
void switchGameState() { game_state = !game_state; }

// ____________________________________________________________________________
void setStateArray() {
  if (game_state) {
    stateArray = pixels;
  } else {
    stateArray = pixelsN;
  }
}

// ____________________________________________________________________________
void setPixel(int row, int col, bool value) {
  setStateArray();

  stateArray[row * numCols + col] = value;
}

// ____________________________________________________________________________
int calc_linear_row(int e) {
  // Calculate the row
  int row = e / numCols;

  // Check if `e` is on the first column of any row
  if (e % numCols == 0 && e != 0) {
    row -= 1;
  }

  return row;
}

// ____________________________________________________________________________
int calc_linear_col(int e, int row) {
  // Calculate the column
  int col = e - (row * numCols);

  return col;
}

// ____________________________________________________________________________
void updateState() {
  bool *currentPixels = game_state ? pixels : pixelsN; // Current state array
  bool *nextPixels = game_state ? pixelsN : pixels;    // Next state array

  // Iterate over all cells to calculate the next state
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      int index = i * numCols + j;
      int aliveNeighbors =
          numAliveNeighbors(i, j, currentPixels); // Pass current array

      bool currentState = currentPixels[index];
      bool newState =
          (currentState && (aliveNeighbors == 2 || aliveNeighbors == 3)) ||
          (!currentState && aliveNeighbors == 3);

      nextPixels[index] = newState; // Update the next state array
    }
  }

  // Toggle the game state to switch roles of pixels and pixelsN for the next
  // generation
  game_state = !game_state;
}

// ____________________________________________________________________________
void showState() {

  setStateArray();

  attron(COLOR_PAIR(2)); // Choose a color pair for drawing
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      if (stateArray[row * numCols + col]) {
        attron(A_REVERSE); // Highlight for living cells
      }
      mvprintw(row, col * 2, "  ");
      if (stateArray[row * numCols + col]) {
        attroff(A_REVERSE);
      }
    }
  }
  attroff(COLOR_PAIR(2));
  refresh(); // Refresh the screen to reflect the changes
}

// ____________________________________________________________________________
void set_alive_pixels() {
  alive_pixels = 0;
  for (bool value : pixels) {
    if (value) {
      alive_pixels++;
    }
  }
}

// ____________________________________________________________________________
bool getPixel(int row, int col) {
  setStateArray();
  return stateArray[row * numCols + col];
}

// ____________________________________________________________________________
void drawGlider(int row, int col) {
  setPixel(row, col, true);
  setPixel(row, col + 1, true);
  setPixel(row, col + 2, true);
  setPixel(row + 1, col, true);
  setPixel(row + 2, col + 1, true);
}

// ____________________________________________________________________________
void setPixelsToRandomValues() {
  setStateArray();
  for (int i = 0; i < numRows * numCols; i++) {
    stateArray[i] = rand() % 5 == 0 ? true : false;
  }
}

// ____________________________________________________________________________
void drawBox() {
  attron(COLOR_PAIR(2) | A_REVERSE);
  mvprintw(row, col * 2, "  ");
  attroff(COLOR_PAIR(2) | A_REVERSE);
  refresh();
}

// ____________________________________________________________________________
bool processUserInput(int keycode) {
  switch (keycode) {
  case 103: // g - glider
    drawGlider(row, col);
    break;
  case 114: // r - random pixels
    setPixelsToRandomValues();
    break;
  case 113: // q - quit
    return true;
    break;
  case 115: // s - step
    updateState();
    break;
  case 32: // spacebar - auto-step
    pressed_spacebar = true;
    break;
  }
  showState();
  return false;
}

// ____________________________________________________________________________
bool processMouseClick(MEVENT event) {
  if (event.bstate & BUTTON1_PRESSED) {
    row = event.y;
    col = event.x / 2;
    return true;
  } else {
    return false;
  }
}

// ____________________________________________________________________________
void endNcurses() { endwin(); }
