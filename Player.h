#pragma once
//#include<fstream>
//#include<string>
#include <vector>
#include<iostream>
#include"ConsoleWindow.h"
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
	void move(Input *input, float dt, float speed);
	void checkWall(float x, float y, float half_x, float half_y);
};