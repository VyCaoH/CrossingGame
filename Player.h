#pragma once
#include "Vehicle.h"
#include "Animal.h"
#include "Object.h"
#include "Row.h"

#include <vector>
#include <deque> 

class Player : public Object
{
private:
	bool isDead;

	static Limits* playerLmt;

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

	Limits getLimits(bool isRight = 0) const override
	{
		return *playerLmt;
	}

	SHORT getLimitofHeight() const override
	{
		return playerLmt->getHeight();
	}

	SHORT getLimitofWidth() const override
	{
		return playerLmt->getWidth();
	}
};



