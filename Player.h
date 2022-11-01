#pragma once
#include "Vehicle.h"
#include "Animal.h"
#include "Entity.h"
#include "Row.h"

#include <vector>
#include <deque> 

class Player : public Entity
{
private:
	bool isDead;

	static Sprite* playerSprt;

public:
	// Maybe change this the default location
	Player();

	~Player();

	void move(int x, int y);

	void setState(bool state);

	int getX() const;

	int getY() const;

	void Up();

	void Left();

	void Down();
	
	void Right();

	int isImpact(std::vector<Row*>& listRow) const;

	bool isAtFinishLine() const;

	bool isPlayerDead() const;

	Sprite getSprite(bool isRight = 0) const override
	{
		return *playerSprt;
	}

	SHORT getSpriteHeight() const override
	{
		return playerSprt->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return playerSprt->getWidth();
	}
};



