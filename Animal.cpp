#include "Animal.h"
Bird::Bird()
{
	is_right = true;
	bird_pX = 0;
	bird_pY = 0;
	entity.clear();
}
Bird::Bird(float posX, float posY)
{
	bird_pX = posX;
	bird_pY = posY;
}
void Bird::left(float speed, float dt, int lv) 
{
	bird_pX -= speed * dt * lv;
}
void Bird::right(float speed, float dt, int lv)  {
	bird_pX += speed * dt * lv;
}
float Bird::getX() const 
{
	return bird_pX;
}
float Bird::getY() const 
{
	return bird_pY;
}
float Bird::getHalfX() const 
{
	return bird_half_X;
}
float Bird::getHalfY()const 
{
	return bird_half_Y;
}
bool Bird::Right()
{
	return is_right;
}
void Bird::setHalf(float x, float y) 
{
	bird_half_X = x;
	bird_half_Y = y;
}

Dinosaur::Dinosaur()
{
	is_right = true;
	dinosaur_pX = 0;
	dinosaur_pY = 0;
	entity.clear();
}
Dinosaur::Dinosaur(float posX, float posY)
{
	dinosaur_pX = posX;
	dinosaur_pY = posY;
}
void Dinosaur::left(float speed, float dt, int lv) 
{
	dinosaur_pX -= speed * dt * lv;
}
void Dinosaur::right(float speed, float dt, int lv)  {
	dinosaur_pX += speed * dt * lv;
}
float Dinosaur::getHalfX() const 
{
	return dinosaur_half_X;
}
float Dinosaur::getHalfY()const 
{
	return dinosaur_half_Y;
}
float Dinosaur::getX() const 
{
	return dinosaur_pX;
}
float Dinosaur::getY() const 
{
	return dinosaur_pY;
}
void Dinosaur::setX(float src) 
{
	dinosaur_pX = src;
}
void Dinosaur::setY(float src) 
{
	dinosaur_pY = src;
}
bool Dinosaur::Right()
{
	return is_right;
}
void Dinosaur::setHalf(float x, float y) 
{
	dinosaur_half_X = x;
	dinosaur_half_Y = y;
}