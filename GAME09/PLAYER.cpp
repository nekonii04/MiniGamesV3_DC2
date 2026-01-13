#include "../../libOne/inc/libOne.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/sound.h"
#include "PLAYER.h"

float PLAYER::getX() const { return x; }
float PLAYER::getY() const { return y; }

void PLAYER::load() {
    img = loadImage("../MAIN/assets/GAME09/player.png");
    se_shot = loadSound("../MAIN/assets/GAME09/shot.wav");
    x = 1920 / 2;
    y = 1080 - 100;

    // 初期状態は通常モード
    bullets.clear();
    rapidFire = false;
    rapidFireTimer = 0;
    shotCooldown = 0;
}

void PLAYER::update() {

    if (speedTimer > 0) speedTimer--;

    float spd = 4.0f;
    if (speedTimer > 0) spd *= 1.8f; // スピードアップ中は1.8倍

    if (isPress(KEY_A)) x -= spd;
    if (isPress(KEY_D)) x += spd;

    // 画面外制限
    if (x < 50) x = 50;
    if (x > 1870) x = 1870;

    // クールダウン更新
    if (shotCooldown > 0) shotCooldown--;

    if (rapidFire) {
        // 連射モード時：SPACEを押している間、一定間隔で発射
        if (isPress(KEY_SPACE) && shotCooldown == 0) {
            bullets.emplace_back(x + 16, y);
            playSound(se_shot);
            shotCooldown = 15;  
        }

        // タイマー減少
        if (--rapidFireTimer <= 0) {
            rapidFire = false;  
        }
    }
    else {
        if (isTrigger(KEY_SPACE) && bullets.size() < 1) {
            bullets.emplace_back(x + 16, y);
            playSound(se_shot);
        }
    }

    // 弾の更新
    for (auto& b : bullets) b.update();

    // 画面外の弾を削除
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](BULLET& b) { return b.isOut(); }), bullets.end());
}

void PLAYER::draw() {
    image(img, VECTOR(x, y), 0, 1.0f, CENTER);
    for (auto& b : bullets) b.draw();
}

void PLAYER::activateRapidFire(int duration) {
    rapidFire = true;
    rapidFireTimer = duration; 
    shotCooldown = 0;          
}
std::vector<BULLET>& PLAYER::getBullets() {
    return bullets;
}

void PLAYER::activateSpeedBoost(int duration) {
    speedTimer = duration;
}

