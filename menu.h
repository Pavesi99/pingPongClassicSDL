#include <SDL2/SDL.h>
#include "game.h"

#ifndef MENU_H
#define MENU_H

void carregaMenu (SDL_Window* janela, SDL_Renderer* renderizador, bool menu);
void optionsMenu ();
void velocidades ();

#endif // MENU_H
