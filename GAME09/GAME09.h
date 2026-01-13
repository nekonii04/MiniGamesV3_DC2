#pragma once
#include "../MAIN/GAME_BASE.h"
#include "PLAYER.h"
#include "INVADER_MANAGER.h"
#include "BARRIER_MANAGER.h"

namespace GAME09
{
    class GAME : public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
        void resetGame();
        void updateHighScore();

        bool gameOver = false;
        bool gameClear = false;
        bool saved = false; 
        bool phaseChanging = false;

        int score = 0;
        int highScore = 0;
        int backImg;
        int phaseStartTimer = 0;
        int currentPhase = 1;

        PLAYER player;
        INVADER_MANAGER invaderManager;
        BARRIER_MANAGER barrierManager;

        
        enum GAME_STATE {
            STATE_TITLE,
            STATE_PLAY,
            STATE_GAMEOVER,
            STATE_CLEAR,
            STATE_PHASE_START
        };
        GAME_STATE state = STATE_TITLE;  

    };
}
