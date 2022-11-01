#ifndef _SPRITE
#define _SPRITE
#include "Win32Helper.h"
#include <vector>
#include <fstream>
#include <iostream>

class Sprite
{
private:
	int height, width;
	std::vector<std::vector<char>> sprt;
public:
	Sprite();

	Sprite(const char* dir);

	~Sprite();

	std::vector<char> operator[](int index);

	void openFile(const char* dir);

	SHORT getHeight();

	SHORT getWidth();
};

#endif //_SPRITE