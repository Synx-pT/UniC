#include "./GameOfLife.h"

#include <ncurses.h>
#include <unistd.h>

int main() {
  GameOfLife gameOfLife;
  gameOfLife.play();
}