#include "INVADER_MANAGER.h"
#include"INVADER.h"
#include "../../libOne/inc/graphic.h"
#include "cstdlib"
#include "../../libOne/inc/sound.h"


std::vector<ENEMY_BULLET>& INVADER_MANAGER::getEnemyBullets() {
    return enemyBullets;
}
void INVADER_MANAGER::load() {
    img = loadImage("../MAIN/assets/GAME09/INVADER.png");
    se_hit = loadSound("../MAIN/assets/GAME09/hit.wav"); 
    dx = 1;
    float totalwidth = COL * 60;
    float startX = (1920 - totalwidth) / 2;
    float startY = 100;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            float x = startX + j * 100;
            float y = startY + i * 90;
            invaders[i][j].set(x, y, img);
        }
    }
}

void INVADER_MANAGER::update(std::vector<BULLET>& bullets,float playerX, float playerY, bool& gameOver,bool& gameClear, int& score) {
    bool needReverse = false;
   
    // “G‚ÌˆÚ“®
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            invaders[i][j].update(dx);
            float x = invaders[i][j].getX();
            float y = invaders[i][j].getY();
            if (invaders[i][j].isAlive()) {
                if (x < 0 || x>1920 - 32) {

                    needReverse = true;
                }
                if (y >= playerY) {
                    gameOver = true;
                }
            }
        }
    }

    if (needReverse) {
        dx = -dx;
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                invaders[i][j].moveDown();
            }
        }
    }

    //“G‚Ì’e
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (invaders[i][j].isAlive() && rand() % 600 == 0) {
                float bx = invaders[i][j].getX();
                float by = invaders[i][j].getY();
                enemyBullets.emplace_back(bx, by);
            }
        }
    }
    //’e‚ÌXV
    for (auto& b : enemyBullets) b.update();
    //’e‚Ìíœ
    enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(),
        [](ENEMY_BULLET& b) { return b.isOut(); }), enemyBullets.end());
    // ’e‚Æ‚Ì“–‚½‚è”»’è
    for (auto& b : bullets) {
        if (b.isDead()) continue;
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                if (invaders[i][j].checkHit(b.getX(), b.getY())) {
                    invaders[i][j].kill();
                    b.setDead();
                    score += 100;
                    playSound(se_hit);
                }
            }
        }
    }
    // ƒvƒŒƒCƒ„[‚ÌÀ•WŽæ“¾
    float px = playerX;
    float py = playerY;
    float playerHalfSize = 32.0f; 

    //“G‚Ì’e‚ª“–‚½‚Á‚½‚çƒQ[ƒ€ƒI[ƒo[
    for (auto& b : enemyBullets) {
        if (b.isDead()) continue;

        float bx = b.getX();
        float by = b.getY();

        if (bx >= px - playerHalfSize && bx <= px + playerHalfSize &&
            by >= py - playerHalfSize && by <= py + playerHalfSize) {
            b.setDead();
            gameOver = true;
        }
    }
    //“G‘S–Å
    bool allDead = true;
    for (int i = 0; i < ROW && allDead; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (invaders[i][j].isAlive()) {
                allDead = false;
                break;
            }
        }
    }
    if (allDead) {
        gameClear = true;
    }
}

void INVADER_MANAGER::draw() {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            invaders[i][j].draw();
        }
    }
    for (auto& b : enemyBullets)b.draw();
}
