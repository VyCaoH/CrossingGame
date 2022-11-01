#ifndef _SCENE
#define _SCENE

#include <iostream>
#include <vector>
#include <string>
#include "Row.h"
#include "Sprite.h"
#include "Pixel.h"
#include "Win32Helper.h"

enum class LightMode
{
	RED, GREEN
};

class Scene
{
private:
	int _row = 30, _playCol = 110, _totalCol = 150;

	char _prevContentBuffer[30][150];
	char _contentBuffer[30][150];

	char _prevForegroundBuffer[30][150];
	char _foregroundBuffer[30][150];

	LightMode _prevLight[4];
	LightMode _light[4];

	Sprite _logo;
public:
	Scene();

	~Scene() = default;

	// Getter
	int getCol() const;

	int getRow() const;

	void setStrToBuffer(int col, int row, std::string nd);

	void clearPrevBuffer();

	/// <summary>
	/// Display generated Buffer to the monitor
	/// </summary>
	void PrintBuffer();

	/// <summary>
	/// Generate and display ALL elements of the game
	/// </summary>
	void drawScene(int level_);

	void deadByBird();

	void deadByDino();

	void deadByVehicle();

	void drawEntity(const Entity& obj, bool isRight = false);

	void drawOneRow(const Row& obj); // Draw rows here

	void drawMainMenu();

	void drawSettingMenu();

	void drawDeadMenu();

	void drawLoadMenu();

	void drawSaveMenu();

	void drawPauseMenu();

	void drawManual();

	const static char DeadMenu[7][33];
	const static char LoadMenu[16][41];
	const static char SaveMenu[5][41];
	const static char PauseMenu[6][41];
	const static char MainMenu[7][27];
	const static char Setting[7][27];
	const static char Manual[5][26];
};

#endif //!_SCENE