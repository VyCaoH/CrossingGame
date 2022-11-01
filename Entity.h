#ifndef _ENTITY
#define _ENTITY
#include "Win32Helper.h"
#include "Sprite.h"
#include <math.h>

class Entity
{
private:
	static Sprite* sprtRight;
	static Sprite* sprtLeft;

protected:
	COORD coord;

	//Clockwise
	SHORT bound[4];
public:
	Entity();
	
	~Entity();

	SHORT getX() const;

	SHORT getY() const;

	virtual void move(int x, int y);
	
	virtual SHORT getSpriteHeight() const;

	virtual SHORT getSpriteWidth() const;
	
	SHORT getBound(int index) const;

	virtual Sprite getSprite(bool isRight = 0) const;

	void recalBound();
};

#endif //_ENTITY