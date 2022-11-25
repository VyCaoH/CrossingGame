#pragma once
#include"Animal.h"
#include"Vehicle.h"
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
	std::random_device gen;
	Threat(int posY):y_coord(posY)
	{
		//std::uniform_int_distribution <int> randType(0, 3);
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
		type = TYPE(-1);
		dir = -1;
	}
	enum DIRECTION {RIGHT,LEFT};
	//enum TYPE { CAR_RIGHT, CAR_LEFT, BUS_RIGHT, BUS_LEFT, CAR2_LEFT, CAR2_RIGHT, BIRD, DINOSAUR};
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
	int getThreat(int type)
	{
		
	}
	vector<Entity*> getThreat()
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
	void setListEntity(TYPE type, int dir)
	{
		int randDistance_left = random_int(0, distance),
			randDistance_right=random_int(-distance,0);
		int randExDistance = random_int(0, 20);
		int randomDistance = random_int(20, 30);

		if (this->dir == -1)
			this->dir = dir;
		if(this->type==-1)
			this->type = type;

		switch (this->dir)
		{
		case LEFT:
		{
			switch (this->type)
			{
			case TYPE::CAR_LEFT || CAR2_LEFT:
			{
				while (threat.size() < numEnemyInRow)
				{
					if (threat.empty())
					{
						//threaten.push_back(new Car(randDistance(gen) - 30, pos_row));
						threat.push_back((new Car((float)randDistance_left - 30, (float)y_coord)));
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
			case TYPE::BUS_LEFT:
			{
				while (threat.size() < numEnemyInRow)
				{
					if (threat.empty())
					{
						//threaten.push_back(new Truck(randDistance(gen) - 30, pos_row));
						threat.push_back((new Truck((float)randDistance_left - 30, (float)y_coord)));
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
						threat.push_back((new Bird((float)randDistance_left - 30, (float)y_coord)));
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
				}
				break;
			}
			case TYPE::DINOSAUR:
			{
				while (threat.size() < numEnemyInRow)
				{
					if (threat.empty())
					{
						//threaten.push_back(new Dinosuar(randDistance(gen) - 30, pos_row));
						threat.push_back((new Dinosaur((float)randDistance_left - 30, (float)y_coord)));
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

			break;
		}
		
		case RIGHT:
		{
			switch (this->type)
			{
			case TYPE::CAR_RIGHT || CAR2_RIGHT:
			{
				while (threat.size() < numEnemyInRow)
				{
					if (threat.empty())
					{

						//threaten.push_back(new Car(randDistance(gen) - 30, pos_row));
						threat.push_back(new Car((float)randDistance_right + 30, (float)y_coord));
					}
					else if (threat.size() < numEnemyInRow)
					{
						/*int prevCoordX = threaten.back()->getX();
						Car* temp = new Car(randExDistance(gen) + prevCoordX + 30, pos_row);
						threaten.push_back(temp->getBird());
						delete temp;*/
						float prevCoordX = threat.back()->getX();
						float distance_temp = -randExDistance + prevCoordX - 30;
						if (distance_temp > -200)
						{
							//threat.insert(threat.begin(), (new Car((float)randDistance_right + 30, (float)y_coord)));

							threat.push_back(new Car((float)distance_temp, (float)y_coord));
						}
					}
				}break;

			}
			case TYPE::BUS_RIGHT:
			{
				while (threat.size() < numEnemyInRow)
				{
					if (threat.empty())
					{

						//threaten.push_back(new Car(randDistance(gen) - 30, pos_row));
						threat.push_back(new Truck((float)randDistance_right + 30, (float)y_coord));
					}
					else if (threat.size() < numEnemyInRow)
					{
						/*int prevCoordX = threaten.back()->getX();
						Car* temp = new Car(randExDistance(gen) + prevCoordX + 30, pos_row);
						threaten.push_back(temp->getBird());
						delete temp;*/
						float prevCoordX = threat.back()->getX();
						float distance_temp = -randExDistance + prevCoordX - 30;
						if (distance_temp > -200)
						{
							//threat.insert(threat.begin(), (new Car((float)randDistance_right + 30, (float)y_coord)));

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

						//threaten.push_back(new Car(randDistance(gen) - 30, pos_row));
						threat.push_back(new Bird((float)randDistance_right + 30, (float)y_coord));
					}
					else if (threat.size() < numEnemyInRow)
					{
						/*int prevCoordX = threaten.back()->getX();
						Car* temp = new Car(randExDistance(gen) + prevCoordX + 30, pos_row);
						threaten.push_back(temp->getBird());
						delete temp;*/
						float prevCoordX = threat.back()->getX();
						float distance_temp = -randExDistance + prevCoordX - 30;
						if (distance_temp > -200)
						{
							//threat.insert(threat.begin(), (new Car((float)randDistance_right + 30, (float)y_coord)));

							threat.push_back(new Bird((float)distance_temp, (float)y_coord));
						}
					}
					break;
				}
			case TYPE::DINOSAUR:
			{
				while (threat.size() < numEnemyInRow)
				{
					if (threat.empty())
					{

						//threaten.push_back(new Car(randDistance(gen) - 30, pos_row));
						threat.push_back(new Dinosaur((float)randDistance_right + 30, (float)y_coord));
					}
					else if (threat.size() < numEnemyInRow)
					{
						/*int prevCoordX = threaten.back()->getX();
						Car* temp = new Car(randExDistance(gen) + prevCoordX + 30, pos_row);
						threaten.push_back(temp->getBird());
						delete temp;*/
						float prevCoordX = threat.back()->getX();
						float distance_temp = -randExDistance + prevCoordX - 30;
						if (distance_temp > -200)
						{
							//threat.insert(threat.begin(), (new Car((float)randDistance_right + 30, (float)y_coord)));

							threat.push_back(new Dinosaur((float)distance_temp, (float)y_coord));
						}
					}
				}
				break;
			}
			}
			break;
			}
			}
		}
	}
	int random_int(int min, int max)
	{
		return min + rand() % (max + 1 - min);
	}
	bool checkWall_left(float x)
	{
		x *= render_state.height * render_scale;
		x += render_state.width / 2.f;
		if (x > 0)
			return true;
		return false;
	}
	bool checkWall_right(float x)
	{
		x *= render_state.height * render_scale;
		x += render_state.width / 2.f;
		if (x < render_state.width)
			return true;
		return false;
	}
	void move(float speed, float dt)
	{
		switch (dir)
		{
		case LEFT:
		{
			switch (type)
			{
			case BIRD:
			{
				for (auto x : threat)
				{

					x->left(speed, dt, lv);
					if (checkWall_left(x->getX()))
						draw_bird(x->getX(), x->getY(), x->getHalfX(), x->getHalfY());
					else
						threat.erase(threat.end());
				}break;
			}
			case DINOSAUR:
			{
				for (auto x : threat)
				{
						x->left(speed, dt, lv);
						if (checkWall_left(x->getX()))
							//draw_entities(DINOSAUR, x->getX(), x->getY(), .5f, 0xFFFFF);
							draw_titan(x->getX(), x->getY(), x->getHalfX(), x->getHalfY());
						else
							threat.erase(threat.end());
				}break;
			}
			case CAR_LEFT||CAR2_LEFT:
			{
				for (auto x : threat)
				{
					x->left(speed, dt, lv);
					if (checkWall_left(x->getX()))
					{
						/*if (type 
							draw_entities(CAR_RIGHT, x->getX(), x->getY(), .5f, 0xFFFFF);
						else draw_entities(CAR2_RIGHT, x->getX(), x->getY(), .5f, 0xFFFFF);*/
						(type == CAR_LEFT)
							? draw_entities(CAR_LEFT, x->getX(), x->getY(), .5f, 0xFFFFF)
							: draw_entities(CAR2_LEFT, x->getX(), x->getY(), .5f, 0xFFFFF);
					}
					else
						threat.erase(threat.end());
				}break;
			}
			case BUS_LEFT:
			{
				for (auto x : threat)
				{
					x->left(speed, dt, lv);
					if (checkWall_left(x->getX()))
					{
						//draw_rect(x->getX(), x->getY(), 1, 1, 0xccccccccccc);
						draw_entities(BUS_LEFT, x->getX(), x->getY(), .5f, 0xFFFFF);
					}
					else
						threat.erase(threat.end());
				}break;
			}
			}
			break;
		}
		case RIGHT:
		{
			switch (type)
			{
			case BIRD:
			{
				for (auto x : threat)
				{
					x->right(speed, dt, lv);
					if (checkWall_right(x->getX()))
						//draw_entities(BIRD,x->getX(), x->getY(),.5f,0xFFFFF);
						draw_bird(x->getX(), x->getY(), x->getHalfX(), x->getHalfY());
					else
						threat.erase(threat.end());

				}break;
			}
			case DINOSAUR:
			{
				for (auto x : threat)
				{
					x->right(speed, dt, lv);
					if (checkWall_right(x->getX()))
						//draw_entities(DINOSAUR,x->getX(), x->getY(), .5f,0xFFFFF);
						draw_titan(x->getX(), x->getY(), x->getHalfX(), x->getHalfY());

					else
						threat.erase(threat.end());

				}break;
			}
			case CAR_RIGHT|CAR2_RIGHT:
			{
				for (auto x : threat)
				{
					x->right(speed, dt, lv);
					if (checkWall_right(x->getX()))
						(type == CAR_RIGHT)
						? draw_entities(CAR_LEFT, x->getX(), x->getY(), .5f, 0xFFFFF)
						: draw_entities(CAR2_LEFT, x->getX(), x->getY(), .5f, 0xFFFFF);
					else
						threat.erase(threat.end());

				}break;
			}
			case BUS_RIGHT:
			{
				for (auto x : threat)
				{
					x->right(speed, dt, lv);
					if (checkWall_right(x->getX()))
						draw_entities(BUS_RIGHT,x->getX(), x->getY(), .5f,0xFFFFF);
					else
						threat.erase(threat.end());

				}break;
			}
			}
			break;
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
