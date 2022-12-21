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
	bool is_right;
	float car_half_X, car_half_Y;
	float car_pX, car_pY;
protected:
	vector<vector<char>> entity;
public:
	Car();
	Car(float posX, float posY);
	void left(float speed, float dt, int lv) override;
	void right(float speed, float dt, int lv) override;
	float getX() const override;
	float getY() const override;
	float getHalfX() const override;
	float getHalfY()const override;
	bool Right();
	void setHalf(float x, float y) override;
	void setDP(float dp);
};
class Truck : public Vehicle
{
private:
	bool is_right;
	float truck_half_X, truck_half_Y;
	float truck_pX, truck_pY;
protected:
	vector<vector<char>> entity;
public:
	Truck();
	Truck(float posX, float posY);
	void left(float speed, float dt, int lv) override;
	void right(float speed, float dt, int lv) override;
	float getX() const override;
	float getY() const override;
	float getHalfX() const override;
	float getHalfY()const override;
	float getDP();
	void setDP(float dp);
	bool Right();
	void setHalf(float x, float y) override;
};
