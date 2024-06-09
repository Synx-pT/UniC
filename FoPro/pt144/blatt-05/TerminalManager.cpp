#include "./TerminalManager.h"
#include "./GameOfLife.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// The initial values are used by the tests. In the game the are overwritten by
// the initTerminal function.
// int numRows_ = 100;
// int numCols_ = 100;

int numCols_;
int numRows_;

// ____________________________________________________________________________
void TerminalManager::setup() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  numCols_ = COLS / 2;
  numRows_ = LINES;
}

// ____________________________________________________________________________
void TerminalManager::cleanup() { endwin(); }
