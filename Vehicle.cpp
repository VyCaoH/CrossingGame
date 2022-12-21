#include "Vehicle.h"

Car::Car()
{
	is_right = true;
	car_pX = 0;
	car_pY = 0;
	entity.clear();
}

Car::Car(float posX, float posY)
{
	car_pX = posX;
	car_pY = posY;
}

void Car::left(float speed, float dt, int lv)
{
	car_pX -= speed * dt * lv;
}

void Car::right(float speed, float dt, int lv) {
	car_pX += speed * dt * lv;
}

float Car::getX() const
{
	return car_pX;
}

float Car::getY() const
{
	return car_pY;
}

float Car::getHalfX() const
{
	return car_half_X;
}

float Car::getHalfY() const
{
	return car_half_Y;
}
bool Car::Right()
{
	return is_right;
}
void Car::setHalf(float x, float y) 
{
	car_half_X = x;
	car_half_Y = y;
}

Truck::Truck()
{
	is_right = true;
	truck_pX = 0;
	truck_pY = 0;
	entity.clear();
}

Truck::Truck(float posX, float posY)
{
	truck_pX = posX;
	truck_pY = posY;
}

void Truck::left(float speed, float dt, int lv)
{
	truck_pX -= speed * dt * lv;
}
void Truck::right(float speed, float dt, int lv)  {
	truck_pX += speed * dt * lv;
}
float Truck::getX() const
{
	return truck_pX;
}
float Truck::getY() const
{
	return truck_pY;
}
float Truck::getHalfX() const
{
	return truck_half_X;
}
float Truck::getHalfY()const
{
	return truck_half_Y;
}
bool Truck::Right()
{
	return is_right;
}
void Truck::setHalf(float x, float y)
{
	truck_half_X = x;
	truck_half_Y = y;
}
