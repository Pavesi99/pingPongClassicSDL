#include <SDL2/SDL.h>
#include <iostream>
using namespace std;



#ifndef GAME_H

#define GAME_H

struct player {
    int pontos = 0;
    int velocidade = 4;
    bool esquerda = false;
    bool direita = false;
    SDL_Rect destino;
    SDL_Rect origem;
    SDL_Texture* texture;
};

struct ball {
    int velocidade = 5;
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
void executaSom (SDL_AudioDeviceID id,  Uint32 length, Uint8 *buffer);
void startGame ( SDL_Renderer* renderizador);
ball attMoves (player* jogador, ball* bola);

#endif // GAME_H
