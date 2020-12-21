#include "game.h"

#ifndef MENU_H
#define MENU_H
int carregaMenu (SDL_Renderer* renderizador);
int menu (SDL_Renderer* renderizador);
int modeGame (SDL_Renderer* renderizador);
int optionsMenu (SDL_Renderer* renderizador);
void velocidades (SDL_Renderer* renderizador);
void pontos (SDL_Renderer* renderizador);
void help (SDL_Renderer* renderizador);
#endif // MENU_H
