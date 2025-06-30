#pragma once
class ENEMY_BULLET
{
	float x, y;
	bool dead;
public:
	ENEMY_BULLET(float x, float y);
	void update();
	void draw();
	bool isOut() const;
	float getX() const;
	float getY() const;
	void setDead();
	bool isDead() const;
};

