#include <iostream>
#include "game.h"
#include "menu.h"

#undef main

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

