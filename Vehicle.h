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
		car_pX = posX;
		car_pY = posY;
	}
	Car(const char* file)
	{

		ifstream fileInput(file, ios::in);
		if (fileInput.is_open())
		{
			int height, width;
			fileInput >> height;
			fileInput.ignore();
			fileInput >> width;
			fileInput.ignore();

			while (!fileInput.eof())
			{
				for (int i = 0; i < height; ++i)
				{
					vector<char> tmp;
					for (int j = 0; j < width; ++j)
					{
						char c;
						fileInput.get(c);
						tmp.push_back(c);
					}
					fileInput.ignore();
					entity.push_back(tmp);
				}
				fileInput.close();
				/*height = sprt.size();
				width = sprt[0].size();*/
				this->height = height;
				this->width = width;
			}
		}
	}
	void left(float speed, float dt,int lv) override
	{
		car_pX -= speed * dt  *lv;
	}
	void right(float speed, float dt,int lv) override {
		car_pX += speed * dt*lv;
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
	void setHalf(float x, float y) override
	{
		car_half_X = x;
		car_half_Y = y;
	}
	void setDP(float dp)  {
		car_dp = dp;
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
		truck_pX -= speed * dt * lv;
	}
	void right(float speed, float dt,int lv) override {
		truck_pX += speed * dt*lv;
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
	void setDP(float dp)  {
		truck_dp = dp;
	}
	bool Right()
	{
		return is_right;
	}
	void setHalf(float x, float y) override
	{
		truck_half_X = x;
		truck_half_Y = y;
	}
};
