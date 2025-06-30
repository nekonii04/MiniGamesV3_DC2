#include "../../libOne/inc/libOne.h"
#include "../../libOne/inc/graphic.h"
#include "INVADER.h"


void INVADER::set(float x, float y, int image) {
    this->x = x;
    this->y = y;
    this->img = image;
    this->alive = true;
}

void INVADER::update(float dx) {
    if (alive) x += dx;
}

void INVADER::draw() {
    if (alive) {
        
        image(img, x, y, 1.0f);
    }
}

bool INVADER::checkHit(float bx, float by) {
    float halfSize = 16.0f; 
    return alive &&
        bx >= x - halfSize && bx <= x + halfSize &&
        by >= y - halfSize && by <= y + halfSize;
}

bool INVADER::isAlive() const { return alive; }
void INVADER::kill() { alive = false; }
float INVADER::getX() const { return x; }
float INVADER::getY() const { return y; }
void INVADER::moveDown() { y += 60; }
