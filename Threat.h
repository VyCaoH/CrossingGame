#pragma once
#include"Animal.h"
#include"Vehicle.h"
#include"ConsoleWindow.h"
#include<ctime>
#include<cmath>
#include<random>
#include "TrafficLight.h"
class Threat
{
	int y_coord;
	int numEnemyInRow;	//Number of Enemy in one row
	unsigned int lv;	//level
	float speed;
	int distance;	//distance of every Enemies in one row

	vector<Entity*>threat;
	TrafficLight trafficlight;
	int dir;
	TYPE type;
public:
	Threat(int posY);
	enum DIRECTION { RIGHT, LEFT };
	int getNumEnemyInRow();
	unsigned int getLv();
	int getType();
	float getSpeed();
	int getDistance();
	int getThreat(int type);
	vector<Entity*> getThreat();
	void setListEntity(TYPE type, int dir);
	void setThreatInRow(int lv);
	int random_int(int min, int max);
	bool checkWall_left(float x);
	bool checkWall_right(float x);
	void move(float speed, float dt);
};