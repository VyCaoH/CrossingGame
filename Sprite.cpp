#include "Sprite.h"

Sprite::Sprite()
{
	height = width = 0;
}

Sprite::Sprite(const char* dir)
{
	//Load sprite
	std::fstream inputSprite(dir, std::ios::in);
	if (inputSprite.is_open())
	{
		int height, width;
		inputSprite >> height;
		inputSprite.ignore();
		inputSprite >> width;
		inputSprite.ignore();

		for (int i = 0; i < height; ++i)
		{
			std::vector<char> temp;
			for (int j = 0; j < width; ++j)
			{
				char chr;
				inputSprite.get(chr);
				temp.push_back(chr);
			}
			inputSprite.ignore();
			sprt.push_back(temp);
		}

		inputSprite.close();
	}

	height = sprt.size();
	width = sprt[0].size();
}
Sprite::~Sprite()
{

}

std::vector<char> Sprite::operator[](int index)
{
	return sprt[index];
}

void Sprite::openFile(const char* dir)
{
	//Load sprite
	std::fstream inputSprite(dir, std::ios::in);
	if (inputSprite.is_open())
	{
		int height, width;
		inputSprite >> height;
		inputSprite.ignore();
		inputSprite >> width;
		inputSprite.ignore();

		for (int i = 0; i < height; ++i)
		{
			std::vector<char> temp;
			for (int j = 0; j < width; ++j)
			{
				char chr;
				inputSprite.get(chr);
				temp.push_back(chr);
			}
			inputSprite.ignore();
			sprt.push_back(temp);
		}

		inputSprite.close();
	}

	height = sprt.size();
	width = sprt[0].size();
}

SHORT Sprite::getHeight()
{
	return height;
}

SHORT Sprite::getWidth()
{
	return width;
}