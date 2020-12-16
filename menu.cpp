#include "menu.h"

int windowWidth  = 800;
int windowHeight = 600;
int delayMenu = 150;

extern int VelocidadeDoJogo;

int carregaMenu (SDL_Renderer* renderizador) {
    bool main = true;
    int retorno = 0;

    SDL_RenderClear(renderizador);

    SDL_Texture* inicio = carregaImagemBMP("assets/menu/iniciar.bmp", renderizador);

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_AudioSpec transitionSpec;
    Uint32 transitionLength;
    Uint8 *transitionBuffer;

    SDL_AudioSpec temaSpec;
    Uint32 temaLength;
    Uint8 *temaBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    SDL_LoadWAV("assets/som/transition.wav", &transitionSpec, &transitionBuffer, &transitionLength);
    SDL_AudioDeviceID transitionId = SDL_OpenAudioDevice(NULL, 0, &transitionSpec, NULL, 0);

    SDL_LoadWAV("assets/som/tema2.wav", &temaSpec, &temaBuffer, &temaLength);
    SDL_AudioDeviceID temaId = SDL_OpenAudioDevice(NULL, 0, &temaSpec, NULL, 0);

    do {
          SDL_RenderClear(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento)) {
            switch(evento.type) {
                case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;

                case SDL_MOUSEBUTTONDOWN:
                    if(evento.button.y > 505 && evento.button.y < 560 && evento.button.x > 299 && evento.button.x < 475) {
                        executaSom(transitionId, transitionLength, transitionBuffer);
                        retorno = 0;
                        SDL_Delay(delayMenu);
                        main = false;
                    }
                break;
            }
        }

        SDL_Rect iniciarOri = {0, 0, 800, 600};
        SDL_Rect iniciarDest = {0, 0, 800, 600};
        SDL_RenderCopy(renderizador, inicio, &iniciarOri, &iniciarDest);

        SDL_RenderPresent(renderizador);
    } while (main);

    //Mix_FreeMusic(background);
    SDL_RenderClear(renderizador);
    SDL_CloseAudioDevice(paddleHitId);
    SDL_CloseAudioDevice(transitionId);
    SDL_DestroyTexture(inicio);

    return retorno;
}

int menu (SDL_Renderer* renderizador) {
    int opcoes = true;
    int retorno = 0;

    SDL_RenderClear(renderizador);

    SDL_Texture* menu = carregaImagemBMP("assets/menu/menu.bmp", renderizador);

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

       do {
           SDL_RenderClear(renderizador);
           SDL_Event evento;
           while(SDL_PollEvent(&evento)) {
               switch(evento.type) {
                    case SDL_QUIT:
                   SDL_Quit();
                   exit(0);
                    break;

                    case SDL_MOUSEBUTTONDOWN:
                       if (evento.button.y > 180  && evento.button.y < 230 && evento.button.x > 285 && evento.button.x < 475) {
                           executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                           retorno = 1;
                           SDL_Delay(delayMenu);
                           opcoes = false;
                       } else if (evento.button.y > 239 && evento.button.y < 293 && evento.button.x > 299 && evento.button.x < 425) {
                           executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                           optionsMenu(renderizador);
                           SDL_Delay(delayMenu);
                           opcoes = false;
                       } else if (evento.button.y > 299 && evento.button.y < 355 && evento.button.x > 299 && evento.button.x < 425) {
                           executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                           SDL_Delay(delayMenu);
                       } else if (evento.button.y > 358 && evento.button.y < 410 && evento.button.x > 299 && evento.button.x < 425) {
                           executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                           retorno = 2;
                           SDL_Delay(delayMenu);
                           SDL_Quit();
                           exit(0);
                       }
                    break;
               }
           }

           SDL_Rect menuOri = {0, 0, 800, 600};
           SDL_Rect menuDest = {0, 0, 800, 600};
           SDL_RenderCopy(renderizador, menu, &menuOri, &menuDest);

           SDL_RenderPresent(renderizador);

       } while (opcoes);

       SDL_RenderClear(renderizador);
       SDL_DestroyTexture(menu);
       SDL_CloseAudioDevice(paddleHitId);

       return retorno;
}

int modeGame (SDL_Renderer* renderizador) {
    int mode = true;
    int retorno = 0;

    SDL_Texture* modo = carregaImagemBMP("assets/menu/modo.bmp", renderizador);
    SDL_RenderClear(renderizador);
    do {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while(SDL_PollEvent(&evento)) {
            switch(evento.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);
                 break;

                 case SDL_MOUSEBUTTONDOWN:
                    if (evento.button.y > 190  && evento.button.y < 255 && evento.button.x > 285 && evento.button.x < 475) {
                        //executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        retorno = 1;
                        mode = false;
                    } else if (evento.button.y > 310 && evento.button.y < 375 && evento.button.x > 299 && evento.button.x < 425) {
                        retorno = 2;
                        mode = false;
                        SDL_Delay(delayMenu);
                    }
                 break;

                 case SDL_KEYDOWN:
                    switch( evento.key.keysym.sym ){
                        case SDLK_ESCAPE:
                            mode = false;
                        break;
                    }
            }
        }

        SDL_Rect modeOri = {0, 0, 800, 600};
        SDL_Rect modeDest = {0, 0, 800, 600};
        SDL_RenderCopy(renderizador, modo, &modeOri, &modeDest);

        SDL_RenderPresent(renderizador);

    } while (mode);

    return retorno;
}

void optionsMenu (SDL_Renderer* renderizador) {
    bool options = true;

    SDL_RenderClear(renderizador);

    SDL_Texture* som = carregaImagemBMP("assets/menu/options.bmp", renderizador);
    SDL_Texture* mute = carregaImagemBMP("assets/menu/optionsS.bmp", renderizador);

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    do {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while(SDL_PollEvent(&evento)) {
            switch(evento.type) {
                 case SDL_QUIT:
                     SDL_Quit();
                     exit(0);
                 break;

                 case SDL_MOUSEBUTTONDOWN:
                    if(evento.button.y > 25 && evento.button.y < 80 && evento.button.x > 180 && evento.button.x < 580) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                        options = false;
                    } else if (evento.button.y > 132  && evento.button.y < 202 && evento.button.x > 180 && evento.button.x < 565) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                        options = false;
                    } else if (evento.button.y > 250 && evento.button.y < 295 && evento.button.x > 220 && evento.button.x < 440) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                        options = false;

                    }
                 break;
            }
        }

        SDL_Rect somOri = {0, 0, 800, 600};
        SDL_Rect somDest = {0, 0, 800, 600};
        SDL_RenderCopy(renderizador, som, &somOri, &somDest);

        SDL_Rect muteOri = {0, 0, 800, 600};
        SDL_Rect muteDest = {0, 0, 800, 600};
        SDL_RenderCopy(renderizador, mute, &muteOri, &muteDest);

        SDL_RenderPresent(renderizador);
    } while (options);
}

void velocidades (SDL_Renderer* renderizador) {
    bool vel = true;

    SDL_RenderClear(renderizador);

    SDL_Texture* normal = carregaImagemBMP("assets/menu/modoNormal.bmp", renderizador);
    SDL_Texture* rapido = carregaImagemBMP("assets/menu/modoRapido.bmp", renderizador);
    SDL_Texture* voltar = carregaImagemBMP("assets/menu/volta.bmp", renderizador);

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    do {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while(SDL_PollEvent(&evento)) {
            switch(evento.type) {
                 case SDL_QUIT:
                     SDL_Quit();
                     exit(0);
                 break;

                 case SDL_MOUSEBUTTONDOWN:
                    if(evento.button.y > 25 && evento.button.y < 80 && evento.button.x > 180 && evento.button.x < 580) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        vel = false;
                        VelocidadeDoJogo = 1;
                        SDL_Delay(delayMenu);
                    } else if (evento.button.y > 132  && evento.button.y < 202 && evento.button.x > 180 && evento.button.x < 565) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        VelocidadeDoJogo = 2;
                        vel = false;
                        SDL_Delay(delayMenu);
                    } else if (evento.button.y > 250 && evento.button.y < 295 && evento.button.x > 220 && evento.button.x < 440) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        vel = false;
                        SDL_Delay(delayMenu);
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
    SDL_CloseAudioDevice(paddleHitId);
    SDL_DestroyTexture(normal);
    SDL_DestroyTexture(voltar);
    SDL_DestroyTexture(rapido);
}
