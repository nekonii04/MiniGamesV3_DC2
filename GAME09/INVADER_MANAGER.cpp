#include "INVADER_MANAGER.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/sound.h"
#include "PLAYER.h"
#include <cstdlib> 
#include <algorithm>

void INVADER_MANAGER::load() {
    img = loadImage("../MAIN/assets/GAME09/INVADER.png");
    fastImg = loadImage("../MAIN/assets/GAME09/INVADER2.png");
    se_hit = loadSound("../MAIN/assets/GAME09/hit.wav");

    invaderSpead = 0.4f;

    createInvaders();
}


void INVADER_MANAGER::update(PLAYER& player,std::vector<BULLET>& bullets,
    float playerX, float playerY,
    bool& gameOver, bool& gameClear, int& score) {
    bool needReverse = false;
    int aliveCount = 0;

    for (auto& inv : invaders) {
        if (!inv.isAlive()) continue;

        aliveCount++;
        inv.update(invaderSpead);


        if (inv.getX() < 0 || inv.getX() > 1920 - 32)
            needReverse = true;

        if (inv.getY() >= playerY)
            gameOver = true;
    }
  
    if (needReverse) {
        for (auto& inv : invaders) {
            inv.moveDown();
            inv.reverseDir();
        }
    }

    // “G‚Ì’e
    if (aliveCount > 0) {
        float fireProb = (float)(ROW * COL) / aliveCount / 800.0f;
        if (fireProb > 0.03f) fireProb = 0.03f;

        for (auto& inv : invaders) {
            if (!inv.isAlive()) continue;
            if ((rand() / (float)RAND_MAX) < fireProb) {
                enemyBullets.emplace_back(inv.getX(), inv.getY());
            }
        }
    }

    for (auto& b : enemyBullets) b.update();
    enemyBullets.erase(
        std::remove_if(enemyBullets.begin(), enemyBullets.end(),
            [](ENEMY_BULLET& b) { return b.isOut(); }),
        enemyBullets.end());

    for (auto& b : enemyBullets)
    {
        if (fabs(b.getX() - playerX) < 24 &&
            fabs(b.getY() - playerY) < 24)
        {
            gameOver = true;
            return; 
        }
    }

    // “–‚½‚è”»’è 
    for (auto& b : bullets) {
        if (b.isDead()) continue;

        for (auto& inv : invaders) {
            if (inv.isAlive() && inv.checkHit(b.getX(), b.getY())) {
                inv.kill();
                b.setDead();
                score += 100;
                playSound(se_hit);

                int r = rand() % 10;
                if (r == 0) items.emplace_back(inv.getX(), inv.getY(), ITEM_RAPID);
                if (r == 1) items.emplace_back(inv.getX(), inv.getY(), ITEM_SPEED);
            }
        }
    }

    //  ƒAƒCƒeƒ€ 
    for (auto& it : items) {
        it.update();
        if (!it.isDead() &&
            fabs(it.getX() - playerX) < 32 &&
            fabs(it.getY() - playerY) < 32) {

            it.setDead();
            if (it.getType() == ITEM_RAPID) player.activateRapidFire(600);
            if (it.getType() == ITEM_SPEED) player.activateSpeedBoost(600);
        }
    }

    items.erase(
        std::remove_if(items.begin(), items.end(),
            [](ITEM& it) { return it.isDead(); }),
        items.end());
}

void INVADER_MANAGER::draw() {
    for (auto& inv : invaders) inv.draw();
    for (auto& b : enemyBullets) b.draw();
    for (auto& it : items) it.draw();
}

void INVADER_MANAGER::reset() {
    img = loadImage("../MAIN/assets/GAME09/INVADER.png");
    fastImg = loadImage("../MAIN/assets/GAME09/INVADER2.png");

    se_hit = loadSound("../MAIN/assets/GAME09/hit.wav");

    invaders.clear();
    enemyBullets.clear();
    items.clear();

    // “G‚ðÄ”z’u
    float totalwidth = COL * 60;
    float startX = (1920 - totalwidth) / 2;
    float startY = 100;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            float x = startX + j * 100;
            float y = startY + i * 90;
            INVADER inv;
            inv.set(x, y,img, 1.0f);
            invaders.push_back(inv);
        }
    }
}

void INVADER_MANAGER::createInvaders() {
    invaders.clear();

    float startX = (1920 - COL * 100) / 2;
    float startY = 120;

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            INVADER inv;
            inv.set(startX + j * 100, startY + i * 80, img, 1);
            invaders.push_back(inv);
        }
    }
    if (phase >= 2) {
        for (int j = 0; j < COL; ++j) {
            INVADER inv;
            inv.set(startX + j * 100, startY - 80, fastImg, -1);
            invaders.push_back(inv);
        }
    }
}


bool INVADER_MANAGER::isAllDead() {
    for (auto& inv : invaders) {
        if (inv.isAlive()) return false;
    }
    return true;
}

void INVADER_MANAGER::preparePhase(int newPhase) {
    phase = newPhase;
    enemyBullets.clear();
    items.clear();

    invaderSpead = 0.4f + 0.15f * (phase - 1);

    createInvaders();
}

void INVADER_MANAGER::startPhase() {

}