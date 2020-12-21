#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "game.h"

void getPlayerMovement(SDL_Event* evento, player* player1);
void getBotMovement (ball* ball, player* bot);
void startSinglePlayerGame (SDL_Renderer* renderizador);

#endif // SINGLEPLAYER_H
