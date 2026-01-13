#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME09.h"
#include"PLAYER.h"
#include <string>
#include <fstream>
namespace GAME09
{
    void drawBackground(int img)
    {
        float sx = (float)width / 1920.0f;
        float sy = (float)height / 1080.0f;
        float scale = (sx > sy) ? sx : sy;

        image(img, VECTOR(0, 0), 0.0f, scale);
    }

    enum GAME_STATE {
        STATE_TITLE,
        STATE_PLAY,
        STATE_GAMEOVER,
        STATE_CLEAR,
        STATE_PHASE_START
    };

    int GAME::create()
    {
        rectMode(CENTER);
        hideCursor();
        

        backImg = loadImage("../MAIN/assets/GAME09/backImg.png");

        // ハイスコア読み込み
        std::ifstream in("../MAIN/assets/GAME09/highscore.txt");
        if (in.is_open()) {
            in >> highScore;
            in.close();
        }
        else {
            highScore = 0;
        }

        state = STATE_TITLE;  //タイトル画面
        return 0;
    }

    void GAME::destroy()
    {
    }

    void GAME::resetGame() {
        player.load();              
        invaderManager.reset();     
        barrierManager.create();    
        score = 0;
        gameOver = false;
        gameClear = false;
        saved = false;
        currentPhase = 1;
        phaseChanging = false;
        phaseStartTimer = 0;
        
    }

    void GAME::updateHighScore() {
        if (score > highScore) {
            highScore = score;

            std::ofstream out("../MAIN/assets/GAME09/highscore.txt");
            if (out.is_open()) {
                out << highScore;   
                out.close();
            }
        }
    }
    void GAME::proc()
    {

        switch (state) {
        case STATE_TITLE:
            clear(0, 0, 64);
            drawBackground(backImg);
            fill(255);
            textSize(150);
            text("SPACE INVADERS", 450, 300);

            textSize(60);
            text("Press ENTER to Start", 500, 600);

            textSize(40);
            text("操作説明:", 200, 750);
            text("← → : 移動", 200, 800);
            text("SPACE : ショット", 200, 850);
            text("赤い弾 ：連射アイテム", 200, 900);
            text("青い弾 ：加速アイテム", 200, 950);


            if (isTrigger(KEY_ENTER)) {
                resetGame();
                // ゲーム開始
                state = STATE_PLAY;
            }
            break;

        case STATE_PLAY:
            clear(0, 0, 64);
            drawBackground(backImg);

            if (!gameOver && !gameClear) {
                player.update();
                invaderManager.update(player, player.getBullets(),
                    player.getX(), player.getY(),
                    gameOver, gameClear, score);
                barrierManager.update(invaderManager.getEnemyBullets(),
                    player.getBullets(),
                    invaderManager.getInvaders());

                // 敵が全滅したら次フェーズへ
                if (!phaseChanging && invaderManager.isAllDead()) {
                    if (currentPhase == 3) {
                        gameClear = true;
                        updateHighScore();
                        state = STATE_CLEAR;
                        return;
                    }

                    
                    updateHighScore();
                    currentPhase++;
                    phaseChanging = true;
                    invaderManager.preparePhase(currentPhase);
                    state = STATE_PHASE_START;
                    phaseStartTimer = 180;
                    return;
                }
                player.draw();
                invaderManager.draw();
                barrierManager.draw();


                // スコア表示
                fill(255);
                textSize(40);
                text(("SCORE: " + std::to_string(score)).c_str(), 1600, 50);
                text(("HIGHSCORE: " + std::to_string(highScore)).c_str(), 1600, 100);

                // 終了チェック
                if (gameOver) {
                    updateHighScore();
                    state = STATE_GAMEOVER;
                }
                else if (gameClear) {
                    updateHighScore();
                    state = STATE_CLEAR;
                }
                break;

        case STATE_GAMEOVER:
            clear(0, 0, 64);
            drawBackground(backImg);

            fill(255, 0, 0);
            textSize(200);
            text("GAME OVER", 480, 540);

            textSize(60);
            fill(255);
            text("Press ENTER to Title", 500, 800);

            if (isTrigger(KEY_ENTER)) {
                resetGame();
                state = STATE_TITLE;
            }
            break;

        case STATE_CLEAR:
            clear(0, 0, 64);
            drawBackground(backImg);

            fill(0, 255, 0);
            textSize(200);
            text("GAME CLEAR!", 540, 540);

            textSize(60);
            fill(255);
            text("Press ENTER to Title", 500, 800);


            if (isTrigger(KEY_ENTER)) {
                state = STATE_TITLE;
            }
            break;

        case STATE_PHASE_START:
            clear(0, 0, 64);
            drawBackground(backImg);

            player.draw();
            invaderManager.draw();
            barrierManager.draw();


            fill(255, 255, 0);
            textSize(150);
            std::string phaseMsg = "PHASE " + std::to_string(currentPhase) + " START!!";
            float x = width / 2 - 300;
            float y = height / 2;
            text(phaseMsg.c_str(), x, y);


            if (phaseStartTimer > 0) {
                phaseStartTimer--;
            }
            else {
                phaseChanging = false;
                state = STATE_PLAY;
            }
            break;
            }
        }
    }
}