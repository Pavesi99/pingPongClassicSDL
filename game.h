#include <SDL2/SDL.h>

#ifndef GAME_H
#define GAME_H

struct player {
    int pontos = 0;
    bool esquerda = false;
    bool direita = false;
    SDL_Rect destino;
    SDL_Rect origem;
    SDL_Texture* texture;
};

struct ball {
    bool esquerda = false;
    bool direita = false;
    bool cima = true;
    bool baixo = false;
    SDL_Rect destino;
    SDL_Rect origem;
    SDL_Texture* texture;
};

SDL_Texture* carregaImagemBMP (const char* src, SDL_Renderer* renderizador);
void getPlayersMovement(SDL_Event* evento, player* player1, player* player2);
void movePlayer(player* player, int windowWidth);
int moveBall(ball* ball, int windowWidth, int windowHeight, int* waitTimeAfterPoint = 0 );
void setInitialPlayersPositions(player* player1, player* player2);
void setBallDirectionAfterPoint(ball* ball);
void setInitialBallPosition(ball* ball,int windowWidth, int windowHeight);
bool checkBallCollision(ball* ball, player* player1, player* player2);
void startGame ( SDL_Renderer* renderizador);

#endif // GAME_H
