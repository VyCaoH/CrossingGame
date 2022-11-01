#include "Scene.h"

const char Scene::DeadMenu[7][33] = {
	{"################################"},
	{"#                              #"},
	{"#       Your are dead...       #"},
	{"#          Continue?           #"},
	{"#    Y: Restart  Others: End   #"},
	{"#                              #"},
	{"################################"}
};

const char Scene::LoadMenu[16][41] = {
	{"########################################"},
	{"#              LOAD GAME:              #"},
	{"#                                      #"},
	{"#                                      #"}, //Max: 10
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#                                      #"},
	{"#  Enter load file:                    #"},
	{"########################################"}
};

const char Scene::SaveMenu[5][41] = {
	{"########################################"},
	{"#              SAVE GAME:              #"},
	{"#                                      #"},
	{"#  Name of file:                       #"},
	{"########################################"}
};
const char Scene::PauseMenu[6][41] = {
	{"########################################"},
	{"#                                      #"},
	{"#              PAUSED GAME             #"},
	{"#       Press any key to resume...     #"},
	{"#                                      #"},
	{"########################################"}
};

const char Scene::MainMenu[7][27] = {
	{"##########################"},
	{"#                        #"},
	{"#      N: New Game       #"},
	{"#      T: Load Game      #"},
	{"#      S: Setting        #"},
	{"#                        #"},
	{"##########################"}
};

const char Scene::Setting[7][27] = {
	{"##########################"},
	{"#                        #"},
	{"#   T: Toggle Music      #"},
	{"#                        #"},
	{"#   Others: Back         #"},
	{"#                        #"},
	{"##########################"}
};


const char Scene::Manual[5][26] = {
	{"         MANUAL          "},
	{"[W] Up          [P] Pause"},
	{"[S] Down        [L] Save "},
	{"[A] Left        [T] Load "},
	{"[D] Right                "}
};


Scene::Scene()
{
	memset(_contentBuffer, (int)' ', 150 * 30);
	memset(_prevContentBuffer, (int)' ', 150 * 30);

	memset(_prevForegroundBuffer, FOREGROUND_WHITE, 150 * 30);
	memset(_foregroundBuffer, FOREGROUND_WHITE, 150 * 30);

	memset(_prevLight, int(LightMode::RED), sizeof(LightMode::RED) * 4);
	memset(_light, int(LightMode::RED), sizeof(LightMode::RED) * 4);

	_logo.openFile("Sprites\\MainScreen.txt");
}

// Getter
int Scene::getCol() const
{
	return _row;
}

int Scene::getRow() const
{
	return _playCol;
}

void Scene::setStrToBuffer(int col, int row, std::string nd)
{
	for (int i = 0; i < nd.size(); i++)
		_contentBuffer[row][col + i] = nd[i];
}

void Scene::clearPrevBuffer()
{
	memset(_prevContentBuffer, (int)'&', 150 * 30);

	memset(_prevLight, int(LightMode::RED), sizeof(LightMode::RED) * 4);
}

/// <summary>
/// Display generated Buffer to the monitor
/// </summary>
void Scene::PrintBuffer()
{
	for (SHORT r = 0; r < 30; ++r)
	{
		for (SHORT c = 0; c < 150; ++c)
		{
			if (_contentBuffer[r][c] == _prevContentBuffer[r][c] && _foregroundBuffer[r][c] == _prevForegroundBuffer[r][c])
				continue;
			else if (_contentBuffer[r][c] != _prevContentBuffer[r][c] && _foregroundBuffer[r][c] == _prevForegroundBuffer[r][c])
			{
				GotoXY(c, r);
				std::cout << _contentBuffer[r][c];
			}
			else
			{
				GotoXY(c, r);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _foregroundBuffer[r][c]);
				std::cout << _contentBuffer[r][c];
			}
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		if (_light[i] != _prevLight[i])
		{
			GotoXY(_playCol + 2, (i + 1) * 5 + 2);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (_light[i] == LightMode::GREEN) ? 10 : 12);
			std::cout << _contentBuffer[(i + 1) * 5 + 2][_playCol + 2];
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	std::cout.flush();

	std::memcpy((char*)_prevContentBuffer, (char const*)_contentBuffer, 150 * 30);
	std::memcpy((char*)_prevForegroundBuffer, (char const*)_foregroundBuffer, 150 * 30);
	std::memcpy((char*)_prevLight, (char const*)_light, sizeof(LightMode::GREEN) * 4);

	memset(_foregroundBuffer, FOREGROUND_WHITE, 150 * 30);
}

/// <summary>
/// Generate and display ALL elements of the game
/// </summary>
void Scene::drawScene(int level_)
{
	//ClearConsoleScreen();

	for (int i = 0; i < _row; ++i)
		_contentBuffer[i][_totalCol - 1] = '\n';

	for (int r = 0; r < _row; ++r)
	{
		for (int c = 0; c < _totalCol - 40; ++c)
		{
			if (r == 0 || r == _row - 1)
				_contentBuffer[r][c] = '#';
			else if (r % 5 == 0)
			{
				if (c == 0 || c == _totalCol - 41)
					_contentBuffer[r][c] = '#';
				else
					_contentBuffer[r][c] = '_';
			}
			else
			{
				if (c == 0 || c == _totalCol - 41)
					_contentBuffer[r][c] = '#';
				else
					_contentBuffer[r][c] = ' ';
			}
		}
	}

	snprintf((*(_contentBuffer + _row / 2) + _playCol + 2), 14, "Level: %d", level_);

	snprintf((*(_contentBuffer + 7) + _playCol + 2), 2, "%c", 254);
	snprintf((*(_contentBuffer + 12) + _playCol + 2), 2, "%c", 254);
	snprintf((*(_contentBuffer + 17) + _playCol + 2), 2, "%c", 254);
	snprintf((*(_contentBuffer + 22) + _playCol + 2), 2, "%c", 254);
}

void Scene::deadByBird()
{
	int x = 5, y = 20;

	std::fstream file("Scene\\BirdDeath.txt");
	int r, c, total;
	file >> r;
	file >> c;
	file >> total;
	file.ignore();

	for (int i = 0; i < total; ++i)
	{
		for (int j = 0; j < r; ++j)
		{
			std::string temp;
			getline(file, temp);
			setStrToBuffer(y, x + j, temp);
		}
		file.ignore();
		PrintBuffer();
		Sleep(225);
	}

	file.close();
}

void Scene::deadByDino()
{
	int x = 5, y = 19;

	std::fstream file("Scene\\DinoDeath.txt");
	int r, c, total;
	file >> r;
	file >> c;
	file >> total;
	file.ignore();

	for (int i = 0; i < total; ++i)
	{
		for (int j = 0; j < r; ++j)
		{
			std::string temp;
			getline(file, temp);
			setStrToBuffer(y, x + j, temp);
		}
		file.ignore();
		PrintBuffer();
		Sleep(300);
	}

	Sleep(150);
	file.close();
}

void Scene::deadByVehicle()
{
	int x = 8, y = 20;

	std::fstream file("Scene\\CarDeath.txt");
	int r, c, total;
	file >> r;
	file >> c;
	file >> total;
	file.ignore();

	for (int i = 0; i < total; ++i)
	{
		for (int j = 0; j < r; ++j)
		{
			std::string temp;
			getline(file, temp);
			setStrToBuffer(y, x + j, temp);
		}
		file.ignore();
		PrintBuffer();
		Sleep(250);
	}

	file.close();
}

void Scene::drawEntity(const Entity & obj, bool isRight)
{
	for (int y = 0; y < obj.getSpriteHeight(); ++y)
		for (int x = 0; x < obj.getSpriteWidth(); ++x)
		{
			if ((y + obj.getY() - obj.getBound(0) > 0 && y + obj.getY() - obj.getBound(0) < _row - 1) && (x + obj.getX() - obj.getBound(3) > 0 && x + obj.getX() - obj.getBound(3) < _playCol - 1))
				_contentBuffer[y + obj.getY() - obj.getBound(0)][x + obj.getX() - obj.getBound(3)] = obj.getSprite(isRight)[y][x];
		}
}

void Scene::drawOneRow(const Row & obj) // Draw rows here
{
	//Draw traffic light
	if (obj.GetRedLight())
		_light[(obj.GetY() - 2) / 5 - 1] = LightMode::RED;
	else
		_light[(obj.GetY() - 2) / 5 - 1] = LightMode::GREEN;

	for (auto& enemy : obj.GetList())
		drawEntity(*enemy, !obj.getIsFromRight());
}

void Scene::drawMainMenu()
{
	for (int i = 0; i < _logo.getHeight(); ++i)
	{
		for (int j = 0; j < _logo.getWidth(); ++j)
		{
			_contentBuffer[i][j] = _logo[i][j];
			_foregroundBuffer[i][j] = FOREGROUND_LIGHT_GREEN;
		}
	}

	for (int i = 0; i < 7; ++i)
		memcpy((char*)(_contentBuffer[i + 19] + 61), (char*)(MainMenu[i]), strlen(MainMenu[0]));
}

void Scene::drawSettingMenu()
{
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 27; ++j)
		{
			_contentBuffer[i + 19][j + 61] = Setting[i][j];
			_foregroundBuffer[i + 19][j + 61] = FOREGROUND_LIGHT_GREEN;
		}
}

void Scene::drawDeadMenu()
{
	for (int i = 0; i < 7; ++i)
	{
		memcpy((char*)(_contentBuffer[i + 12] + 39), (char*)(DeadMenu[i]), strlen(DeadMenu[0]));
		memset(_foregroundBuffer[i + 12] + 39, FOREGROUND_RED, sizeof(char) * strlen(DeadMenu[0]));
	}
}

void Scene::drawLoadMenu()
{
	for (int i = 0; i < 16; ++i)
		memcpy((char*)(_contentBuffer[i + 8] + 35), (char*)(LoadMenu[i]), strlen(LoadMenu[0]));
}

void Scene::drawSaveMenu()
{
	for (int i = 0; i < 5; ++i)
		memcpy((char*)(_contentBuffer[i + 13] + 35), (char*)(SaveMenu[i]), strlen(SaveMenu[0]));
}

void Scene::drawPauseMenu()
{
	for (int i = 0; i < 6; ++i)
		memcpy((char*)(_contentBuffer[i + 13] + 35), (char*)(PauseMenu[i]), strlen(PauseMenu[0]));
}

void Scene::drawManual()
{
	for (int i = 0; i < 5; ++i)
		memcpy((char*)(_contentBuffer[i + 5] + 118), (char*)(Manual[i]), strlen(Manual[0]));
}