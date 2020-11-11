#include <iostream>
#include <SDL2/SDL.h>

#undef main
using namespace std;

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
                    if(evento.button.y > 25 && evento.button.y < 100 && evento.button.x > 299 && evento.button.x < 475) {
                        SDL_Log("Iniciar Pressionado");
                    } else if (evento.button.y > 142  && evento.button.y < 200 && evento.button.x > 285 && evento.button.x < 475) {
                        SDL_Log("Opcoes pressionado");
                    } else if (evento.button.y > 250 && evento.button.y < 300 && evento.button.x > 299 && evento.button.x < 425) {
                        SDL_Log("Sair...");
                        SDL_Quit();
                    }


            }
        }

        SDL_Rect iniciarOri = {0, 0, 500, 100};
        SDL_Rect iniciarDest = {0, 20, 615, 101};
        SDL_RenderCopy(renderizador, iniciar, &iniciarOri, &iniciarDest);

        SDL_Rect opcoesOri = {0, 0, 490, 100};
        SDL_Rect opcoesDest = {0, 125, 615, 101};
        SDL_RenderCopy(renderizador, opcoes, &opcoesOri, &opcoesDest);

        SDL_Rect sairOri = {0, 0, 490, 100};
        SDL_Rect sairDest = {0, 225, 615, 101};
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

void movePlayer(player* player, int windowWidth){
    int velocidade = 5;

    if(player->direita){
        player->destino.x += velocidade;
        if(player->destino.x > (windowWidth - player->destino.w)){
            player->destino.x = (windowWidth - player->destino.w);
        }
    }

    if(player->esquerda){
        player->destino.x -= velocidade;
        if(player->destino.x < 0){
            player->destino.x = 0;
        }
    }
}

int moveBall(ball* ball, int windowWidth, int windowHeight, int* waitTimeAfterPoint = 0 ){

    if (*waitTimeAfterPoint > 0){
        return 3;
    }

    int velocidade = 6;

    if(ball->direita){
        ball->destino.x +=velocidade;
        if(ball->destino.x > (windowWidth - ball->destino.w)){
            ball->direita = false;
            ball->esquerda = true;
        }
    }

    if(ball->esquerda){
        ball->destino.x -=velocidade;
        if(ball->destino.x < 0){
            ball->esquerda = false;
            ball->direita = true;
        }
    }

    if(ball->cima){
        ball->destino.y-=velocidade;
        if(ball->destino.y < -20){
            return 1;
        }
    }

    if(ball->baixo){
        ball->destino.y +=velocidade;
        if(ball->destino.y > (windowHeight + 20)){
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



int main()
{
    int windowWidth  = 800;
    int windowHeight = 600;
    bool gameOver = false;
    bool menu = true;
    int waitTimeAfterPoint = 0;

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

     SDL_RenderCopy(renderizador, player1.texture, &player1.origem, &player1.destino);
     SDL_RenderCopy(renderizador, player2.texture, &player2.origem, &player2.destino);
     SDL_RenderCopy(renderizador, ball.texture, &ball.origem, &ball.destino);

    while (!gameOver) {

        SDL_RenderClear(renderizador);

        SDL_Event evento;
        while(SDL_PollEvent(&evento) > 0){
            switch (evento.type) {
                case SDL_QUIT: gameOver = true;
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
                waitTimeAfterPoint = 180;

                //bola inicia indo para baixo
                //bola no meio, restart
                cout << "jogador 1:" << player1.pontos << "\n";
                cout << "jogador 2:" << player2.pontos << "\n";

            break;
            case 2:
                player2.pontos++;
                setBallDirectionAfterPoint(&ball);
                setInitialBallPosition(&ball,windowWidth, windowHeight);

                waitTimeAfterPoint = 180;

                //bola inicia indo para cima
                //bola no meio, restart
                cout << "jogador 1:" << player1.pontos << "\n";
                cout << "jogador 2:" << player2.pontos << "\n";
            break;
            case 3:
            waitTimeAfterPoint--;
            break;
        }

    }

    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);

    SDL_Quit();
     return 0;
}

