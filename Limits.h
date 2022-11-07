#pragma once
#ifndef _LIMITS
#define _LIMITS
#include <iostream>
#include "ConsoleWindow.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
class Limits
{
private:
	int height, width;
	std::vector<std::vector<char>> lmt;
public:
	Limits();

	Limits(const char* dir);

	~Limits();

	vector <char> operator[](int index);

	void openFile(const char* dir);

	SHORT getHeight();

	SHORT getWidth();
};

#endif 