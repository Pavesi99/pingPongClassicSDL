#include <iostream>
#include "singlePlayer.h"
#include "twoPlayers.h"
#include "menu.h"

#undef main

extern int windowHeight;
extern int windowWidth;

int main()
{
    bool running = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* janela = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    while (running) {
        switch (carregaMenu(renderizador)) {
            case 0:
                startSinglePlayerGame(renderizador);
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

