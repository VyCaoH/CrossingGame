#pragma once
#ifndef _OBJECT
#define _OBJECT
#include "ConsoleWindow.h"
#include "Limits.h"
#include <math.h>
class Object
{
private:
	static Limits* LRight;
	static Limits* LLeft;
protected:
	COORD coord;

	SHORT bound[4];

public:
	Object();

	~Object();

	SHORT getX() const;

	SHORT getY() const;

	virtual void move(int x, int y);

	virtual SHORT getLimitofHeight() const;

	virtual SHORT getLimitofWidth() const;

	SHORT getBound(int index) const;

	virtual Limits getLimits(bool isRight = 0) const;

	void recalBound();
};

#endif //_Object
