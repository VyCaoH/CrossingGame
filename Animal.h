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
	float bird_dp;//van toc
	//int height,width;
	float bird_half_X, bird_half_Y;
	float bird_pX, bird_pY;
	bool is_right;

protected:
	//float bird_pX, bird_pY;
	vector<vector<char>> entity;
public:
	Bird()
	{
		bird_dp = 0;
		//height = width = 0;
		is_right = true;
		bird_pX = 0;
		bird_pY = 0;
		entity.clear();
	}
	Bird(float posX, float posY)
	{
		//bird = new Bird("Bird-Left.txt");
		bird_pX = posX;
		bird_pY =posY;
		//bird->setXY(posX, posY);
		//bird->setXY(getX(), getY());
	}
	//Entity* getBird() const
	//{
	//	/*bird->setXY(getX(), getY());
	//	Entity temp=*bird;*/
	//	return bird;
	//}
	void left(float speed,float dt,int lv) override
	{
		bird_pX -= speed * dt *lv;
	}
	void right(float speed, float dt,int lv) override {
		bird_pX += speed * dt*lv;
	}
	float getX() const override
	{
		return bird_pX;
	}
	float getY() const override
	{
		return bird_pY;
	}
	float getHalfX() const override
	{
		return bird_half_X;
	}
	float getHalfY()const override
	{
		return bird_half_Y;
	}
	float getDP()
	{
		return bird_dp;
	}
	bool Right()
	{
		return is_right;
	}
	void setHalf(float x, float y) override
	{
		bird_half_X = x;
		bird_half_Y = y;
	}
};
class Dinosaur : public Animal
{
private:
	float dinosaur_dp;//van toc
	int height, width;
	bool is_right;
	float dinosaur_half_X, dinosaur_half_Y;
	float dinosaur_pX,dinosaur_pY;
protected:
	vector<vector<char>> entity;
public:
	Dinosaur()
	{
		dinosaur_dp = 0;
		height = width = 0;
		is_right = true;
		dinosaur_pX = 0;
		dinosaur_pY = 0;
		entity.clear();
	}
	Dinosaur(float posX, float posY)
	{
		//Dinosuar = new Dinosuar("Dinosuar-Left.txt");
		dinosaur_pX = posX;
		dinosaur_pY = posY;
		//Dinosuar->setXY(posX, posY);
		//Dinosuar->setXY(getX(), getY());
	}
	//Entity* getBird() const
	//{
	//	/*Dinosuar->setXY(getX(), getY());
	//	Entity temp=*Dinosuar;*/
	//	return Dinosuar;
	//}
	void left(float speed, float dt,int lv) override
	{
		dinosaur_pX -= speed * dt*lv;
	}
	void right(float speed, float dt,int lv) override {
		dinosaur_pX += speed * dt*lv;
	}
	float getHalfX() const override
	{
		return dinosaur_half_X;
	}
	float getHalfY()const override
	{
		return dinosaur_half_Y;
	}
	float getX() const override
	{
		return dinosaur_pX;
	}
	float getY() const override
	{
		return dinosaur_pY;
	}
	void setX(float src) override
	{
		dinosaur_pX = src;
	}
	virtual void setY(float src) override
	{
		dinosaur_pY = src;
	}
	float getDP()
	{
		return dinosaur_dp;
	}
	bool Right()
	{
		return is_right;
	}
	void setHalf(float x, float y) override
	{
		dinosaur_half_X = x;
		dinosaur_half_Y = y;
	}
};
//	~Bird();
//
//	Limits getLimits(bool isRight = 0) const override
//	{
//		return (isRight) ? *birdLmtRight : *birdLmtLeft;
//	}
//
//	SHORT getLimitofHeight()const override
//	{
//		return birdLmtRight->getHeight();
//	}
//
//	SHORT getLimitofWidth() const override
//	{
//		return birdLmtRight->getWidth();
//	}
//};
//
//class Dinosaur : public Animal
//{
//private:
//	static Limits* dinoLmtRight;
//	static Limits* dinoLmtLeft;
//public:
//	Dinosaur(int x, int y);
//
//	~Dinosaur();
//
//	Limits getLimits(bool isRight = 0) const override
//	{
//		return (isRight) ? *dinoLmtRight : *dinoLmtLeft;
//	}
//	SHORT getLimitofHeight()const override
//	{
//		return dinoLmtRight->getHeight();
//	}
//
//	SHORT getLimitofWidth() const override
//	{
//		return dinoLmtRight->getWidth();
//	}
//};
//#endif // _ANIMAL