#ifndef TWO_PLAYER_H

#define TWO_PLAYER_H

#include "game.h";

void getPlayersMovement(SDL_Event* evento, player* player1, player* player2);
void setInitialPlayersPositions(player* player1, player* player2);
bool checkBallCollision(ball* ball, player* player1, player* player2);
void startGame ( SDL_Renderer* renderizador);

#endif // TWO_PLAYER_H
