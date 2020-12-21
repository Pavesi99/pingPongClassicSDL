#include "game.h"
#include "menu.h"

int VelocidadeDoJogo = 1;

extern int windowWidth;
extern int windowHeight;

SDL_Texture* carregaImagemBMP (const char* src, SDL_Renderer* renderizador) {
    SDL_Surface* imagem = SDL_LoadBMP(src);
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderizador, imagem);
    SDL_FreeSurface(imagem);

    return textura;
}

void setInitialPlayersPositions(player* player1, player* player2){
    player2->origem.h = 200;
    player2->origem.w = 800;
    player2->origem.x = 0;
    player2->origem.y = 0;

    player2->destino.h = 40;
    player2->destino.w = windowWidth / 8;
    player2->destino.x = windowWidth / 2;
    player2->destino.y = 0;

    player1->origem.h = 200;
    player1->origem.w = 800;
    player1->origem.x = 0;
    player1->origem.y = 0;

    player1->destino.h = 40;
    player1->destino.w = windowWidth / 8;
    player1->destino.x = windowWidth / 2;
    player1->destino.y = windowHeight - 30;
}

bool checkBallCollision(ball* ball, player* player1, player* player2){
    if(ball->destino.x >= player2->destino.x
            && ball->destino.x <= (player2->destino.x + player2->destino.w)
            && ball->destino.y <= (player2->destino.y + (player2->destino.h /2))
            ){
        ball->cima = false;
        ball->baixo = true;

        if(ball->destino.x <= (player2->destino.x + 5)){
            ball->esquerda = true;
            ball->direita = false;
        }else if(ball->destino.x >= (player2->destino.x + player2->destino.w - 5) ){
            ball->esquerda = false;
            ball->direita = true;
        }else {
            if( ball->esquerda == false && ball->direita == false){
                ball->esquerda = true;
            }
        }
        return true;
    }
    if(ball->destino.x >= player1->destino.x
            && ball->destino.x <= (player1->destino.x + player1->destino.w)
            && ball->destino.y >= (player1->destino.y - (player1->destino.h / 2))
            ){
        ball->cima = true;
        ball->baixo = false;
        if(ball->destino.x <= (player1->destino.x + 5)){
            ball->esquerda = true;
            ball->direita = false;
        }else if(ball->destino.x >= (player1->destino.x + player1->destino.w  - 5)){
            ball->esquerda = false;
            ball->direita = true;
        }else {
            if( ball->esquerda == false && ball->direita == false){
                ball->esquerda = true;
            }
        }
        return true;
    }
    return false;
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

int moveBall(ball* ball, int windowWidth,  int windowHeight, int* waitTimeAfterPoint){
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
        if(ball->destino.y > (windowHeight - 25)){
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
    ball->origem.h = windowHeight / 2;
    ball->origem.w = windowHeight / 2;
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
