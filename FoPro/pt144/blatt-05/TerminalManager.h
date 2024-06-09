#pragma once

class TerminalManager {
private:

  int numRows_;
  int numCols_;

public:

  int numRows() { return numRows_; }
  int numCols() { return numCols_; }

  void setup();

  void cleanup();

  // Draw the new grid using ncurses.
  void showState();
};