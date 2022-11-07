#include "Limits.h"

Limits::Limits()
{
	height = width = 0;
}

Limits::Limits(const char* dir)
{
	std::fstream inputLimits(dir, std::ios::in);
	if (inputLimits.is_open())
	{
		int height, width;
		inputLimits >> height;
		inputLimits.ignore();
		inputLimits >> width;
		inputLimits.ignore();

		for (int i = 0; i < height; ++i)
		{
			vector<char> tmp;
			for (int j = 0; j < width; ++j)
			{
				char c;
				inputLimits.get(c);
				tmp.push_back(c);
			}
			inputLimits.ignore();
			lmt.push_back(tmp);
		}
		inputLimits.close();

		height = lmt.size();
		width = lmt[0].size();
	}
}

Limits::~Limits()
{

}
//qua tai toan tu []
vector <char> Limits::operator[](int index) {
	return lmt[index];
}


void Limits::openFile(const char* dir) {
	std::fstream inputLimits(dir, std::ios::in);
	if (inputLimits.is_open())
	{
		int height, width;
		inputLimits >> height;
		inputLimits.ignore();
		inputLimits >> width;
		inputLimits.ignore();

		for (int i = 0; i < height; ++i)
		{
			vector<char> tmp;
			for (int j = 0; j < width; ++j)
			{
				char c;
				inputLimits.get(c);
				tmp.push_back(c);
			}
			inputLimits.ignore();
			lmt.push_back(tmp);
		}
		inputLimits.close();

		height = lmt.size();
		width = lmt[0].size();
	}
}

SHORT Limits::getHeight() {
	return height;
}

SHORT Limits::getWidth() {
	return width;
}