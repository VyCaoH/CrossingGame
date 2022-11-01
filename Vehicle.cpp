#include "Vehicle.h"

Sprite* Car::carSprtRight = new Sprite("Sprites\\Car-Right.txt");
Sprite* Car::carSprtLeft = new Sprite("Sprites\\Car-Left.txt");

Sprite* Truck::truckSprtRight = new Sprite("Sprites\\Truck-Right.txt");
Sprite* Truck::truckSprtLeft = new Sprite("Sprites\\Truck-Left.txt");

Car::Car(int x, int y)
{
	move(x, y);
	recalBound();
}

Car::~Car()
{
	delete carSprtRight;
	delete carSprtLeft;
}


Truck::Truck(int x, int y)
{
	move(x, y);
	recalBound();
}

Truck::~Truck()
{
	delete truckSprtRight;
	delete truckSprtLeft;
}