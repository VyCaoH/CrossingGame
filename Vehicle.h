#ifndef _VEHICLE
#define _VEHICLE

#include "Object.h"

class Vehicle : public Object
{
public:
	/*virtual void move(int x, int y)
	{
		coord.X = x;
		coord.Y = y;;
	}*/
};

class Car : public Vehicle
{
private:
	static Limits* carLmtRight;
	static Limits* carLmtLeft;
public:
	Car(int x, int y);

	~Car();

	Limits getLimits(bool isRight = 0) const override
	{
		return (isRight) ? *carLmtRight : *carLmtLeft;
	}
	SHORT getLimitofHeight() const override
	{
		return carLmtRight->getHeight();
	}

	SHORT getLimitofWidth() const override
	{
		return carLmtRight->getWidth();
	}
};

class Truck : public Vehicle
{
private:
	static Limits* truckLmtRight;
	static Limits* truckLmtLeft;

public:
	Truck(int x, int y);

	~Truck();

	Limits getLimits(bool isRight = 0) const override
	{
		return (isRight) ? *truckLmtRight : *truckLmtLeft;
	}
	SHORT  getLimitofHeight() const override
	{
		return truckLmtRight->getHeight();
	}

	SHORT  getLimitofWidth()  const override
	{
		return truckLmtRight->getWidth();
	}
};

#endif // _VEHICLE