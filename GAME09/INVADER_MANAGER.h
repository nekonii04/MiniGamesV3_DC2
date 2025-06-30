#pragma once
#include "INVADER.h"
#include "BULLET.h"
#include"ENEMY_BULLET.h"
#include <vector>

class INVADER_MANAGER {
    static const int ROW = 5;
    static const int COL = 7;
    INVADER invaders[ROW][COL];
    float dx;
    int img;
    int se_hit;
    std::vector<ENEMY_BULLET> enemyBullets;
    
public:
    void load();
    void update(std::vector<BULLET>& bullets, float playerX, float playerY, bool& gameOver, bool& gameClear, int& score);
    void draw();
    std::vector<ENEMY_BULLET>& getEnemyBullets();
};

