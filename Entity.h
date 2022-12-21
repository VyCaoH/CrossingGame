#pragma once
class Entity
{
private:
	int height, width;
	float entity_half_x, entity_half_y;
	float entity_pX, entity_pY;
protected:

public:
	virtual float getX() const;
	virtual float getY() const;
	virtual void setX(float src);
	virtual void setY(float src);
	virtual void setHalf(float x, float y);
	virtual float getHalfX() const;
	virtual float getHalfY() const;
	virtual void left(float speed, float dt, int lv);
	virtual void right(float speed, float dt, int lv);
};
