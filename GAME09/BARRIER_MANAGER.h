
#pragma once
#include "BARRIER.h"
#include <vector>
#include "ENEMY_BULLET.h"
#include "BULLET.h"
#include "INVADER.h"

class BARRIER_MANAGER {
private:
    std::vector<BARRIER> barriers;
public:
    void create();
    void update(std::vector<ENEMY_BULLET>& enemyBullets, std::vector<BULLET>& playerBullets, std::vector<INVADER>& invaders);
    void draw();
};
