#include "Entity.h"
//
//void Entity::setHeight(int height)
//{
//	this->height = height;
//}
//void Entity::setWidth(int width)
//{
//	this->width = width;
//}
 void Entity::setX(float src)
{
	entity_pX = src;
}
 void Entity:: setY(float src)
{
	entity_pY = src;
}
 void Entity::setHalf(float x, float y)
 {
	 entity_half_x = x;
	 entity_half_y = y;
 }
float Entity::getX() const
{
	return entity_pX;
}
float Entity::getY() const
{
	return entity_pY;
}
float Entity:: getHalfX() const
{
	return entity_half_x;
}
float Entity::getHalfY() const
{
	return entity_half_y;
}
void Entity::left(float speed, float dt, int lv)
{
	entity_pX -= speed  * lv;
}

void Entity::right(float speed, float dt, int lv) {
	entity_pX += speed * lv;
}

//vector<vector<char>> Entity::getEntity() const
//{
//	return entity;
//}
//int Entity::getHeight() const
//{
//	return height;
//}
//int Entity::getWidth() const
//{
//	return width;
//}
////void Entity::setXY(SHORT posX, SHORT posY)
////{
////	coord.X = posX;
////	coord.Y = posY;
////}
