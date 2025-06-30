#include "../../libOne/inc/libOne.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/sound.h"
#include "PLAYER.h"

float PLAYER::getX() const { return x; }

float PLAYER::getY() const
{
    return y;
}

void PLAYER::load() {
    img = loadImage("../MAIN/assets/GAME09/player.png");
    se_shot = loadSound("../MAIN/assets/GAME09/shot.wav");
    x = 1920 / 2;
    y = 1080 - 100;

}

void PLAYER::update() {
    if (isPress(KEY_A)) x -= 5;
    if (isPress(KEY_D)) x += 5;
    if (isTrigger(KEY_SPACE) && bullets.size() < 1) {
        bullets.emplace_back(x + 16, y);
        playSound(se_shot);
    }
    
    for (auto& b : bullets) b.update();

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](BULLET& b) { return b.isOut(); }), bullets.end());
}

void PLAYER::draw() {
    image(img, VECTOR(x, y),0,1.0f,CENTER);
    for (auto& b : bullets) b.draw();
}

std::vector<BULLET>& PLAYER::getBullets() {
    return bullets;
}
