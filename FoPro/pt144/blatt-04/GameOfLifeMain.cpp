// Copyright Paul Tröster

#include "./GameOfLife.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  // Initialize Ncurses.
  initTerminal();
  initGame();

  if (numRows * numCols > MAX_NUM_PIXELS) {
    printf("Screen too large, increase MAX_NUM_PIXELS\n");
    return 1;
  }

  // Main loop.
  while (true) {
    MEVENT event;
    int key = getch();

    while (pressed_spacebar) {
      updateState();
      showState();

      set_alive_pixels();
      mvprintw(2, 2, "Alive Pixels: %d", alive_pixels);

      mvprintw(LINES - 2, COLS / 2 - 12, "---SPACEBAR ACTIVATED---");

      int key = getch();

      if (key == 32) {
        pressed_spacebar = false;
        mvprintw(LINES - 2, COLS / 2 - 12, "---SPACEBAR DEACTIVATED---");
      }
      usleep(500'000);
    }

    if (getmouse(&event) == OK) {
      bool mouseClicked = processMouseClick(event);
      if (mouseClicked) {
        setPixel(row, col, !getPixel(row, col));
        showState();
        attron(COLOR_PAIR(1));
        mvprintw(2, 2, "Mouse clicked at: %3d,%3d", row, col);
        attroff(COLOR_PAIR(1));
      }
    }
    if (key == 'g') {
      drawGlider(row, col);
      showState();
    }
    if (key == 'r') {
      setPixelsToRandomValues();
      showState();
    }
    if (key == 113) {
      break;
    }
    if (key == 115) {
      updateState();
      showState();
    }
    if (key == 32) {
      pressed_spacebar = true;
    }
    usleep(1000);
  }
  endNcurses();
}