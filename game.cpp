#include "game.h"
//#include <SDL2/SDL_ttf.h>

/*SDL_Texture* criaFonte (SDL_Renderer* renderizador, const char* chat) {
    TTF_Font *fonte = TTF_OpenFont("arial.ttf", 12); // Defne fonte e seu tamanho
    SDL_Color corFonte = {255, 255, 255, 255}; // Define a cor da fonte

    SDL_Surface* texto = TTF_RenderText_Solid(fonte, chat , corFonte);
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderizador, texto);

    SDL_FreeSurface(texto);
    TTF_CloseFont(fonte);

    return textura;
}*/

SDL_Texture* carregaImagemBMP (const char* src, SDL_Renderer* renderizador) {
    SDL_Surface* imagem = SDL_LoadBMP(src);
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderizador, imagem);
    SDL_FreeSurface(imagem);

    return textura;
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

void movePlayer(player* player, int windowWidth){

    if(player->direita){
        player->destino.x += player->velocidade;
        if(player->destino.x > (windowWidth - player->destino.w)){
            player->destino.x = (windowWidth - player->destino.w);
        }
    }

    if(player->esquerda){
        player->destino.x -= player->velocidade;
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
        ball->destino.x += ball->velocidade;
        if(ball->destino.x > (windowWidth - ball->destino.w)){
            ball->direita = false;
            ball->esquerda = true;
        }
    }

    if(ball->esquerda){
        ball->destino.x -= ball->velocidade;
        if(ball->destino.x < 0){
            ball->esquerda = false;
            ball->direita = true;
        }
    }

    if(ball->cima){
        ball->destino.y-= ball->velocidade;
        if(ball->destino.y < 0){
            return 1;
        }
    }

    if(ball->baixo){
        ball->destino.y += ball->velocidade;
        if(ball->destino.y > (windowHeight - 10)){
           return 2;
        }
    }
    return 0;
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
    player1->destino.x = 300;
    player1->destino.y = 570;
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

void checkBallCollision(ball* ball, player* player1, player* player2){
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
    }
}

void attMoves (player* jogador, ball* bola) {

}

void startGame () {
    int windowWidth  = 800;
    int windowHeight = 600;
    bool gameOver = false;
    int waitTimeAfterPoint = 0;


    player player1;
    player player2;
    ball ball;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* janela = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    //SDL_Texture* pontuacao = criaFonte(renderizador, "Pontuação");
    SDL_Texture* imgPlayer1 = carregaImagemBMP("assets/elementosJogo/Stick.bmp", renderizador);
    SDL_Texture* imgPlayer2 = carregaImagemBMP("assets/elementosJogo/Stick01.bmp", renderizador);
    SDL_Texture* imgBall = carregaImagemBMP("assets/elementosJogo/Ball.bmp", renderizador);
    player1.texture = imgPlayer1;
    player2.texture = imgPlayer2;
    ball.texture = imgBall;


    setInitialBallPosition(&ball,windowWidth, windowHeight);
    setInitialPlayersPositions(&player1,&player2);

     SDL_RenderCopy(renderizador, player1.texture, &player1.origem, &player1.destino);
     SDL_RenderCopy(renderizador, player2.texture, &player2.origem, &player2.destino);
     SDL_RenderCopy(renderizador, ball.texture, &ball.origem, &ball.destino);

    while (!gameOver) {

        SDL_RenderClear(renderizador);

        SDL_Event evento;
        while(SDL_PollEvent(&evento) > 0){
            switch (evento.type) {
                case SDL_QUIT:
                    gameOver = true;
                break;
            }

            getPlayersMovement(&evento,&player1,&player2);
        }

        movePlayer(&player1, windowWidth);
        movePlayer(&player2, windowWidth);

        checkBallCollision(&ball,&player1,&player2);

        SDL_RenderCopy(renderizador, player2.texture, &player2.origem,&player2.destino );
        SDL_RenderCopy(renderizador, player1.texture, &player1.origem,&player1.destino );
        SDL_RenderCopy(renderizador, ball.texture, &ball.origem, &ball.destino);

        SDL_RenderPresent(renderizador);
        SDL_Delay(1000 / 60);

        switch(moveBall(&ball,windowWidth,windowHeight, &waitTimeAfterPoint )){
            case 1:
                player1.pontos++;
                setBallDirectionAfterPoint(&ball);
                setInitialBallPosition(&ball,windowWidth, windowHeight);
                setInitialPlayersPositions(&player1,&player2);
                waitTimeAfterPoint = 180;

                //bola inicia indo para baixo
                //bola no meio, restart
            break;
            case 2:
                player2.pontos++;
                setBallDirectionAfterPoint(&ball);
                setInitialBallPosition(&ball,windowWidth, windowHeight);
                setInitialPlayersPositions(&player1,&player2);
                waitTimeAfterPoint = 180;

                //bola inicia indo para cima
                //bola no meio, restart
            break;
            case 3:
            waitTimeAfterPoint--;
            break;
        }
    }


    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);
    SDL_Quit();
}
