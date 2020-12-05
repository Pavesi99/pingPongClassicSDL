#include "game.h"

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

void setInitialPlayersPositions(player* player1, player* player2){
    player2->origem.h = 200;
    player2->origem.w = 800;
    player2->origem.x = 0;
    player2->origem.y = 0;

    player2->destino.h = 40;
    player2->destino.w = player2->origem.w / 8;
    player2->destino.x = 300;
    player2->destino.y = 0;

    player1->origem.h = 200;
    player1->origem.w = 800;
    player1->origem.x = 0;
    player1->origem.y = 0;

    player1->destino.h = 40;
    player1->destino.w = player1->origem.w / 8;
    player1->destino.x = 300;
    player1->destino.y = 570;
}

bool checkBallCollision(ball* ball, player* player1, player* player2){
    if(ball->destino.x >= player2->destino.x
            && ball->destino.x <= (player2->destino.x + player2->destino.w)
            && ball->destino.y <= (player2->destino.y + (player2->destino.h /2))
            ){
        ball->cima = false;
        ball->baixo = true;

        if(ball->destino.x <= (player2->destino.x + 5)){
            ball->esquerda = true;
            ball->direita = false;
        }else if(ball->destino.x >= (player2->destino.x + player2->destino.w - 5) ){
            ball->esquerda = false;
            ball->direita = true;
        }else {
            if( ball->esquerda == false && ball->direita == false){
                ball->esquerda = true;
            }
        }
        return true;
    }
    if(ball->destino.x >= player1->destino.x
            && ball->destino.x <= (player1->destino.x + player1->destino.w)
            && ball->destino.y >= (player1->destino.y - (player1->destino.h / 2))
            ){
        ball->cima = true;
        ball->baixo = false;
        if(ball->destino.x <= (player1->destino.x + 5)){
            ball->esquerda = true;
            ball->direita = false;
        }else if(ball->destino.x >= (player1->destino.x + player1->destino.w  - 5)){
            ball->esquerda = false;
            ball->direita = true;
        }else {
            if( ball->esquerda == false && ball->direita == false){
                ball->esquerda = true;
            }
        }
        return true;
    }
    return false;
}

void startTwoPlayersGame (SDL_Renderer* renderizador) {
    int windowWidth  = 800;
    int windowHeight = 600;
    bool gameOver = false;
    int waitTimeAfterPoint = 0;

    player player1;
    player player2;
    ball ball;

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
    setInitialPlayersPositions(&player1,&player2);

     SDL_RenderCopy(renderizador, player1.texture, &player1.origem, &player1.destino);
     SDL_RenderCopy(renderizador, player2.texture, &player2.origem, &player2.destino);
     SDL_RenderCopy(renderizador, ball.texture, &ball.origem, &ball.destino);

    while (player1.pontos <= 5 && player2.pontos <= 5 && !gameOver) {
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

        SDL_RenderPresent(renderizador);
        SDL_Delay(1000 / 60);

        switch(moveBall(&ball,windowWidth,windowHeight, &waitTimeAfterPoint )){
            case 1:
                player1.pontos++;
                setBallDirectionAfterPoint(&ball);
                setInitialBallPosition(&ball,windowWidth, windowHeight);
                setInitialPlayersPositions(&player1,&player2);
                executaSom(errorId, errorLength, errorBuffer);
                waitTimeAfterPoint = 180;
            break;
            case 2:
                player2.pontos++;
                setBallDirectionAfterPoint(&ball);
                setInitialBallPosition(&ball,windowWidth, windowHeight);
                setInitialPlayersPositions(&player1,&player2);
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
}
