#include "game.h"

extern int VelocidadeDoJogo;
extern int windowHeight;
extern int windowWidth;

void getPlayerMovement(SDL_Event* evento, player* player1) {
                switch (evento->type) {
                case SDL_KEYDOWN:
                    switch( evento->key.keysym.sym ){
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

void getBotMovement (ball* ball, player* bot) {
    if(ball->destino.y > (windowHeight - (windowHeight/4))){
        if(bot->destino.x > (windowWidth/2)){
            bot->esquerda = true;
            bot->direita = false;
        }

        if(bot->destino.x < (windowWidth/2)){
            bot->direita = true;
            bot->esquerda = false;
        }

        if(bot->destino.x == (windowWidth/2)){
            bot->direita = false;
            bot->esquerda = false;
        }
    }else {
        if((bot->destino.x + (bot->destino.w/2)) < ball->destino.x){
                bot->direita = true;
                bot->esquerda = false;

                if(ball->esquerda && ball->destino.y < (windowHeight/6)){
                    bot->direita = false;
                    bot->esquerda = false;
                }
        }

        if( (bot->destino.x + (bot->destino.w/2)) > ball->destino.x ){
                bot->esquerda = true;
                bot->direita = false;

                if(ball->direita && ball->destino.y < (windowHeight/6)){
                    bot->direita = false;
                    bot->esquerda = false;
                }
        }

       /* if(ball->destino.y < (windowHeight/2)
                && ball->destino.y > (windowHeight/3.5)){
            if(ball->destino.x > (windowWidth - 80)){
                bot->esquerda = true;
                bot->direita = false;
            }

            if(ball->destino.x < 80){
                bot->direita = true;
                bot->esquerda = false;
            }
        }*/
    }
}

void startSinglePlayerGame (SDL_Renderer* renderizador) {
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

            getPlayerMovement(&evento,&player1);
        }

         getBotMovement(&ball, &player2);

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
