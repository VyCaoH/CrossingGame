#include "Animal.h"

Sprite* Bird::birdSprtRight = new Sprite("Sprites\\Bird-Right.txt");
Sprite* Bird::birdSprtLeft = new Sprite("Sprites\\Bird-Left.txt");

Sprite* Dinosaur::dinoSprtRight = new Sprite("Sprites\\Dino-Right.txt");
Sprite* Dinosaur::dinoSprtLeft = new Sprite("Sprites\\Dino-Left.txt");

Bird::Bird(int x, int y)
{
	move(x, y);
	recalBound();
}

Bird::~Bird()
{
	delete birdSprtRight;
	delete birdSprtLeft;
}


Dinosaur::Dinosaur(int x, int y)
{
	move(x, y);
	recalBound();
}

Dinosaur::~Dinosaur()
{
	delete dinoSprtRight;
	delete dinoSprtLeft;
}