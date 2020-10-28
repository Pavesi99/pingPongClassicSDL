#include <iostream>
#include <SDL2/SDL.h>

#undef main
using namespace std;

SDL_Texture* carregaImagemBMP (const char* src, SDL_Renderer* renderizador) {
    SDL_Surface* imagem = SDL_LoadBMP(src);
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderizador, imagem);
    SDL_FreeSurface(imagem);

    return textura;
}

int main()
{
    int width  = 800;
    int height = 600;
    bool gameOver = false;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* janela = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* imgBackground = carregaImagemBMP("assets/elementosJogo/Background.bmp", renderizador);
    SDL_Texture* imgPlayer1 = carregaImagemBMP("assets/elementosJogo/Stick.bmp", renderizador);
    //SDL_Texture* imgPlayer2 = carregaImagemBMP("assets/elementosJogo/Stick01.bmp", renderizador);

    while (!gameOver) {
        SDL_Event* evento;
        SDL_PollEvent(evento);
        SDL_RenderClear(renderizador);

        SDL_RenderCopy(renderizador, imgBackground, NULL, NULL);

        SDL_Rect origem;
        origem.x = 200;
        origem.y = 100;
        origem.h = 100;
        origem.w = 400;

        SDL_Rect destino;
        destino.h = 100;
        destino.w = 400;

        SDL_RenderCopy(renderizador, imgPlayer1, NULL, NULL);
        //SDL_RenderCopy(renderizador, imgPlayer2, origem, NULL);
        SDL_RenderPresent(renderizador);

        SDL_Delay(1000 / 60);
    }

    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);

    SDL_Quit();
     return 0;
}

