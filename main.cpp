#include <iostream>
#include "game.h"

#undef main
using namespace std;

int carregaMenu (SDL_Renderer* renderizador) {

    bool menu = true;
    int retorno = 0;

    SDL_Texture* iniciar = carregaImagemBMP("assets/menu/iniciar.bmp", renderizador);
    SDL_Texture* opcoes = carregaImagemBMP("assets/menu/opcoes.bmp", renderizador);
    SDL_Texture* sair = carregaImagemBMP("assets/menu/sair.bmp", renderizador);

    do {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento)) {
            switch(evento.type) {
                case SDL_QUIT:
                    menu = false;
                    SDL_Quit();
                break;

                case SDL_MOUSEBUTTONDOWN:
                    if(evento.button.y > 25 && evento.button.y < 100 && evento.button.x > 299 && evento.button.x < 475) {
                        retorno = 0;
                         menu = false;
                    } else if (evento.button.y > 142  && evento.button.y < 200 && evento.button.x > 285 && evento.button.x < 475) {
                        SDL_Log("Opcoes pressionado");
                    } else if (evento.button.y > 250 && evento.button.y < 300 && evento.button.x > 299 && evento.button.x < 425) {
                        SDL_Log("Sair...");
                        menu = false;
                        retorno = 1;
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

    SDL_RenderClear(renderizador);
    SDL_DestroyTexture(iniciar);
    SDL_DestroyTexture(opcoes);
    SDL_DestroyTexture(sair);

    return retorno;

}

int main()
{
    int windowWidth  = 800;
    int windowHeight = 600;
    bool running = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* janela = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    while (running) {
        switch (carregaMenu(renderizador)) {
            case 0:
                startGame(renderizador);
            break;
            case 1:
                running = false;
            break;
        }
    }

    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);
    SDL_Quit();
    return 0;
}

