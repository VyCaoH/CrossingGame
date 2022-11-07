#ifndef _ANIMAL
#define _ANIMAL
//#include "Object.h"
#include "Limits.h"
#include "Object.h"

class Animal : public Object
{
public:
	/*virtual void move(int x, int y)
	{
		coord.X = x;
		coord.Y = y;
	}*/
};

class Bird : public Animal
{
private:
	static Limits* birdLmtRight;
	static Limits* birdLmtLeft;
public:
	Bird(int x, int y);

	~Bird();

	Limits getLimits(bool isRight = 0) const override
	{
		return (isRight) ? *birdLmtRight : *birdLmtLeft;
	}

	SHORT getLimitofHeight()const override
	{
		return birdLmtRight->getHeight();
	}

	SHORT getLimitofWidth() const override
	{
		return birdLmtRight->getWidth();
	}
};

class Dinosaur : public Animal
{
private:
	static Limits* dinoLmtRight;
	static Limits* dinoLmtLeft;
public:
	Dinosaur(int x, int y);

	~Dinosaur();

	Limits getLimits(bool isRight = 0) const override
	{
		return (isRight) ? *dinoLmtRight : *dinoLmtLeft;
	}
	SHORT getLimitofHeight()const override
	{
		return dinoLmtRight->getHeight();
	}

	SHORT getLimitofWidth() const override
	{
		return dinoLmtRight->getWidth();
	}
};
#endif // _ANIMAL