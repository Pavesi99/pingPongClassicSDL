#include <iostream>
#include <SDL2/SDL.h>

#undef main
using namespace std;

struct player {
    bool esquerda = false;
    bool direita = false;
    SDL_Rect destino;
    SDL_Rect origem;
    SDL_Texture* texture;
};

struct ball {
    bool esquerda = true;
    bool direita = false;
    bool cima = false;
    bool baixo = false;
    SDL_Rect destino;
    SDL_Rect origem;
    SDL_Texture* texture;
};

SDL_Texture* carregaImagemBMP (const char* src, SDL_Renderer* renderizador) {
    SDL_Surface* imagem = SDL_LoadBMP(src);
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderizador, imagem);
    SDL_FreeSurface(imagem);

    return textura;
}

void carregaMenu (SDL_Window* janela, SDL_Renderer* renderizador, bool menu) {

    SDL_Texture* iniciar = carregaImagemBMP("assets/menu/iniciar.bmp", renderizador);
    SDL_Texture* opcoes = carregaImagemBMP("assets/menu/opcoes.bmp", renderizador);
    SDL_Texture* sair = carregaImagemBMP("assets/menu/sair.bmp", renderizador);

    do {
        SDL_Event evento;
        while (SDL_PollEvent(&evento)) {
            switch(evento.type) {
                case SDL_QUIT:
                    menu = false;
                break;

                case SDL_MOUSEBUTTONDOWN:
                    if(evento.button.y > 20 && evento.button.y < 100) {
                        SDL_Log("Iniciar Pressionado");
                    } else if (evento.button.y > 115  && evento.button.y < 200) {
                        SDL_Log("Opcoes pressionado");
                    } else if (evento.button.y > 250 && evento.button.y < 300) {
                        SDL_Log("Sair...");
                        SDL_Quit();
                    }


            }
        }

        SDL_Rect iniciarOri = {0, 0, 500, 100};
        SDL_Rect iniciarDest = {100, 20, 615, 101};
        SDL_RenderCopy(renderizador, iniciar, &iniciarOri, &iniciarDest);
        SDL_RenderPresent(renderizador);

        SDL_Rect opcoesOri = {0, 0, 490, 100};
        SDL_Rect opcoesDest = {100, 125, 615, 101};
        SDL_RenderCopy(renderizador, opcoes, &opcoesOri, &opcoesDest);
        SDL_RenderPresent(renderizador);

        SDL_Rect sairOri = {0, 0, 490, 100};
        SDL_Rect sairDest = {105, 225, 615, 101};
        SDL_RenderCopy(renderizador, sair, &sairOri, &sairDest);
        SDL_RenderPresent(renderizador);

        SDL_DestroyWindow(janela);


    } while (menu);

    SDL_DestroyWindow(janela);
    SDL_DestroyTexture(iniciar);
    SDL_DestroyTexture(opcoes);
    SDL_DestroyTexture(sair);
}

void getPlayersMovement(SDL_Event* evento, player* player1, player* player2) {
                switch (evento->type) {
                case SDL_KEYDOWN:
                    switch( evento->key.keysym.sym ){
                        case SDLK_LEFT:
                            player2->esquerda = true;
                            break;
                        case SDLK_RIGHT:
                            player2->direita = true;
                            break;
                        case SDLK_a:
                            player1->esquerda = true;
                            break;
                        case SDLK_d:
                            player1->direita = true;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch( evento->key.keysym.sym ){
                        case SDLK_LEFT:
                            player2->esquerda = false;
                            break;
                        case SDLK_RIGHT:
                            player2->direita = false;
                            break;
                        case SDLK_a:
                            player1->esquerda = false;
                            break;
                        case SDLK_d:
                            player1->direita = false;
                            break;
                    }
                    break;
                }
}

bool movePlayer(player* player, int windowWidth, SDL_Renderer* renderizador){
    if(player->direita){
        player->destino.x += 5;
        if(player->destino.x > (windowWidth - player->destino.w)){
            player->destino.x = (windowWidth - player->destino.w);
        }
        SDL_RenderClear(renderizador);
        SDL_RenderCopy(renderizador, player->texture, &player->origem,&player->destino );
        return true;
    }

    if(player->esquerda){
        player->destino.x -= 5;
        if(player->destino.x < 0){
            player->destino.x = 0;
        }
        SDL_RenderClear(renderizador);
        SDL_RenderCopy(renderizador, player->texture, &player->origem,&player->destino );
        return true;
    }
    return false;
}

void moveBall(ball* ball, int windowWidth, int windowHeight, SDL_Renderer* renderizador){
    if(ball->direita){
        ball->destino.x ++;
        if(ball->destino.x > (windowWidth - ball->destino.w)){
            ball->direita = false;
            ball->esquerda = true;
        }
    }

    if(ball->esquerda){
        ball->destino.x --;
        if(ball->destino.x < 0){
            ball->esquerda = false;
            ball->direita = true;
        }
    }

    if(ball->cima){
        ball->destino.y--;
        if(ball->destino.y < -5){
            //ponto player1
        }
    }

    if(ball->baixo){
        ball->destino.y ++;
        if(ball->destino.y > (windowHeight + 50)){
            //ponto player2
        }
    }
}

void setInitialPlayersPositions(player* player1, player* player2){
    player2->origem.h = 200;
    player2->origem.w = 800;
    player2->origem.x = 0;
    player2->origem.y = 0;

    player2->destino.h = 40;
    player2->destino.w = player2->origem.w / 8;
    player2->destino.x = 300;
    player2->destino.y = 0;

    player1->origem.h = 200;
    player1->origem.w = 800;
    player1->origem.x = 0;
    player1->origem.y = 0;

    player1->destino.h = 40;
    player1->destino.w = player1->origem.w / 8;
    player1->destino.x = 600;
    player1->destino.y = 580;
}

void setInitialBallPosition(ball* ball,int windowWidth, int windowHeight){
    ball->origem.h = 160;
    ball->origem.w = 300;
    ball->origem.x = 0;
    ball->origem.y = 0;

    ball->destino.h = 40;
    ball->destino.w = ball->origem.w / 8;
    ball->destino.x = windowWidth / 2;
    ball->destino.y = windowHeight / 2;
}



int main()
{
    int windowWidth  = 800;
    int windowHeight = 600;
    bool gameOver = false;
    bool menu = true;

    player player1;
    player player2;
    ball ball;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* janela = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Window* janelaMenu = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    carregaMenu(janelaMenu, renderizador, menu);

    SDL_Texture* imgPlayer1 = carregaImagemBMP("assets/elementosJogo/Stick.bmp", renderizador);
    SDL_Texture* imgPlayer2 = carregaImagemBMP("assets/elementosJogo/Stick01.bmp", renderizador);
    SDL_Texture* imgBall = carregaImagemBMP("assets/elementosJogo/Ball.bmp", renderizador);
    player1.texture = imgPlayer1;
    player2.texture = imgPlayer2;
    ball.texture = imgBall;


    setInitialBallPosition(&ball,windowWidth, windowHeight);
    setInitialPlayersPositions(&player1,&player2);

     //SDL_RenderCopy(renderizador, imgBackground, NULL, NULL);
     SDL_RenderCopy(renderizador, player1.texture, &player1.origem, &player1.destino);
     SDL_RenderCopy(renderizador, player2.texture, &player2.origem, &player2.destino);
     SDL_RenderCopy(renderizador, ball.texture, &ball.origem, &ball.destino);

    while (!gameOver) {

        SDL_Event evento;
        while(SDL_PollEvent(&evento) > 0){
            switch (evento.type) {
                case SDL_QUIT: gameOver = true;
                break;
            }

            getPlayersMovement(&evento,&player1,&player2);
        }

        if(movePlayer(&player1, windowWidth,renderizador)){
           SDL_RenderCopy(renderizador, player2.texture, &player2.origem,&player2.destino );
        }

        if(movePlayer(&player2, windowWidth,renderizador)){
             SDL_RenderCopy(renderizador, player1.texture, &player1.origem,&player1.destino );
        }

        SDL_RenderPresent(renderizador);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);

    SDL_Quit();
     return 0;
}

