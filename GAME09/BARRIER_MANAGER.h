
#pragma once
#include "BARRIER.h"
#include <vector>
#include "ENEMY_BULLET.h"

class BARRIER_MANAGER {
private:
    std::vector<BARRIER> barriers;
public:
    void create();
    void update(std::vector<ENEMY_BULLET>& enemyBullets);
    void draw();
};
