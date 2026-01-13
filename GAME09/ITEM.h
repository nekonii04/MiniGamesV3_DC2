#pragma once
#include "../../libOne/inc/VECTOR.h"

enum ITEM_TYPE {
	ITEM_RAPID,
	ITEM_SPEED
};
class ITEM {
	float x, y;
	bool dead;
	ITEM_TYPE type;
    
public:
	ITEM(float x, float y, int img);
	void update();
	void draw();
	bool isDead() const;
	float getX() const;
	float getY() const;
	void setDead();
	ITEM(float x, float y, ITEM_TYPE type);
	ITEM_TYPE getType() const { return type; }
 };
