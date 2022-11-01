#include "Entity.h"

Sprite* Entity::sprtRight = new Sprite("Sprites\\Default.txt");
Sprite* Entity::sprtLeft = new Sprite("Sprites\\Default.txt");

Entity::Entity()
{
	coord.X = 0;
	coord.Y = 0;
	sprtRight = nullptr;
	bound[0] = 0;
	bound[1] = 0;
	bound[2] = 0;
	bound[3] = 0;
}

Entity::~Entity()
{
	delete sprtRight;
}

SHORT Entity::getX() const
{
	return coord.X;
}

SHORT Entity::getY() const
{
	return coord.Y;
}

void Entity::move(int x, int y)
{
	coord.X = x;
	coord.Y = y;
}

SHORT Entity::getSpriteHeight() const
{
	return sprtRight->getHeight();
}

SHORT Entity::getSpriteWidth() const
{
	return sprtRight->getWidth();
}

SHORT Entity::getBound(int index) const
{
	return bound[index];
}

Sprite Entity::getSprite(bool isRight) const
{
	return (isRight) ? *sprtRight : *sprtLeft;
}

void Entity::recalBound()
{
	//Clockwise order
	bound[0] = (getSpriteHeight() - 1) / 2;
	bound[1] = floor((getSpriteWidth() - 1) / 2);
	bound[2] = getSpriteHeight() / 2;
	bound[3] = ceil((getSpriteWidth()) / 2);
}