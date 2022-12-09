#pragma once
#include"Animal.h"
#include"Vehicle.h"
#include"ConsoleWindow.h"
#include<ctime>
#include<cmath>
#include<random>

class Threat
{
	int y_coord;
	//int pos_row;	//position of the row
	int numEnemyInRow;	//Number of Enemy in one row
	unsigned int lv;	//level
	float speed;
	int distance;	//distance of every Enemies in one row
	clock_t time;
	//vector<Entity*> threaten;	//Number of threaten 
	vector<Entity*>threat;
	int redLightTime;	//Redlight's time occur
	bool trafficLight;	//true=red, false=green
	int dir;
	TYPE type;
public:
	//std::random_device gen;
	Threat(int posY);
	enum DIRECTION { RIGHT, LEFT };
	//enum TYPE { CAR_RIGHT, CAR_LEFT, BUS_RIGHT, BUS_LEFT, CAR2_LEFT, CAR2_RIGHT, BIRD, DINOSAUR};
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
//	void lvIncrease()
//	{
//		lv++;
//	}
//	void setSpeed()
//	{
//		speed = floor(speed * ((double)lv * 0.5));
//	}
//	int getSpeed()
//	{
//		return speed;
//	}
//	int getDistance()
//	{
//		return distance;
//	}
//	clock_t getTime()
//	{
//		return time;
//	}
//	void setRandomDistance()
//	{
//		distance = rand() % (100 - 20 + 1) - 20;
//	}
//	void setnumEnemyInRow()
//	{
//		int temp = round(lv / 2);
//		numEnemyInRow += temp;
//	}
//	void setTime(float time)
//	{
//		redLightTime = time;
//	}
//	void setTraffic(bool color)
//	{
//		if (color == Red)
//		{
//			trafficLight = Red;
//		}
//	}
//	void setListThread();
//};
//
