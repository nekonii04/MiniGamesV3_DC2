#pragma once
#include "BULLET.h"
#include <vector>

class PLAYER {
	float x, y;
	int img;
	std::vector<BULLET> bullets;
	int se_shot;
public:
	void load();
	void update();
	void draw();
	std::vector<BULLET>& getBullets();
	float getX() const;
	float getY() const;
};  

