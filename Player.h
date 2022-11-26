#pragma once
//#include<fstream>
//#include<string>
#include <vector>
#include<iostream>

#include "Threat.h"
using namespace std;

class Player //:public Entity
{
	bool isDead; //true=dead, false=alive
	float player_dp;//van toc
	float player_ddp;
	float player_half_X, player_half_Y;
	//int height, width;
protected:
	float player_pX, player_pY;
	vector<vector<char>> entity;
public:
	Player();
	float getHalfX();
	float getHalfY();
	void up(float speed, float dt);	
	void down(float speed, float dt);
	void left(float speed, float dt);
	void right(float speed, float dt);
	float getX();
	float getY();
	float getDP();
	void setX(float src);
	void setY(float src);
	void setDP(float src);
	void setDDP(float src);
	float getDDP();
	bool isImpact(vector<Threat*> threat);
	void setIsDead(bool type);
	bool getIsDead();
};
	//void setHeight(int height);
	//void setWidth(int width);


////	//Player()
////	//{
////	//	ePlayer = new Entity("Bird - Right.txt");
////	//	isDead = false;
////	//	//ePlayer->setXY(10, 0);
////	//}
//////	//void setPlayer()
//////	//{
//////	//	ePlayer = new Entity("Bird-Right.txt");
//////	//}
//////	Entity* getePlayer()
//////	{
//////		return ePlayer;
//////	}
//////	void setXY(int posX, int posY)
//////	{
//////		ePlayer->setXY(posX, posY);
//////	}
//////
//////	void setState(bool state)
//////	{
//////		this->isDead = state;
//////	}

//////	//bool collision(vector<Threat*> threaten)
//////	//{
//////
//////	//	auto posYPlayer = this->getY();
//////	//	unsigned int inRow = 0;
//////
//////	//	/*if (posXPlayer == 3 || posXPlayer == 27)
//////	//	{
//////	//		return 0;
//////	//	}*/
//////	//	inRow = (unsigned int)(posYPlayer - 3) / 5 - 1;
//////
//////
//////	//	Threat* row = threaten[inRow];
//////
//////	//	unsigned int typeOfEnemy = row->getType();
//////	//	std::vector<Entity*> listEnemy = row->getListEntity();
//////
//////	//	for (auto& mem : listEnemy)
//////	//	{
//////	//		auto coordXEnemy = mem->getX();
//////
//////	//		// Enemy -> Player
//////	//		if (coordXEnemy < this->getX())
//////	//		{
//////	//			// Right | Left
//////	//			if (coordXEnemy + (mem->getX() - 1) / 2 >= this->getX() - this->getHeight() / 2)
//////	//				return true;
//////	//			else
//////	//				continue;
//////	//		}
//////
//////	//		if (coordXEnemy == this->getX())
//////	//			return true;
//////
//////	//		// Player -> Enemy
//////	//		if (coordXEnemy > this->getX())
//////	//		{
//////	//			if (this->getX() + (this->getHeight() - 1) / 2 >= coordXEnemy - mem->getHeight() / 2)
//////	//				return true;
//////	//			else
//////	//				continue;
//////	//		}
//////	//	}
//////
//////	/*	return false;
//////	}*/
//////	bool isPlayerDead()
//////	{
//////		return this->isDead;
//////	}
//////};
////////int getHeight() const override
////////{
////////	return ePlayer->getHeight();
////////}
////////int getWidth() const override
////////{
////////	return ePlayer->getWidth();
////////}
////////Entity* getPlayer()
////////{
////////	return ePlayer;
////////}
////////	void setXY(SHORT, SHORT);
////////	void moveLeft();
////////	void moveRight();
////////	void moveUp();
////////	void moveDown();
////////	bool isImpact();
////////	//int getX()
////////	//{
////////	//	return coord.X;
////////	//}
////////	//int getY()
////////	//{
////////	//	return coord.Y;
////////	//}
////////	//void setXY(int, int)const override;
////////};
////////
