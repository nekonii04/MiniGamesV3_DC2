#pragma once

class INVADER {
	float x, y;
	bool alive;
	int img;
public:
	void set(float x, float y, int image);
	void update(float dx);
	void draw();
	bool checkHit(float bx, float by);
	bool isAlive() const;
	void kill();
	float getX() const;
	float getY() const;
	void moveDown();
};