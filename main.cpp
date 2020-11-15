#include <iostream>
#include "game.h"
#include "menu.h"

#undef main
using namespace std;

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

