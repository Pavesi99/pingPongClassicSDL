
#include "singlePlayer.h"
#include "twoPlayers.h"
#include "menu.h"
#include "game.h"

#undef main

extern int windowHeight;
extern int windowWidth;

int main()
{
    bool running = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(janela, &windowWidth, &windowHeight);

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *background = Mix_LoadMUS("assets/som/tema.wav");

    while (running)
    {
        Mix_PlayMusic(background, -1);
        switch (carregaMenu(renderizador))
        {
        case 0:
            switch (menu(renderizador))
            {
            case 1:
                switch (modeGame(renderizador))
                {
                case 1:
                    startSinglePlayerGame(renderizador);
                    break;
                case 2:
                    startTwoPlayersGame(renderizador);
                    break;
                case 3:
                    //Multiplayer
                    break;
                }
                break;

            case 2:
                switch (optionsMenu(renderizador))
                {
                case 1:
                    SDL_DestroyWindow(janela);
                    SDL_DestroyRenderer(renderizador);
                    SDL_Window *modoJanela = SDL_CreateWindow("Ping Pong Classico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
                    SDL_Renderer *renderizador1 = SDL_CreateRenderer(modoJanela, -1, SDL_RENDERER_ACCELERATED);
                    SDL_RenderPresent(renderizador1);
                    break;
                }
            }
            break;
        case 1:
            running = false;
            break;
        }
    }

    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}
