#include "game.h"

extern int windowWidth;
extern int windowHeight;
extern int points;

void getPlayersMovement(SDL_Event* evento, player* player1, player* player2) {
                switch (evento->type) {
                case SDL_KEYDOWN:
                    switch( evento->key.keysym.sym ){
                        case SDLK_LEFT:
                            player2->esquerda = true;
                            break;
                        case SDLK_RIGHT:
                            player2->direita = true;
                            break;
                        case SDLK_a:
                            player1->esquerda = true;
                            break;
                        case SDLK_d:
                            player1->direita = true;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch( evento->key.keysym.sym ){
                        case SDLK_LEFT:
                            player2->esquerda = false;
                            break;
                        case SDLK_RIGHT:
                            player2->direita = false;
                            break;
                        case SDLK_a:
                            player1->esquerda = false;
                            break;
                        case SDLK_d:
                            player1->direita = false;
                            break;
                    }
                    break;
                }
}

void startTwoPlayersGame (SDL_Renderer* renderizador) {
    bool gameOver = false;
    int waitTimeAfterPoint = 0;

    player player1;
    player player2;
    ball ball;

    /*
    TTF_Font* fonte = TTF_OpenFont("vgafix.ttf", 54);
    SDL_Color cor = {255, 255, 255, 255};
    SDL_Surface* fonteTexuture = TTF_RenderText_Solid(fonte, "Pontuação:", cor);
    SDL_Texture* pontuacao1 = SDL_CreateTextureFromSurface(renderizador, fonteTexuture);

    SDL_FreeSurface(fonteTexuture);

    SDL_Rect rectTexto;
    rectTexto.x = rectTexto.y = 0;

    SDL_QueryTexture(pontuacao1, NULL, NULL, &rectTexto.w, &rectTexto.h);
    */
    SDL_Texture* imgPlayer1 = carregaImagemBMP("assets/elementosJogo/Stick.bmp", renderizador);
    SDL_Texture* imgPlayer2 = carregaImagemBMP("assets/elementosJogo/Stick01.bmp", renderizador);
    SDL_Texture* imgBall = carregaImagemBMP("assets/elementosJogo/Ball.bmp", renderizador);
    player1.texture = imgPlayer1;
    player2.texture = imgPlayer2;
    ball.texture = imgBall;

    SDL_AudioSpec wallSpec;
    Uint32 wallLength;
    Uint8 *wallBuffer;
    SDL_LoadWAV("assets/som/WallHit.wav", &wallSpec, &wallBuffer, &wallLength);
    SDL_AudioDeviceID wallId = SDL_OpenAudioDevice(NULL, 0, &wallSpec, NULL, 0);

    SDL_AudioSpec paddleSpec;
    Uint32 paddleLength;
    Uint8 *paddleBuffer;
    SDL_LoadWAV("assets/som/PaddleHit.wav", &paddleSpec, &paddleBuffer, &paddleLength);
    SDL_AudioDeviceID paddleId = SDL_OpenAudioDevice(NULL, 0, &paddleSpec, NULL, 0);

    SDL_AudioSpec errorSpec;
    Uint32 errorLength;
    Uint8 *errorBuffer;
    SDL_LoadWAV("assets/som/point.wav", &errorSpec, &errorBuffer, &errorLength);
    SDL_AudioDeviceID errorId = SDL_OpenAudioDevice(NULL, 0, &errorSpec, NULL, 0);

    setInitialBallPosition(&ball,windowWidth, windowHeight);
    setInitialPlayersPositions(&player1,&player2, windowWidth, windowHeight);

     SDL_RenderCopy(renderizador, player1.texture, &player1.origem, &player1.destino);
     SDL_RenderCopy(renderizador, player2.texture, &player2.origem, &player2.destino);
     SDL_RenderCopy(renderizador, ball.texture, &ball.origem, &ball.destino);

    while (player1.pontos <= points && player2.pontos <= points && !gameOver) {
        SDL_RenderClear(renderizador);

        SDL_Event evento;
        while(SDL_PollEvent(&evento) > 0){
            switch (evento.type) {
                case SDL_QUIT: 
                SDL_Quit();
                exit(0);
                break;
            case SDL_KEYDOWN:
                switch( evento.key.keysym.sym ){
                    case SDLK_ESCAPE:
                        gameOver = true;
                    break;
                }
                break;
            }

            getPlayersMovement(&evento,&player1,&player2);
        }

        movePlayer(&player1, windowWidth);
        movePlayer(&player2, windowWidth);

        if(checkBallCollision(&ball,&player1,&player2)){
            executaSom(wallId, wallLength, wallBuffer);
        }

        SDL_RenderCopy(renderizador, player2.texture, &player2.origem,&player2.destino );
        SDL_RenderCopy(renderizador, player1.texture, &player1.origem,&player1.destino );
        SDL_RenderCopy(renderizador, ball.texture, &ball.origem, &ball.destino);
        //SDL_RenderCopy(renderizador, pontuacao1, NULL, &rectTexto);

        SDL_RenderPresent(renderizador);
        SDL_Delay(1000 / 60);

        switch(moveBall(&ball,windowWidth,windowHeight, &waitTimeAfterPoint )){
            case 1:
                player1.pontos++;
                setBallDirectionAfterPoint(&ball);
                setInitialBallPosition(&ball,windowWidth, windowHeight);
                setInitialPlayersPositions(&player1,&player2, windowWidth, windowHeight);
                executaSom(errorId, errorLength, errorBuffer);
                waitTimeAfterPoint = 180;
            break;
            case 2:
                player2.pontos++;
                setBallDirectionAfterPoint(&ball);
                setInitialBallPosition(&ball,windowWidth, windowHeight);
                setInitialPlayersPositions(&player1,&player2, windowWidth, windowHeight);
                executaSom(errorId, errorLength, errorBuffer);
                waitTimeAfterPoint = 180;
            break;
            case 3:
                waitTimeAfterPoint--;
            break;
            case 4:
                executaSom(paddleId, paddleLength, paddleBuffer);
            break;
        }
    }

    int cont = 0;
    SDL_Texture* vencer = carregaImagemBMP("assets/menu/venceu.bmp", renderizador);
    SDL_Rect vencerOri = {0, 0, 1280, 720};
    SDL_Rect vencerDest = {0, 0, windowWidth, windowHeight};

    if (!gameOver) {
        while (cont < 5000) {
            SDL_RenderCopy(renderizador, vencer, &vencerOri, &vencerDest);
            SDL_RenderPresent(renderizador);
            cont++;
        }
    }

    SDL_CloseAudioDevice(errorId);
    SDL_CloseAudioDevice(paddleId);
    SDL_CloseAudioDevice(wallId);
    SDL_ClearQueuedAudio(wallId);
    SDL_ClearQueuedAudio(paddleId);
    SDL_ClearQueuedAudio(errorId);
    SDL_RenderClear(renderizador);
    SDL_DestroyTexture(imgPlayer1);
    SDL_DestroyTexture(imgPlayer2);
    SDL_DestroyTexture(imgBall);
    //SDL_DestroyTexture(pontuacao1);
    //TTF_CloseFont(fonte);
}
