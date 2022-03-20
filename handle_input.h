#ifndef HANDLE_INPUT_H
#define HANDLE_INPUT_H

#include <SDL.h>

// Quit the game on certain inputs
void handle_input(bool *running, SDL_Rect *dest, int player_velocity);

#endif
