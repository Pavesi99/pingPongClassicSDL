#include "game.h"

#ifndef TWO_PLAYER_H
#define TWO_PLAYER_H

void getPlayersMovement(SDL_Event* evento, player* player1, player* player2);
void setInitialPlayersPositions(player* player1, player* player2, int windowWidth, int windowHeight);
bool checkBallCollision(ball* ball, player* player1, player* player2);
void startTwoPlayersGame ( SDL_Renderer* renderizador);



#endif // TWO_PLAYER_H
