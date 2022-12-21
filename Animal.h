#pragma once
#include"Entity.h"
#include<fstream>
#include<string>
#include<iostream>
#include <vector>

using namespace std;
class Animal:public Entity
{
public:
};

class Bird : public Animal
{
private:
	float bird_half_X, bird_half_Y;
	float bird_pX, bird_pY;
	bool is_right;

protected:
	vector<vector<char>> entity;
public:
	Bird();
	Bird(float posX, float posY);
	void left(float speed, float dt, int lv) override;
	void right(float speed, float dt, int lv) override;
	float getX() const override;
	float getY() const override;
	float getHalfX() const override;
	float getHalfY()const override;
	bool Right();
	void setHalf(float x, float y) override;
};
class Dinosaur : public Animal
{
private:
	bool is_right;
	float dinosaur_half_X, dinosaur_half_Y;
	float dinosaur_pX,dinosaur_pY;
protected:
	vector<vector<char>> entity;
public:
	Dinosaur();
	Dinosaur(float posX, float posY);
	void left(float speed, float dt, int lv) override;
	void right(float speed, float dt, int lv) override;
	float getHalfX() const override;
	float getHalfY()const override;
	float getX() const override;
	float getY() const override;
	void setX(float src) override;
	void setY(float src) override;
	bool Right();
	void setHalf(float x, float y) override;
};
