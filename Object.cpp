#include "Object.h"

Limits* Object::LRight = new Limits("Limits\\Default.txt");
Limits* Object::LLeft = new Limits("Limits\\Default.txt");

Object::Object()
{
	coord.X = 0;
	coord.Y = 0;
	LRight = nullptr;
	bound[0] = 0;
	bound[1] = 0;
	bound[2] = 0;
	bound[3] = 0;
}

Object::~Object() {
	delete LRight;
}

SHORT Object::getX() const {
	return coord.X;
}

SHORT Object::getY() const {
	return coord.Y;
}

void Object::move(int x, int y) {
	coord.X = x;
	coord.Y = y;
}

SHORT Object::getLimitofHeight() const {
	return LRight->getHeight();
}

SHORT Object::getLimitofWidth() const {
	return LLeft->getWidth();
}

SHORT Object::getBound(int index) const {
	return bound[index];
}

Limits Object::getLimits(bool isRight) const {
	return (isRight) ? *LRight : *LLeft;
}

void Object::recalBound() {
	//Theo chieu kim dong ho
	bound[0] = (getLimitofHeight() - 1) / 2;
	bound[1] = floor((getLimitofWidth() - 1) / 2);
	bound[2] = getLimitofHeight() / 2;
	bound[3] = ceil((getLimitofWidth()) / 2);

}