// Copyright Paul Tröster

#pragma once

#include <ncurses.h>

// Position of the box.
extern int row;
extern int col;

// How many steps of the game have been played.
extern int done_steps;

// Int for num of alive pixels.
extern int alive_pixels;

// Bool that checks wether the game is playing or paused.
// True = Pixels / False = PixelsN
extern bool game_state;

// The state of all pixels on the screen + the dimensions of the screen.
const int MAX_NUM_PIXELS = 10'000;
extern int numRows;
extern int numCols;
extern bool pixels[MAX_NUM_PIXELS];

// Second state for game
extern bool *pointer1;
extern bool *pointer2;
extern bool pixelsN[MAX_NUM_PIXELS];

// Handle inputs
extern bool pressed_spacebar;

// Initialize Ncurses.
void initTerminal();

// Initialize game.
void initGame();

// Amount of alive neighbors around a pixel.
int numAliveNeighbors(int row, int col, bool *pixels);

// Switch the current game state.
void switchGameState();

// Switches the arrays depending on the game state.
// Switch the current game state.
void setStateArray();

// Set pixel at given logical position.
void setPixel(int row, int col, bool value);

// Calculate one-dimensional list into cols/rows.
int calc_linear_row(int e);
int calc_linear_col(int e, int row);

// Update state of the game.
void updateState();

// Show current state of the game.
void showState();

// Set the number of alive pixels.
void set_alive_pixels();

// Get the value of the pixel at the given logical position.
bool getPixel(int row, int col);

// Draw glider at given logical position.
void drawGlider(int row, int col);

// Set all pixels to random values.
void setPixelsToRandomValues();

// Draw a pixel.
void drawBox();

// handle user input.
bool processUserInput(int keycode);

// Process mouse click. Return true if there was a mouse click.
bool processMouseClick(MEVENT event);

// Clean up Ncurses.
void endNcurses();
