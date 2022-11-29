#pragma once
#include <vector>	
#include <iostream>
#include <fstream>
#include "ConsoleWindow.h"
#include <sstream>
#include <algorithm>
using namespace std;
class Score
{
	int score;
	vector<int> highscore;
public:
	Score() 
	{ score = 0;for (int i = 0; i < 3; i++)
		{
		highscore.push_back(0);
		}
	}
	~Score()
	{
		highscore.clear();
	}
	int getScore();
	void setScore(int x);
	void DisplayScore();
	void readHighScore();
	void writeHighScore();
	void DisplayHighScore();
};

