#ifndef _ROW
#define _ROW

#include "Animal.h"
#include "Vehicle.h"

#include <Windows.h>
#include <vector> 
#include <ctime>
#include <random>

class Row
{
private:
	int y_coord; // Coordinate Y
	int type; // Type of enemy
	int MAX_ENEMIES; // Max number of enemies on a row
	clock_t t; // Time
	int speed;  //Speed
	int _speed; //Speed buffer
	int _lvl;
	int distance; // Distance between 2 entities
	int redLightTime; // Red light time
	bool isFromRight; // true if Row from right
	bool isRedLight; // true if Row has red light
	std::vector <Entity*> inhabitance; // list of entities on row

public:
	std::random_device gen;
	Row(int y); // DEFAULT

	~Row();

	int GetY() const;

	int GetT() const;

	int GetTime() const;

	bool GetRight() const;

	bool GetRedLight() const;

	int getType() const;

	bool getIsFromRight() const;

	std::vector <Entity*> GetList() const;

	void SetY(int y);

	void SetT(clock_t T);

	void SetTime(float time);

	void SetRight(bool right);

	void SetRedLight(bool tick);

	void toggle();

	void AtLevel(int lvl); // Set new red light time by new level

	void append();

	void move();
};
#endif // _ROW