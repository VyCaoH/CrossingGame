#pragma once
//#include<fstream>
#include<fstream>
#include<string>
#include <vector>
#include<iostream>

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
	Player()
	{
		isDead = false;
		player_dp = 0;
		player_ddp = 0;
		//height = width = 0;
		player_pX = 0;
		player_pY= -40;
		entity.clear();
		player_half_X = 2.5;
		player_half_Y = 5;
	}
	float getHalfX()
	{
		return player_half_X;
	}
	float getHalfY()
	{
		return player_half_Y;
	}
	void up(float speed, float dt)
	{
		player_pY += speed*dt;
	}
	void down(float speed, float dt) {
		player_pY -= speed * dt;
	}
	void left(float speed, float dt) {
		player_pX -= speed * dt;
	}
	void right(float speed, float dt) {
		player_pX += speed * dt;
	}
	float getX()
	{
		return player_pX;
	}
	float getY()
	{
		return player_pY;
	}
	float getDP()
	{
		return player_dp;
	}
	void setX(float src)
	{
		player_pX = src;
	}
	void setY(float src)
	{
		player_pY = src;
	}
	void setDP(float src)
	{
		player_dp = src;
	}
	void setDDP(float src)
	{
		player_ddp = src;
	}
	float getDDP()
	{
		return player_ddp;
	}

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
