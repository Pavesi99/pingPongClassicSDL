#include "menu.h"
#include "game.h"

int windowWidth  = 800;
int windowHeight = 600;

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
                        SDL_Quit();
                        startGame();
                    } else if (evento.button.y > 142  && evento.button.y < 200 && evento.button.x > 285 && evento.button.x < 475) {
                        optionsMenu();
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
    SDL_DestroyRenderer(renderizador);

    SDL_Quit();
}

void optionsMenu () {
    int opcoes = true;

    SDL_Window* janela = SDL_CreateWindow("Opções", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

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
                       if(evento.button.y > 25 && evento.button.y < 100 && evento.button.x > 299 && evento.button.x < 475) {
                            SDL_Log("clique");
                       } else if (evento.button.y > 142  && evento.button.y < 200 && evento.button.x > 285 && evento.button.x < 475) {
                            velocidades();
                       } else if (evento.button.y > 250 && evento.button.y < 300 && evento.button.x > 299 && evento.button.x < 425) {
                           carregaMenu(janela, renderizador, opcoes);
                       }
                    break;
               }
           }

           SDL_Rect velocidadesOri = {0, 0, 490, 100};
           SDL_Rect velocidadesDest = {0, 125, 615, 101};
           SDL_RenderCopy(renderizador, velocidade, &velocidadesOri, &velocidadesDest);

           SDL_Rect voltaOri = {0, 0, 490, 100};
           SDL_Rect voltaDest = {0, 225, 615, 101};
           SDL_RenderCopy(renderizador, voltar, &voltaOri, &voltaDest);

           SDL_RenderPresent(renderizador);

       } while (opcoes);

       SDL_DestroyTexture(velocidade);
       SDL_DestroyTexture(voltar);
       SDL_DestroyWindow(janela);
       SDL_DestroyRenderer(renderizador);

       SDL_Quit();
}

void velocidades () {
    bool vel = true;

    SDL_Window* janela = SDL_CreateWindow("Velocidades", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

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
                          optionsMenu();
                    } else if (evento.button.y > 132  && evento.button.y < 202 && evento.button.x > 180 && evento.button.x < 565) {
                          optionsMenu();
                    } else if (evento.button.y > 250 && evento.button.y < 295 && evento.button.x > 220 && evento.button.x < 440) {
                          optionsMenu();
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

    SDL_DestroyTexture(normal);
    SDL_DestroyTexture(voltar);
    SDL_DestroyTexture(rapido);
    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);
    SDL_Quit();
}


