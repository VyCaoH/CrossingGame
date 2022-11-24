#pragma once
class Entity
{
private:
	int height, width;
	bool is_right;
	float entity_half_x, entity_half_y;
	float entity_pX, entity_pY;
protected:

public:
	virtual float getX() const;
	virtual float getY() const;
	virtual void setX(float src)
	{
		entity_pX = src;
	}
	virtual void setY(float src)
	{
		entity_pY = src;
	}
	virtual float getHalfX() const
	{
		return entity_half_x;
	}
	virtual float getHalfY() const
	{
		return entity_half_y;
	}
	virtual void left(float speed, float dt,int lv) {
		entity_pX -= speed * dt*lv;
	}
	virtual void right(float speed, float dt,int lv){
		entity_pX += speed * dt*lv;
	}
};
//#pragma once
//#include<vector>
//#include<string>
//#include<iostream>
//#include<fstream>
//
//#include"ConsoleWindow.h"
//
//using namespace std;
//
//class Entity
//{
//	int height, width;
//	vector<vector<char>>entity;
//	//COORD coord;
//public:
//};
////	Entity()
////	{
////		height = width = 0;
////		//coord.X = coord.Y = 0;
////	};
////	Entity(const char* file)
////	{
////		ifstream fileInput(file, ios::in);
////		if (fileInput.is_open())
////		{
////			int height, width;
////			fileInput >> height;
////			fileInput.ignore();
////			fileInput >> width;
////			fileInput.ignore();
////
////			while (!fileInput.eof())
////			{
////				string s;
////				vector<char>temp;
////				getline(fileInput, s);
////				for (int i = 0; i < s.length(); i++)
////					temp.push_back(s[i]);
////				entity.push_back(temp);
////			}
////			fileInput.close();
////			/*height = sprt.size();
////			width = sprt[0].size();*/
////			setHeight(height);
////			setWidth(width);
////		}
////	}
////	void setHeight(int);
////	void setWidth(int);
////	int getX() const;
////	int getY() const;
////	/*COORD getXY()
////	{
////		return coord;
////	}*/
////	vector<vector<char>>getEntity()const;
////	virtual int getHeight() const;
////	virtual int getWidth() const;
////	void setXY(SHORT, SHORT);
////	//virtual void moveUp();
////	//virtual void moveDown();
////	//virtual void moveLeft();
////	//virtual void moveRight();
////	void output()
////	{
////		for (int i = 0; i < height; i++)
////		{
////			for (int j = 0; j < width; j++)
////			{
////				cout << entity[i][j];
////			}
////			cout << endl;
////		}
////	}
////};
////
////
