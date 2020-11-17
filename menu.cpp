#include "menu.h"
#include "game.h"

int windowWidth  = 800;
int windowHeight = 600;

int carregaMenu (SDL_Renderer* renderizador) {
    bool menu = true;
    int retorno = 0;

    SDL_RenderClear(renderizador);

    SDL_Texture* iniciar = carregaImagemBMP("assets/menu/iniciar.bmp", renderizador);
    SDL_Texture* opcoes = carregaImagemBMP("assets/menu/opcoes.bmp", renderizador);
    SDL_Texture* sair = carregaImagemBMP("assets/menu/sair.bmp", renderizador);

    do {
        //SDL_RenderCopy(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento)) {
            switch(evento.type) {
                case SDL_QUIT:
                    SDL_Quit();
                break;

                case SDL_MOUSEBUTTONDOWN:
                    if(evento.button.y > 25 && evento.button.y < 100 && evento.button.x > 299 && evento.button.x < 475) {
                        retorno = 0;
                        menu = false;
                    } else if (evento.button.y > 142  && evento.button.y < 200 && evento.button.x > 285 && evento.button.x < 475) {
                        optionsMenu(renderizador);
                    } else if (evento.button.y > 250 && evento.button.y < 300 && evento.button.x > 299 && evento.button.x < 425) {
                        retorno = 1;
                        SDL_Quit();
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

void optionsMenu (SDL_Renderer* renderizador) {
    int opcoes = true;

    SDL_RenderClear(renderizador);

    SDL_Texture* velocidade = carregaImagemBMP("assets/menu/velocidadeJogo.bmp", renderizador);
    SDL_Texture* voltar = carregaImagemBMP("assets/menu/volta.bmp", renderizador);

       do {
           SDL_Event evento;
           while(SDL_PollEvent(&evento)) {
               switch(evento.type) {
                    case SDL_QUIT:
                        opcoes = false;
                    break;

                    case SDL_MOUSEBUTTONDOWN:
                       if (evento.button.y > 142  && evento.button.y < 200 && evento.button.x > 285 && evento.button.x < 475) {
                            velocidades(renderizador);
                       } else if (evento.button.y > 250 && evento.button.y < 300 && evento.button.x > 299 && evento.button.x < 425) {
                           opcoes = false;
                       }
                    break;
               }
           }

           SDL_Rect velocidadesOri = {0, 0, 620, 120};
           SDL_Rect velocidadesDest = {100, 125, 620, 101};
           SDL_RenderCopy(renderizador, velocidade, &velocidadesOri, &velocidadesDest);

           SDL_Rect voltaOri = {0, 0, 490, 100};
           SDL_Rect voltaDest = {80, 225, 615, 101};
           SDL_RenderCopy(renderizador, voltar, &voltaOri, &voltaDest);

           SDL_RenderPresent(renderizador);

       } while (opcoes);

       SDL_RenderClear(renderizador);
       SDL_DestroyTexture(velocidade);
       SDL_DestroyTexture(voltar);
}

void velocidades (SDL_Renderer* renderizador) {
    bool vel = true;

    SDL_RenderClear(renderizador);

    SDL_Texture* normal = carregaImagemBMP("assets/menu/modoNormal.bmp", renderizador);
    SDL_Texture* rapido = carregaImagemBMP("assets/menu/modoRapido.bmp", renderizador);
    SDL_Texture* voltar = carregaImagemBMP("assets/menu/volta.bmp", renderizador);

    do {
        SDL_Event evento;
        while(SDL_PollEvent(&evento)) {
            switch(evento.type) {
                 case SDL_QUIT:
                     vel = false;
                 break;

                 case SDL_MOUSEBUTTONDOWN:
                    if(evento.button.y > 25 && evento.button.y < 80 && evento.button.x > 180 && evento.button.x < 580) {
                        vel = false;
                    } else if (evento.button.y > 132  && evento.button.y < 202 && evento.button.x > 180 && evento.button.x < 565) {
                        vel = false;
                    } else if (evento.button.y > 250 && evento.button.y < 295 && evento.button.x > 220 && evento.button.x < 440) {
                        vel = false;
                    }
                 break;
            }
        }

        SDL_Rect normalOri = {0, 0, 490, 100};
        SDL_Rect normalDest = {0, 0, 615, 101};
        SDL_RenderCopy(renderizador, normal, &normalOri, &normalDest);

        SDL_Rect rapidoOri = {0, 0, 490, 100};
        SDL_Rect rapidoDest = {0, 102, 615, 101};
        SDL_RenderCopy(renderizador, rapido, &rapidoOri, &rapidoDest);

        SDL_Rect voltaOri = {0, 0, 490, 100};
        SDL_Rect voltaDest = {0, 203, 615, 101};
        SDL_RenderCopy(renderizador, voltar, &voltaOri, &voltaDest);

        SDL_RenderPresent(renderizador);

    } while (vel);

    SDL_RenderClear(renderizador);
    SDL_DestroyTexture(normal);
    SDL_DestroyTexture(voltar);
    SDL_DestroyTexture(rapido);
}
