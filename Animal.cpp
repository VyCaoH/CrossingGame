#include "Animal.h"

Limits* Bird::birdLmtRight = new Limits("Limits\\Bird-Right.txt");
Limits* Bird::birdLmtLeft = new Limits("Limits\\Bird-Left.txt");

Limits* Dinosaur::dinoLmtRight = new Limits("Limits\\Dino-Right.txt");
Limits* Dinosaur::dinoLmtLeft = new Limits("Limits\\Dino-Left.txt");

Bird::Bird(int x, int y)
{
	move(x, y);
	recalBound();
}

Bird::~Bird()
{
	delete birdLmtRight;
	delete birdLmtLeft;
}


Dinosaur::Dinosaur(int x, int y)
{
	move(x, y);
	recalBound();
}

Dinosaur::~Dinosaur()
{
	delete dinoLmtRight;
	delete dinoLmtLeft;
}