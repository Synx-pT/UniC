// Copyright Paul Tröster

#pragma once


extern int speed; // Int for game speed
extern int score; // Score of the game
extern int sec; // A second for usleep.
extern int acceleration; // Accel. of the speed
extern int row, column; // Row and column for placement of pixels.
extern int dx; // Direction for horizontal movement
extern int dy; // Direction for vertical movement

// Initialize Terminal.
void initTerminal();

// Move the snake into a certain direction.
void moveSnake();

// Clean up Ncurses.
void endGame();

// Intialize Game.
void initGame();

// Draw Box.
void drawPixel(int row, int column, int color);

// Draw Border based on window size.
void drawBorder(int color);

// Checks wether the snake is colliding with the border.
bool collidesWithBorder();

// Handels input keys in order to stop the game/ move the snake.
bool handleKey(int key);