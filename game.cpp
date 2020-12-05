#include "game.h"
#include "menu.h"

int VelocidadeDoJogo = 1;

SDL_Texture* carregaImagemBMP (const char* src, SDL_Renderer* renderizador) {
    SDL_Surface* imagem = SDL_LoadBMP(src);
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderizador, imagem);
    SDL_FreeSurface(imagem);

    return textura;
}

void movePlayer(player* player, int windowWidth){

    if(player->direita){
        player->destino.x += (player->velocidade  * VelocidadeDoJogo);
        if(player->destino.x > (windowWidth - player->destino.w)){
            player->destino.x = (windowWidth - player->destino.w);
        }
    }

    if(player->esquerda){
        player->destino.x -= (player->velocidade * VelocidadeDoJogo);
        if(player->destino.x < 0){
            player->destino.x = 0;
        }
    }
}

int moveBall(ball* ball, int windowWidth, int windowHeight, int* waitTimeAfterPoint){
    if (*waitTimeAfterPoint > 0){
        return 3;
    }

    if(ball->direita){
        ball->destino.x += (ball->velocidade * VelocidadeDoJogo);
        if(ball->destino.x > (windowWidth - ball->destino.w)){
            ball->direita = false;
            ball->esquerda = true;
            return 4;
        }
    }

    if(ball->esquerda){
        ball->destino.x -= (ball->velocidade * VelocidadeDoJogo);
        if(ball->destino.x < 0){
            ball->esquerda = false;
            ball->direita = true;
            return 4;
        }
    }

    if(ball->cima){
        ball->destino.y-= (ball->velocidade * VelocidadeDoJogo);
        if(ball->destino.y < 0){
            return 1;
        }
    }

    if(ball->baixo){
        ball->destino.y += (ball->velocidade * VelocidadeDoJogo);
        if(ball->destino.y > (windowHeight - 10)){
           return 2;
        }
    }
    return 0;
}

void setBallDirectionAfterPoint(ball* ball){
    ball->esquerda = false;
    ball->direita = false;
    ball->cima = !ball->cima;
    ball->baixo = !ball->baixo;
}

void setInitialBallPosition(ball* ball,int windowWidth, int windowHeight){
    ball->origem.h = 160;
    ball->origem.w = 300;
    ball->origem.x = 0;
    ball->origem.y = 0;

    ball->destino.h = ball->origem.w / 15;
    ball->destino.w = ball->origem.w / 16;
    ball->destino.x = windowWidth / 2;
    ball->destino.y = windowHeight / 2;
}

void executaSom (SDL_AudioDeviceID id,  Uint32 length, Uint8 *buffer) {
    SDL_ClearQueuedAudio(id);
    SDL_QueueAudio(id, buffer, length);
    SDL_PauseAudioDevice(id, 0);
}
