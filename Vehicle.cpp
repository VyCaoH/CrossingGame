#include "Vehicle.h"

Limits* Car::carLmtRight = new Limits("Limits\\Car-Right.txt");
Limits* Car::carLmtLeft = new Limits("Limits\\Car-Left.txt");

Limits* Truck::truckLmtRight = new Limits("Limits\\Truck-Right.txt");
Limits* Truck::truckLmtLeft = new Limits("Limits\\Truck-Left.txt");

Car::Car(int x, int y)
{
	move(x, y);
	recalBound();
}

Car::~Car()
{
	delete carLmtRight;
	delete carLmtLeft;
}


Truck::Truck(int x, int y)
{
	move(x, y);
	recalBound();
}

Truck::~Truck()
{
	delete truckLmtRight;
	delete truckLmtLeft;
}