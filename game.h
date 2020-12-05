#ifndef GAME_H

#define GAME_H
#include <SDL2/SDL.h>

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
void movePlayer(player* player, int windowWidth);
int moveBall(ball* ball, int windowWidth, int windowHeight, int* waitTimeAfterPoint = 0 );
void setBallDirectionAfterPoint(ball* ball);
void setInitialBallPosition(ball* ball,int windowWidth, int windowHeight);
void executaSom (SDL_AudioDeviceID id,  Uint32 length, Uint8 *buffer);

#endif // GAME_H
