#pragma once
#include "../MAIN/GAME_BASE.h"
#include "PLAYER.h"
#include "INVADER_MANAGER.h"
#include "BARRIER_MANAGER.h"
namespace GAME09
{
    class GAME :
        public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
        bool gameOver = false;
        bool gameClear = false;

        int score = 0;
        int highScore = 0;
        int backImg;
        PLAYER player;
        INVADER_MANAGER invaderManager;
        BARRIER_MANAGER barrierManager;

    };
}
