#include "menu.h"

int windowWidth = 1920;
int windowHeight = 1080;
int delayMenu = 150;

extern int VelocidadeDoJogo;

int carregaMenu(SDL_Renderer *renderizador)
{
    bool main = true;
    int retorno = 0;

    SDL_RenderClear(renderizador);

    SDL_Texture *inicio = carregaImagemBMP("assets/menu/inicioHD.bmp", renderizador);

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    do
    {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.y > (windowHeight / 1.2) && evento.button.y < (windowHeight / 1.11) && evento.button.x > (windowWidth / 2.49) && evento.button.x < (windowWidth / 1.77))
                {
                    //executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    retorno = 0;
                    SDL_Delay(delayMenu);
                    main = false;
                }
                else if (evento.button.y > (windowHeight / 1.09) && evento.button.y < (windowHeight / 1.01) && evento.button.x > (windowWidth / 2.31) && evento.button.x < (windowWidth / 1.85))
                {
                    SDL_Delay(delayMenu);
                    SDL_Quit();
                    exit(0);
                }
                break;
            }
        }

        SDL_Rect iniciarOri = {0, 0, 1280, 720};
        SDL_Rect iniciarDest = {0, 0, windowWidth, windowHeight};

        SDL_RenderCopy(renderizador, inicio, &iniciarOri, &iniciarDest);
        SDL_RenderPresent(renderizador);

    } while (main);

    SDL_RenderClear(renderizador);
    SDL_CloseAudioDevice(paddleHitId);
    SDL_DestroyTexture(inicio);
    return retorno;
}

int menu(SDL_Renderer *renderizador)
{
    int opcoes = true;
    int retorno = 0;

    SDL_RenderClear(renderizador);

    SDL_Texture *menu = carregaImagemBMP("assets/menu/menu.bmp", renderizador);

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    do
    {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.y > (windowHeight / 3.73) && evento.button.y < (windowHeight / 2.75) && evento.button.x > (windowWidth / 2.69) && evento.button.x < (windowWidth / 1.62))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    retorno = 1;
                    SDL_Delay(delayMenu);
                    opcoes = false;
                }
                else if (evento.button.y > (windowHeight / 2.66) && evento.button.y < (windowHeight / 2.16) && evento.button.x > (windowWidth / 2.34) && evento.button.x < (windowWidth / 1.77))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    optionsMenu(renderizador);
                    SDL_Delay(delayMenu);
                }
                else if (evento.button.y > (windowHeight / 2.11) && evento.button.y < (windowHeight / 1.76) && evento.button.x > (windowWidth / 2.63) && evento.button.x < (windowWidth / 1.64))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                }
                else if (evento.button.y > (windowHeight / 1.73) && evento.button.y < (windowHeight / 1.52) && evento.button.x > (windowWidth / 2.21) && evento.button.x < (windowWidth / 1.86))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                    SDL_Quit();
                    exit(0);
                }
                break;
            }
        }

        SDL_Rect menuOri = {0, 0, 1280, 720};
        SDL_Rect menuDest = {0, 0, windowWidth, windowHeight};
        SDL_RenderCopy(renderizador, menu, &menuOri, &menuDest);

        SDL_RenderPresent(renderizador);

    } while (opcoes);

    SDL_RenderClear(renderizador);
    SDL_DestroyTexture(menu);
    SDL_CloseAudioDevice(paddleHitId);

    return retorno;
}

int optionsMenu(SDL_Renderer *renderizador)
{
    bool options = true;
    bool muted = false;
    int retorno = 2;

    SDL_RenderClear(renderizador);

    SDL_Texture *som = carregaImagemBMP("assets/menu/opcoes.bmp", renderizador);
    SDL_Rect somOri = {0, 0, 1280, 720};
    SDL_Rect somDest = {0, 0, windowWidth, windowHeight};

    SDL_Texture *mute = carregaImagemBMP("assets/menu/opcoesS.bmp", renderizador);
    SDL_Rect muteOri = {0, 0, 1280, 720};
    SDL_Rect muteDest = {0, 0, windowWidth, windowHeight};

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    do
    {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.y > (windowHeight / 4.36) && evento.button.y < (windowHeight / 3.06) && evento.button.x > (windowWidth / 3.13) && evento.button.x < (windowWidth / 1.49))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                    velocidades(renderizador);
                }
                else if (evento.button.y > (windowHeight / 2.95) && evento.button.y < (windowHeight / 2.33) && evento.button.x > (windowWidth / 3.80) && evento.button.x < (windowWidth / 1.37))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                }
                else if (evento.button.y > (windowHeight / 2.29) && evento.button.y < (windowHeight / 1.95) && evento.button.x > (windowWidth / 2.22) && evento.button.x < (windowWidth / 1.87))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                    //tela(renderizador);
                }
                else if (evento.button.y > (windowHeight / 1.84) && evento.button.y < (windowHeight / 1.63) && evento.button.x > (windowWidth / 2.32) && evento.button.x < (windowWidth / 1.78))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                    options = false;
                }
                else if (evento.button.y > (windowHeight / 1.5) && evento.button.y < (windowHeight / 1.24) && evento.button.x > (windowWidth / 2.24) && evento.button.x < (windowWidth / 1.91))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);

                    if (muted)
                    {
                        Mix_VolumeMusic(100);
                        muted = false;
                    }
                    else
                    {
                        SDL_RenderCopy(renderizador, mute, &muteOri, &muteDest);
                        SDL_RenderPresent(renderizador);
                        Mix_VolumeMusic(0);
                        muted = true;
                    }
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

    return retorno;
}

void velocidades(SDL_Renderer *renderizador)
{
    bool vel = true;

    SDL_RenderClear(renderizador);

    SDL_Texture *velocidade = carregaImagemBMP("assets/menu/velocidades.bmp", renderizador);
    SDL_Texture *velocidade1 = carregaImagemBMP("assets/menu/velocidade.bmp", renderizador);

    SDL_Rect velocidadeOri = {0, 0, 1280, 720};
    SDL_Rect velocidadeDest = {0, 0, windowWidth, windowHeight};

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    do
    {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.y > (windowHeight / 4.44) && evento.button.y < (windowHeight / 3.34) && evento.button.x > (windowWidth / 2.87) && evento.button.x < (windowWidth / 1.61))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    VelocidadeDoJogo = 1;
                    SDL_RenderCopy(renderizador, velocidade1, &velocidadeOri, &velocidadeDest);
                    SDL_RenderPresent(renderizador);
                    SDL_Delay(delayMenu * 5);
                }
                else if (evento.button.y > (windowHeight / 3.06) && evento.button.y < (windowHeight / 2.4) && evento.button.x > (windowWidth / 2.80) && evento.button.x < (windowWidth / 1.65))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    VelocidadeDoJogo = 1.5;
                    SDL_RenderCopy(renderizador, velocidade1, &velocidadeOri, &velocidadeDest);
                    SDL_RenderPresent(renderizador);
                    SDL_Delay(delayMenu * 5);
                }
                else if (evento.button.y > (windowHeight / 2.33) && evento.button.y < (windowHeight / 1.97) && evento.button.x > (windowWidth / 2.69) && evento.button.x < (windowWidth / 1.68))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    VelocidadeDoJogo = 2;
                    SDL_RenderCopy(renderizador, velocidade1, &velocidadeOri, &velocidadeDest);
                    SDL_RenderPresent(renderizador);
                    SDL_Delay(delayMenu * 5);
                }
                else if (evento.button.y > (windowHeight / 1.6) && evento.button.y < (windowHeight / 1.39) && evento.button.x > (windowWidth / 2.39) && evento.button.x < (windowWidth / 1.81))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                    vel = false;
                }
                break;
            }
        }

        SDL_Rect normalOri = {0, 0, 1280, 720};
        SDL_Rect normalDest = {0, 0, windowWidth, windowHeight};
        SDL_RenderCopy(renderizador, velocidade, &normalOri, &normalDest);

        SDL_RenderPresent(renderizador);

    } while (vel);

    SDL_RenderClear(renderizador);
    SDL_CloseAudioDevice(paddleHitId);
    SDL_DestroyTexture(velocidade);
    SDL_DestroyTexture(velocidade1);
}

int modeGame(SDL_Renderer *renderizador)
{
    int mode = true;
    int retorno = 0;

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    SDL_Texture *modo = carregaImagemBMP("assets/menu/modo.bmp", renderizador);
    SDL_RenderClear(renderizador);
    do
    {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.y > (windowHeight / 3.82) && evento.button.y < (windowHeight / 2.80) && evento.button.x > (windowWidth / 2.65) && evento.button.x < (windowWidth / 1.62))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    retorno = 1;
                    SDL_Delay(delayMenu);
                    mode = false;
                }
                else if (evento.button.y > (windowHeight / 2.74) && evento.button.y < (windowHeight / 2.18) && evento.button.x > (windowWidth / 2.96) && evento.button.x < (windowWidth / 1.52))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    retorno = 2;
                    SDL_Delay(delayMenu);
                    mode = false;
                }
                else if (evento.button.y > (windowHeight / 2.13) && evento.button.y < (windowHeight / 1.77) && evento.button.x > (windowWidth / 3.32) && evento.button.x < (windowWidth / 1.45))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    retorno = 3;
                    SDL_Delay(delayMenu);
                    mode = false;
                }
                else if (evento.button.y > (windowHeight / 1.5) && evento.button.y < (windowHeight / 1.33) && evento.button.x > (windowWidth / 2.32) && evento.button.x < (windowWidth / 1.77))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                    mode = false;
                }
                break;
            }
        }

        SDL_Rect modeOri = {0, 0, 1280, 720};
        SDL_Rect modeDest = {0, 0, windowWidth, windowHeight};
        SDL_RenderCopy(renderizador, modo, &modeOri, &modeDest);

        SDL_RenderPresent(renderizador);

    } while (mode);

    return retorno;
}

int tela(SDL_Renderer *renderizador)
{
    bool options = true;
    int tela = 0;

    SDL_RenderClear(renderizador);

    SDL_Texture *som = carregaImagemBMP("assets/menu/tela.bmp", renderizador);
    SDL_Rect somOri = {0, 0, 1280, 720};
    SDL_Rect somDest = {0, 0, windowWidth, windowHeight};

    SDL_AudioSpec paddleHitSpec;
    Uint32 paddleHitLength;
    Uint8 *paddleHitBuffer;

    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleHitSpec, &paddleHitBuffer, &paddleHitLength);
    SDL_AudioDeviceID paddleHitId = SDL_OpenAudioDevice(NULL, 0, &paddleHitSpec, NULL, 0);

    do
    {
        SDL_RenderClear(renderizador);
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.y > (windowHeight / 4.47) && evento.button.y < (windowHeight / 3.30) && evento.button.x > (windowWidth / 2.45) && evento.button.x < (windowWidth / 1.67))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    tela = 0;
                    SDL_Delay(delayMenu);
                }
                else if (evento.button.y > (windowHeight / 3) && evento.button.y < (windowHeight / 2.36) && evento.button.x > (windowWidth / 2.61) && evento.button.x < (windowWidth / 1.61))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    tela = 1;
                    SDL_Delay(delayMenu);
                }
                else if (evento.button.y > (windowHeight / 1.87) && evento.button.y < (windowHeight / 1.63) && evento.button.x > (windowWidth / 2.32) && evento.button.x < (windowWidth / 1.78))
                {
                    executaSom(paddleHitId, paddleHitLength, paddleHitBuffer);
                    SDL_Delay(delayMenu);
                    options = false;
                }
                break;
            }
        }

        SDL_RenderCopy(renderizador, som, &somOri, &somDest);
        SDL_RenderPresent(renderizador);
    } while (options);

    SDL_DestroyTexture(som);
    SDL_CloseAudioDevice(paddleHitId);

    return tela;
}
