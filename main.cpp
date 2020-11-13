#include <iostream>
#include "game.h"

#undef main
using namespace std;

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
                        startGame();
                    } else if (evento.button.y > 142  && evento.button.y < 200 && evento.button.x > 285 && evento.button.x < 475) {
                        SDL_Log("Opcoes pressionado");
                    } else if (evento.button.y > 250 && evento.button.y < 300 && evento.button.x > 299 && evento.button.x < 425) {
                        SDL_Log("Sair...");
                        menu = false;
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
    } while (menu);

    SDL_DestroyWindow(janela);
    SDL_DestroyTexture(iniciar);
    SDL_DestroyTexture(opcoes);
    SDL_DestroyTexture(sair);

    SDL_Quit();
}


int main()
{
    int windowWidth  = 800;
    int windowHeight = 600;
    bool menu = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* janelaMenu = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janelaMenu, -1, SDL_RENDERER_ACCELERATED);

    carregaMenu(janelaMenu, renderizador, menu);

    SDL_DestroyWindow(janelaMenu);
    SDL_DestroyRenderer(renderizador);
    SDL_Quit();
    return 0;
}

