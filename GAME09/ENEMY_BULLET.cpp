#include "ENEMY_BULLET.h"
#include "../../libOne/inc/graphic.h"

ENEMY_BULLET::ENEMY_BULLET(float x,float y):x(x),y(y),dead(false){}

void ENEMY_BULLET::update() {
	y += 3;
	if (y > 1080)dead = true;
}

void ENEMY_BULLET::draw() {
	fill(0, 255, 0);
	rect(x, y, 4, 10);
}

bool ENEMY_BULLET::isOut() const { return dead; }
float ENEMY_BULLET::getX() const { return x; }
float ENEMY_BULLET::getY() const { return y; }
void ENEMY_BULLET::setDead() { dead = true; }
bool ENEMY_BULLET::isDead() const { return dead; }