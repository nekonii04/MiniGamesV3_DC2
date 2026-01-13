#include "ITEM.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/libOne.h"

bool ITEM::isDead() const { return dead; }
float ITEM::getX() const { return x; }
float ITEM::getY() const { return y; }
void ITEM::setDead() { dead = true; }

ITEM::ITEM(float x, float y, ITEM_TYPE type)
	: x(x), y(y), dead(false), type(type) {}


void ITEM::update() {
	y += 2;
	if (y > 1000)dead = true;
}
void ITEM::draw() {
	if (dead) return;

	noStroke();
	if (type == ITEM_RAPID) fill(255, 0, 0);
	else if (type == ITEM_SPEED) fill(0, 128, 255);
	circle(x, y, 20);
}

