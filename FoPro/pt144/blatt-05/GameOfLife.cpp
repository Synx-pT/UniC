#include "./GameOfLife.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// The grid, alternated used to store the current and previous state.
bool grid1[GameOfLife::MAX_NUM_CELLS];
bool grid2[GameOfLife::MAX_NUM_CELLS];
bool *previousGrid_;
bool *currentGrid_;

// Glider.
int glider[5][2] = {{1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}};

const int GLIDER_FACTORY_SIZE = 36;
int gliderFactory[GLIDER_FACTORY_SIZE][2] = {
    {0, 24}, {1, 22}, {1, 24}, {2, 12}, {2, 13}, {2, 20}, {2, 21}, {2, 34},
    {2, 35}, {3, 11}, {3, 15}, {3, 20}, {3, 21}, {3, 34}, {3, 35}, {4, 0},
    {4, 1},  {4, 10}, {4, 16}, {4, 20}, {4, 21}, {5, 0},  {5, 1},  {5, 10},
    {5, 14}, {5, 16}, {5, 17}, {5, 22}, {5, 24}, {6, 10}, {6, 16}, {6, 24},
    {7, 11}, {7, 15}, {8, 12}, {8, 13}};

// Last click, used to generate glider.
int lastClickedRow_;
int lastClickedCol_;

// Global state
bool isRunning_;
int numSteps_;
int numLivingCells_;

// ____________________________________________________________________________
void GameOfLife::play() {
  // Initialize terminal and grid.
  terminalManager_.setup();
  initGame();

  if (terminalManager_.numRows() * terminalManager_.numCols() > MAX_NUM_CELLS) {
    printf("Screen too large, increase MAX_NUM_PIXELS\n");
    return;
  }

  while (processUserInput(getch())) {
    if (isRunning_) {
      updateState();
    }
    // Draw and wait.
    showState();
    usleep(50 * 1000);
  }
  // Clean up window.
  terminalManager_.cleanup();
}

// ____________________________________________________________________________
void GameOfLife::initGame() {
  previousGrid_ = grid1;
  currentGrid_ = grid2;
  for (int row = 0; row < terminalManager_.numRows(); ++row) {
    for (int col = 0; col < terminalManager_.numCols(); ++col) {
      setCurrent(row, col, false);
      setPrevious(row, col, false);
    }
  }

  lastClickedRow_ = -1;
  lastClickedCol_ = -1;

  isRunning_ = false;
  numSteps_ = 0;
  numLivingCells_ = 0;
}

// ____________________________________________________________________________
bool GameOfLife::processUserInput(int keycode) {
  MEVENT event;
  switch (keycode) {
  case 'q':
    // Exit
    return false;
  case ' ':
    // Toggle run
    isRunning_ = !isRunning_;
    break;
  case 's':
    // Execute step
    updateState();
    break;
  case 'c':
    // Clear all
    for (int row = 0; row < terminalManager_.numRows(); ++row) {
      for (int col = 0; col < terminalManager_.numCols(); ++col) {
        setCurrent(row, col, false);
      }
    }
    break;
  case 'r':
    // Fill randomly
    for (int row = 0; row < terminalManager_.numRows(); ++row) {
      for (int col = 0; col < terminalManager_.numCols(); ++col) {
        setCurrent(row, col, drand48() > 0.8);
      }
    }
    break;
  case 'g':
    // Generate glider
    setCurrent(lastClickedRow_, lastClickedCol_, false);
    for (int i = 0; i < 5; ++i) {
      int row = lastClickedRow_ + glider[i][0];
      int col = lastClickedCol_ + glider[i][1];
      setCurrent(row, col, true);
    }
    break;
  case 'G':
    // Generate glider factory
    setCurrent(lastClickedRow_, lastClickedCol_, false);
    for (int i = 0; i < GLIDER_FACTORY_SIZE; ++i) {
      int row = lastClickedRow_ + gliderFactory[i][0];
      int col = lastClickedCol_ + gliderFactory[i][1];
      setCurrent(row, col, true);
    }
    break;
  case KEY_MOUSE:
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_PRESSED) {
        // Store position of click and invert cell.
        // Check if the click was inside the grid:
        //
        lastClickedCol_ = event.x / 2;
        lastClickedRow_ = event.y;
        bool prev = getCurrent(lastClickedRow_, lastClickedCol_);
        setCurrent(lastClickedRow_, lastClickedCol_, !prev);
      }
    }
    break;
  }
  return true;
}

// ____________________________________________________________________________
void GameOfLife::updateState() {
  numLivingCells_ = 0;

  // Exchange the grid pointers without copying the grids.
  bool *tempGrid = currentGrid_;
  currentGrid_ = previousGrid_;
  previousGrid_ = tempGrid;

  for (int row = 0; row < terminalManager_.numRows(); ++row) {
    for (int col = 0; col < terminalManager_.numCols(); ++col) {
      int neighbours = numAliveNeighbours(row, col);
      bool isAlive = false;
      if (getPrevious(row, col)) {
        // Stay alive if 2 or 3 neighbours are alive, die otherwise.
        isAlive = neighbours > 1 && neighbours < 4;
      } else if (neighbours == 3) {
        // Birth of a cell if exactly 3 neighbours are alive.
        isAlive = true;
      }
      // Count cells which are alive.
      numLivingCells_ += isAlive;
      setCurrent(row, col, isAlive);
    }
  }

  // Update the step counter.
  ++numSteps_;
}

// ____________________________________________________________________________
int GameOfLife::numAliveNeighbours(int row, int col) {
  int result = 0;
  // Check the 3x3 around the given cell.
  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      // Ignore the given cell itself
      if (dr == 0 && dc == 0) {
        continue;
      }
      result += getPrevious(row + dr, col + dc);
    }
  }
  return result;
}

// __________________________________________________________________________
bool GameOfLife::isLegalPosition(int row, int col) {
  return (row >= 0) && (col >= 0) && (row < terminalManager_.numRows()) &&
         (col < terminalManager_.numCols());
}

// __________________________________________________________________________
bool GameOfLife::get(int row, int col, bool isPrevious) {
  // return false for out-of-bounds access.
  if (!isLegalPosition(row, col)) {
    return false;
  }
  int idx = row * terminalManager_.numCols() + col;
  bool *grid = isPrevious ? previousGrid_ : currentGrid_;
  return grid[idx];
}

bool GameOfLife::getPrevious(int row, int col) { return get(row, col, true); }

bool GameOfLife::getCurrent(int row, int col) { return get(row, col, false); }

// __________________________________________________________________________
void GameOfLife::set(int row, int col, bool value, bool isPrevious) {
  // do nothing for out of bounds acces.
  if (!isLegalPosition(row, col)) {
    return;
  }
  int idx = row * terminalManager_.numCols() + col;
  bool *grid = isPrevious ? previousGrid_ : currentGrid_;
  grid[idx] = value;
}

void GameOfLife::setPrevious(int row, int col, bool value) {
  set(row, col, value, true);
}

void GameOfLife::setCurrent(int row, int col, bool value) {
  set(row, col, value, false);
}

// ____________________________________________________________________________
void GameOfLife::showState() {
  // Only draw visible cells.
  for (int row = 0; row < terminalManager_.numRows(); ++row) {
    for (int col = 0; col < terminalManager_.numCols(); ++col) {
      attroff(A_REVERSE);
      if (getCurrent(row, col)) {
        attron(A_REVERSE);
      }
      mvprintw(row, col * 2, "  ");
    }
  }
  attroff(A_REVERSE);
  mvprintw(0, 0, "Steps: %9d Cells alive: %4d Running: %d", numSteps_,
           numLivingCells_, isRunning_);
}