#pragma once
#include"Animal.h"
#include"Vehicle.h"
#include<ctime>
#include<cmath>
#include<random>

class Threat
{
	int y_coord;
	int type;
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
public:
	std::random_device gen;
	Threat(int posY):y_coord(posY)
	{
		std::uniform_int_distribution <int> randType(0, 3);
		//type = randType(gen);
		//pos_row = posY;
		time = 0;
		numEnemyInRow = 4;
		lv = 1;
		speed = 10;
		distance = 30;
		redLightTime = 0;
		trafficLight = false;
		threat.resize(0);
		type = -1;
	}
	enum TYPE { CAR, TRUCK, BIRD, DINOSAUR };
	int getNumEnemyInRow()
	{
		return numEnemyInRow;
	}
	unsigned int getLv()
	{
		return lv;
	}
	int getType()
	{
		return type;
	}
	float getSpeed()
	{
		return speed;
	}
	int getDistance()
	{
		return distance;
	}
	/*int getThreat(int type)
	{
		return type;
	}*/
	vector<Entity*> getThreatBird()
	{
		return threat;
	}
	//vector<Entity*> getListEntity()
	//{
	//	return threaten;
	//}
	//Entity* getEntity(int index)
	//{
	//	return threaten[index];
	//}
	void setListEntity(int type)
	{
		int randDistance = random_int(0, distance);
		int randExDistance = random_int(0, 20);

		/*uniform_int_distribution <int> randDistance(0, distance);
		uniform_int_distribution <int> randExDistance(0, 20);*/
		int randomDistance = random_int(20, 30);
		if(this->type==-1)
			this->type = type;
		switch (this->type)
		{
			//int y = randomRow;
		case TYPE::CAR:
		{
			while (threat.size() < numEnemyInRow)
			{
				if (threat.empty())
				{
					//threaten.push_back(new Car(randDistance(gen) - 30, pos_row));
					threat.push_back((new Car((float)randDistance - 30, (float)y_coord)));
				}
				else if (threat.size() < numEnemyInRow)
				{
					/*int prevCoordX = threaten.back()->getX();
					Car* temp = new Car(randExDistance(gen) + prevCoordX + 30, pos_row);
					threaten.push_back(temp->getBird());
					delete temp;*/
					float prevCoordX = threat.back()->getX();
					float distance_temp = randExDistance + prevCoordX + 30;
					if (distance_temp < 200)
					{
						threat.push_back(new Car((float)distance_temp, (float)y_coord));
					}
				}
			}break;

		}
		case TYPE::TRUCK:
		{
			while (threat.size() < numEnemyInRow)
			{
				if (threat.empty())
				{
					//threaten.push_back(new Truck(randDistance(gen) - 30, pos_row));
					threat.push_back((new Truck((float)randDistance - 30, (float)y_coord)));
				}
				else if (threat.size() < numEnemyInRow)
				{
					/*int prevCoordX = threaten.back()->getX();
					Truck* temp = new Truck(randExDistance(gen) + prevCoordX + 30, pos_row);
					threaten.push_back(temp->getBird());
					delete temp;*/
					float prevCoordX = threat.back()->getX();
					float distance_temp = randExDistance + prevCoordX + 30;
					if (distance_temp < 200)
					{
						threat.push_back(new Truck((float)distance_temp, (float)y_coord));
					}
				}
			}break;
		}
		case TYPE::BIRD:
		{
			while (threat.size() < numEnemyInRow)
			{
				if (threat.empty())
				{
					//threaten.push_back(new Bird(randDistance(gen) - 30, pos_row));
					threat.push_back((new Bird((float)randDistance - 30, (float)y_coord)));
				}
				else if (threat.size() < numEnemyInRow)
				{
					/*int prevCoordX = threaten.back()->getX();
					Bird* temp = new Bird(randExDistance(gen) + prevCoordX + 30, pos_row);
					threaten.push_back(temp->getBird());
					delete temp;*/
					float prevCoordX = threat.back()->getX();
					float distance_temp = randExDistance + prevCoordX + 30;
					if (distance_temp < 200)
					{
						threat.push_back(new Bird((float)distance_temp, (float)y_coord));
					}
				}
			}/*
			Bird* temp = new Bird(randomDistance, pos_row);
			threaten* tempEntity = temp->getBird();
			tempEntity->setXY(randomDistance, pos_row);
			if (tEntity.empty())
			{
				tEntity.push_back(tempEntity);
			}
			else if (tEntity.size() < 4)
			{
				int prevCoordX = tEntity.front()->getX();
				tempEntity->setXY(randomDistance + prevCoordX, pos_row);
				tEntity.push_back(tempEntity);
			}*/
			break;
		}
		case TYPE::DINOSAUR:
		{
			while (threat.size() < numEnemyInRow)
			{
				if (threat.empty())
				{
					//threaten.push_back(new Dinosuar(randDistance(gen) - 30, pos_row));
					threat.push_back((new Dinosaur((float)randDistance - 30, (float)y_coord)));
				}
				else if (threat.size() < numEnemyInRow)
				{
					/*int prevCoordX = threaten.back()->getX();
					Dinosuar* temp = new Dinosuar(randExDistance(gen) + prevCoordX + 30, pos_row);
					threaten.push_back(temp->getBird());
					delete temp;*/
					float prevCoordX = threat.back()->getX();
					float distance_temp = randExDistance + prevCoordX + 30;
					if (distance_temp < 200)
					{
						threat.push_back(new Dinosaur((float)distance_temp, (float)y_coord));
					}
				}
			}
			break;
		}

		}
	}
	int random_int(int min, int max)
	{
		return min + rand() % (max + 1 - min);
	}
	void move(float speed, float dt)
	{
		switch (type)
		{
		case BIRD:
		{
			for (auto x : threat)
			{
				x->left(speed, dt,lv);
				if (checkWall(x->getX()))
				{
					draw_rect(x->getX(), x->getY(), 1, 1, 0x00fffff);
				}
				else
					threat.erase(threat.begin());
			}break;
		}
		case DINOSAUR:
		{
			for (auto x : threat)
			{
				x->left(speed, dt,lv);
				if (checkWall(x->getX()))
				{
					draw_rect(x->getX(), x->getY(), 1, 1, 0xaabb00000);
				}
				else
					threat.erase(threat.begin());
			}break;
		}
		case CAR:
		{
			for (auto x : threat)
			{
				x->left(speed, dt, lv);
				if (checkWall(x->getX()))
				{
					draw_rect(x->getX(), x->getY(), 1, 1, 0x0000000);
					draw_rect(x->getX()-3, x->getY()-3, 2, 2, 0x0000000);
				}
				else
					threat.erase(threat.begin());
			}break;
		}
		case TRUCK:
		{
			for (auto x : threat)
			{
				x->left(speed, dt,lv);
				if (checkWall(x->getX()))
				{
					//draw_rect(x->getX(), x->getY(), 1, 1, 0xccccccccccc);
					draw_truck(x->getX(), x->getY(), x->getHalfX(), x->getHalfY());
				}
				else
					threat.erase(threat.begin());
			}break;
		}
		}
	}
};

//	enum Type { Car, Truck, Bird, Dinosaur };
//	enum Traffic { Red, Green };
//	tEntity(int);
//	~tEntity();
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
