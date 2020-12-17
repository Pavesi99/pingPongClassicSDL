#include "menu.h"

int windowWidth  = 1280;
int windowHeight = 720;
int delayMenu = 150;

extern int VelocidadeDoJogo;

int carregaMenu (SDL_Renderer* renderizador) {
    bool main = true;
    int retorno = 0;

    SDL_RenderClear(renderizador);

    SDL_Texture* inicio = carregaImagemBMP("assets/menu/inicioHD.bmp", renderizador);

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
                    if(evento.button.y > 600 && evento.button.y < 647 && evento.button.x > 513 && evento.button.x < 730) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        retorno = 0;
                        SDL_Delay(delayMenu);
                        main = false;
                    } else if (evento.button.y > 660 && evento.button.y < 712 && evento.button.x > 554 && evento.button.x < 690) {
                        SDL_Delay(delayMenu);
                        SDL_Quit();
                        exit(0);
                    }
                break;
            }
        }

        SDL_Rect iniciarOri = {0, 0, windowWidth, windowHeight};
        SDL_Rect iniciarDest = {0, 0, windowWidth, windowHeight};

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
                       if (evento.button.y > 193  && evento.button.y < 261 && evento.button.x > 475 && evento.button.x < 788) {
                           executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                           retorno = 1;
                           SDL_Delay(delayMenu);
                           opcoes = false;
                       } else if (evento.button.y > 270 && evento.button.y < 333 && evento.button.x > 545 && evento.button.x < 720) {
                           executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                           optionsMenu(renderizador);
                           SDL_Delay(delayMenu);
                       } else if (evento.button.y > 341 && evento.button.y < 407 && evento.button.x > 485 && evento.button.x < 780) {
                           executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                           SDL_Delay(delayMenu);
                       } else if (evento.button.y > 415 && evento.button.y < 473 && evento.button.x > 577 && evento.button.x < 688) {
                           executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                           SDL_Delay(delayMenu);
                           SDL_Quit();
                           exit(0);
                       }
                    break;
               }
           }

           SDL_Rect menuOri = {0, 0, windowWidth, windowHeight};
           SDL_Rect menuDest = {0, 0, windowWidth, windowHeight};
           SDL_RenderCopy(renderizador, menu, &menuOri, &menuDest);

           SDL_RenderPresent(renderizador);

       } while (opcoes);

       SDL_RenderClear(renderizador);
       SDL_DestroyTexture(menu);
       SDL_CloseAudioDevice(paddleHitId);

       return retorno;
}

void optionsMenu (SDL_Renderer* renderizador) {
    bool options = true;

    SDL_RenderClear(renderizador);

    SDL_Texture* som = carregaImagemBMP("assets/menu/opcoes.bmp", renderizador);
    SDL_Rect somOri = {0, 0, windowWidth, windowHeight};
    SDL_Rect somDest = {0, 0, windowWidth, windowHeight};

    SDL_Texture* mute = carregaImagemBMP("assets/menu/opcoesS.bmp", renderizador);
    SDL_Rect muteOri = {0, 0, windowWidth, windowHeight};
    SDL_Rect muteDest = {0, 0, windowWidth, windowHeight};

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
                    if(evento.button.y > 165 && evento.button.y < 235 && evento.button.x > 408 && evento.button.x < 854) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                        velocidades(renderizador);
                    } else if (evento.button.y > 244  && evento.button.y < 308 && evento.button.x > 336 && evento.button.x < 930) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                    } else if (evento.button.y > 314 && evento.button.y < 369 && evento.button.x > 575 && evento.button.x < 683) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                    } else if (evento.button.y > 390 && evento.button.y < 440 && evento.button.x > 550 && evento.button.x < 718) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                        options = false;
                    } else if (evento.button.y > 480 && evento.button.y < 580 && evento.button.x > 570 && evento.button.x < 670) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_RenderCopy(renderizador, mute, &muteOri, &muteDest);
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(delayMenu);
                    }
                 break;
            }
        }

        SDL_RenderCopy(renderizador, som, &somOri, &somDest);
        SDL_RenderPresent(renderizador);
    } while (options);

    SDL_DestroyTexture(mute);
    SDL_DestroyTexture(som);
    SDL_CloseAudioDevice(paddleHitId);

}

void velocidades (SDL_Renderer* renderizador) {
    bool vel = true;

    SDL_RenderClear(renderizador);

    SDL_Texture* velocidade = carregaImagemBMP("assets/menu/velocidades.bmp", renderizador);
    SDL_Texture* velocidade1 = carregaImagemBMP("assets/menu/velocidade.bmp", renderizador);

    SDL_Rect velocidadeOri = {0, 0, windowWidth, windowHeight};
    SDL_Rect velocidadeDest = {0, 0, windowWidth, windowHeight};

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
                    if(evento.button.y > 162 && evento.button.y < 215 && evento.button.x > 445 && evento.button.x < 793) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        VelocidadeDoJogo = 1;
                        SDL_RenderCopy(renderizador, velocidade1, &velocidadeOri, &velocidadeDest);
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(delayMenu * 4);
                    } else if (evento.button.y > 235  && evento.button.y < 300 && evento.button.x > 457 && evento.button.x < 775) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        VelocidadeDoJogo = 2;
                        SDL_RenderCopy(renderizador, velocidade1, &velocidadeOri, &velocidadeDest);
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(delayMenu * 4);
                    } else if (evento.button.y > 308 && evento.button.y < 365 && evento.button.x > 475 && evento.button.x < 760) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        VelocidadeDoJogo = 3;
                        SDL_RenderCopy(renderizador, velocidade1, &velocidadeOri, &velocidadeDest);
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(delayMenu * 4);
                    } else if (evento.button.y > 450 && evento.button.y < 515 && evento.button.x > 534 && evento.button.x < 707) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                        vel = false;
                    }
                 break;
            }
        }

        SDL_Rect normalOri = {0, 0, windowWidth, windowHeight};
        SDL_Rect normalDest = {0, 0, windowWidth, windowHeight};
        SDL_RenderCopy(renderizador, velocidade, &normalOri, &normalDest);

        SDL_RenderPresent(renderizador);

    } while (vel);

    SDL_RenderClear(renderizador);
    SDL_CloseAudioDevice(paddleHitId);
    SDL_DestroyTexture(velocidade);
    SDL_DestroyTexture(velocidade1);
}

int modeGame (SDL_Renderer* renderizador) {
    int mode = true;
    int retorno = 0;

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

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
                    if (evento.button.y > 188  && evento.button.y < 257 && evento.button.x > 482 && evento.button.x < 787) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        retorno = 1;
                        SDL_Delay(delayMenu);
                        mode = false;
                    } else if (evento.button.y > 262 && evento.button.y < 330 && evento.button.x > 432 && evento.button.x < 840) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        retorno = 2;
                        SDL_Delay(delayMenu);
                        mode = false;
                    } else if (evento.button.y > 337 && evento.button.y < 405 && evento.button.x > 385 && evento.button.x < 880) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        retorno = 3;
                        SDL_Delay(delayMenu);
                        mode = false;
                    } else if (evento.button.y > 480 && evento.button.y < 540 && evento.button.x > 550 && evento.button.x < 720) {
                        executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                        SDL_Delay(delayMenu);
                        mode = false;
                    }
                 break;
            }
        }

        SDL_Rect modeOri = {0, 0, windowWidth, windowHeight};
        SDL_Rect modeDest = {0, 0, windowWidth, windowHeight};
        SDL_RenderCopy(renderizador, modo, &modeOri, &modeDest);

        SDL_RenderPresent(renderizador);

    } while (mode);

    return retorno;
}
