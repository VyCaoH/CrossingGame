#ifndef _ANIMAL
#define _ANIMAL
#include "Entity.h"
#include "Sprite.h"

class Animal : public Entity
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
	static Sprite* birdSprtRight;
	static Sprite* birdSprtLeft;
public:
	Bird(int x, int y);

	~Bird();

	Sprite getSprite(bool isRight = 0) const override
	{
		return (isRight) ? *birdSprtRight : *birdSprtLeft;
	}

	SHORT getSpriteHeight() const override
	{
		return birdSprtRight->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return birdSprtRight->getWidth();
	}
};

class Dinosaur : public Animal
{
private:
	static Sprite* dinoSprtRight;
	static Sprite* dinoSprtLeft;
public:
	Dinosaur(int x, int y);

	~Dinosaur();

	Sprite getSprite(bool isRight = 0) const override
	{
		return (isRight) ? *dinoSprtRight : *dinoSprtLeft;
	}
	SHORT getSpriteHeight() const override
	{
		return dinoSprtRight->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return dinoSprtRight->getWidth();
	}
};
#endif // _ANIMAL