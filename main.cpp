#include <iostream>
#include <SDL2/SDL.h>

#undef main
using namespace std;

struct player {
    bool esquerda;
    bool direita;
    SDL_Rect destino;
};

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

void movePlayers( player* player1, player* player2, int windowWidth){
   //colocar os ifs para detectar se a direcao esta ativa e modificar a posicao x do player
}

int main()
{
    int windowWidth  = 800;
    int windowHeight = 600;
    bool gameOver = false;

    player player1;
    player player2;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* janela = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* imgBackground = carregaImagemBMP("assets/elementosJogo/Background.bmp", renderizador);
    SDL_Texture* imgPlayer1 = carregaImagemBMP("assets/elementosJogo/Stick.bmp", renderizador);
    //SDL_Texture* imgPlayer2 = carregaImagemBMP("assets/elementosJogo/Stick01.bmp", renderizador);


    SDL_Rect origem;
    origem.x = 200;
    origem.y = 100;
    origem.h = 100;
    origem.w = 400;

    SDL_Rect destino;
    destino.h = 100;
    destino.w = 400;

     SDL_RenderCopy(renderizador, imgBackground, NULL, NULL);
     //SDL_RenderCopy(renderizador, imgPlayer1, NULL, NULL);
     //SDL_RenderCopy(renderizador, imgPlayer2, &origem, &destino);

    while (!gameOver) {
        SDL_Event evento;
        while(SDL_PollEvent(&evento) > 0){
            switch (evento.type) {
                case SDL_QUIT: gameOver = true;
                break;
            }

        getPlayersMovement(&evento,&player1,&player1);

        }


        SDL_RenderPresent(renderizador);

        SDL_Delay(1000 / 60);
    }

    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);

    SDL_Quit();
     return 0;
}

