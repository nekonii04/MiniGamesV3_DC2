#pragma once
#include "BULLET.h"
#include <vector>

class PLAYER {
    float x, y;
    int img;
    std::vector<BULLET> bullets;
    int se_shot;

    bool rapidFire = false;
    int rapidFireTimer = 0;
    int shotCooldown = 0;

public:
    void load();
    void update();
    void draw();
    std::vector<BULLET>& getBullets();
    float getX() const;
    float getY() const;

    void activateRapidFire(int duration);

    float moveSpeed = 10.0f;
    int speedTimer = 0;
    void activateSpeedBoost(int duration);
};