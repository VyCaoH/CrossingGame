#pragma once
#include"Entity.h"
#include<fstream>
#include<string>
#include<iostream>
#include <vector>

using namespace std;
class Vehicle:public Entity
{
};
class Car : public Vehicle
{
private:
	float car_dp;//van toc
	int height, width;
	bool is_right;
	float car_half_X, car_half_Y;
	float car_pX, car_pY;
protected:
	vector<vector<char>> entity;
public:
	Car()
	{
		car_dp = 0;
		height = width = 0;
		is_right = true;
		car_pX = 0;
		car_pY = 0;
		entity.clear();
	}
	Car(float posX, float posY)
	{
		//Dinosuar = new Dinosuar("Dinosuar-Left.txt");
		car_pX = posX;
		car_pY = posY;
		//Dinosuar->setXY(posX, posY);
		//Dinosuar->setXY(getX(), getY());
	}
	void left(float speed, float dt,int lv) override
	{
		car_pX -= speed * dt * lv * .2f;
	}
	void right(float speed, float dt,int lv) override {
		car_pX += speed * dt * lv * .2f;
	}
	float getX() const override
	{
		return car_pX;
	}
	float getY() const override
	{
		return car_pY;
	}
	float getHalfX() const override
	{
		return car_half_X;
	}
	float getHalfY()const override
	{
		return car_half_Y;
	}
	float getDP()
	{
		return car_dp;
	}
	bool Right()
	{
		return is_right;
	}
};
class Truck : public Vehicle
{
private:
	float truck_dp;//van toc
	int height, width;
	bool is_right;
	float truck_half_X, truck_half_Y;
	float truck_pX, truck_pY;
protected:
	vector<vector<char>> entity;
public:
	Truck()
	{
		truck_dp = 0;
		height = width = 0;
		is_right = true;
		truck_pX = 0;
		truck_pY = 0;
		entity.clear();
	}
	Truck(float posX, float posY)
	{
		truck_pX = posX;
		truck_pY = posY;

	}


	void left(float speed, float dt, int lv) override
	{
		truck_pX -= speed * dt *0.1* lv;
	}
	void right(float speed, float dt, int lv) override {
		truck_pX += speed * dt * lv * .2f;;
	}
	float getX() const override
	{
		return truck_pX;
	}
	float getY() const override
	{
		return truck_pY;
	}
	float getHalfX() const override
	{
		return truck_half_X;
	}
	float getHalfY()const override
	{
		return truck_half_Y;
	}
	float getDP()
	{
		return truck_dp;
	}
	bool Right()
	{
		return is_right;
	}
};
