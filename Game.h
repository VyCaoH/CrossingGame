#pragma once
#include "Animal.h"
#include "Vehicle.h"
#include "Player.h"
#include "Scene.h"
#include "Win32Helper.h"
#include <cstdint>
#include "MMSystem.h"
#pragma comment(lib, "winmm.lib")

#include "Windows.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <cstdio>
#include <conio.h>
#include <fstream>
#include <string>
#include <algorithm>

static bool g_isRunning = false; // True if the game it currently running (false on pause, main menu...)
static bool g_isPause = false; // True if the game is pause
static bool g_isMainMenu = true; // True if the game is at main menu
static bool g_isDeadMenu = false; //True if the player is dead
static bool g_isAnimate = false; //True if the game is running an animation
static bool g_isMusic = true;

#define OFF	0
#define ON	-1

class Game
{
private:
	int level_; // Current level
	Player player_; // Player

	int vol;
	Scene gameScene; // Scene for displaying the game
	std::vector<Row*> row; // Manage each row in the scene
public:
	Game()
	{
		level_ = 0;
		vol = 100;
	}

	~Game()
	{
	}

	std::vector<Row*>& getRow()
	{
		return row;
	}

	int getLevel() const
	{
		return level_;
	}

	/// <summary>
	/// Display generated Buffer to the monitor
	/// Causion when use outside of SubThread
	/// </summary>
	void PrintBuffer()
	{
		gameScene.PrintBuffer();
	}

	/// <summary>
	/// Display main menu
	/// </summary>
	void mainMenu()
	{
		gameScene.drawMainMenu();
		gameScene.PrintBuffer();
	}

	/// <summary>
	/// Play music of game
	/// </summary>
	void playMusic()
	{
		DWORD dwVol = ON;
		waveOutSetVolume(NULL, dwVol);

		PlaySound(TEXT("Music\\music.wav"), NULL, SND_ASYNC | SND_LOOP);
	}

	void stopMusic()
	{
		PlaySound(NULL, NULL, SND_ASYNC);
	}

	/// <summary>
	/// Generate and display ALL elements of the game
	/// </summary>
	void drawNormalGame()
	{
		gameScene.drawScene(level_);

		for (auto x : row)
			gameScene.drawOneRow(*x);

		gameScene.drawEntity(player_);
		gameScene.drawManual();
		gameScene.PrintBuffer();
	}

	//Remember to pause the game
	void playerDead()
	{
		gameScene.drawDeadMenu();
		gameScene.PrintBuffer();
	}

	void setPlayerDead()
	{
		player_.setState(false);
	}

	const Player& getPlayer() const
	{
		return player_;
	}

	void levelUp()
	{
		level_++;
	}

	void resetLevel()
	{
		level_ = 0;
	}

	void resetGame()
	{
		row.clear();
		updatePosPeople(' ');
		updateRows();
		drawNormalGame();
	}

	void exitGame(std::thread& thd)
	{
		ClearConsoleScreen();
		thd.join();
	}

	void startGame()
	{
		g_isRunning = true;
		player_.setState(true);

		player_.move(55, 27);
	}

	void loadGame()
	{
		std::deque<std::string> listName;
		std::deque<int> listLevel;

		//Get data
		std::fstream input("SaveGame.txt", std::ios::in);
		std::string name;
		int lvl;
		while (input.eof() == false)
		{
			input >> lvl;
			input.ignore(80, ' ');
			getline(input, name);
			listName.push_back(name);
			listLevel.push_back(lvl);
		}
		listName.pop_back();
		listLevel.pop_back();
		input.close();

		//Update the number of data in the file
		int n = listName.size();
		if (n > 10)
		{
			for (int i = 0; i < n - 10; i++)
			{
				listName.erase(listName.begin());
				listLevel.erase(listLevel.begin());
			}
			n = listName.size();
			std::fstream output("SaveGame.txt", std::ios::out);
			for (int i = 0; i < n; i++)
				output << listLevel[i] << " " << listName[i] << std::endl;
			output.close();
		}

		gameScene.drawLoadMenu();
		for (int i = 0; i < n; i++)
		{
			gameScene.setStrToBuffer(38, 11 + i, listName[i]);
			gameScene.setStrToBuffer(52, 11 + i, "level: " + std::to_string(listLevel[i]));
		}
		gameScene.PrintBuffer();

		GotoXY(55, 22); getline(std::cin, name);
		gameScene.clearPrevBuffer();
		gameScene.PrintBuffer();

		for (int i = 0; i < n; i++)
			if (name == listName[i])
			{
				level_ = listLevel[i];
				resetGame();
				startGame();
			}
	}

	void saveGame()
	{
		gameScene.drawSaveMenu();
		gameScene.PrintBuffer();

		std::string name;
		GotoXY(52, 16); getline(std::cin, name);
		gameScene.clearPrevBuffer();
		gameScene.PrintBuffer();

		std::fstream out("SaveGame.txt", std::ios::app);
		out << level_ << " " << name << std::endl;
		out.close();
	}

	void pauseGame()
	{
		gameScene.drawPauseMenu();
		gameScene.PrintBuffer();
	}

	void pauseSystem(HANDLE hd)
	{
		SuspendThread(hd);
	}

	void resumeSystem(HANDLE hd)
	{
		ResumeThread(hd);
	}

	void atMainMenu(char input, HANDLE hd)
	{
		if (input == 'N')
		{
			g_isMainMenu = false;
		}
		else if (input == 'T')
		{
			pauseSystem(hd);
			loadGame();
			g_isMainMenu = false;
			resumeSystem(hd);
		}
		else if (input == 'S')
		{
			int newVol = 0;
			pauseSystem(hd);
			gameScene.drawSettingMenu();
			gameScene.PrintBuffer();

			GotoXY(81, 21);
			char settingInput = toupper(_getch());
			if (settingInput == 'T')
			{
				g_isMusic = !g_isMusic;
				if (g_isMusic)
					playMusic();
				else
					stopMusic();
			}
			gameScene.clearPrevBuffer();
			gameScene.PrintBuffer();
			resumeSystem(hd);
		}
		else if (input == 27)
		{
			g_isRunning = false;
		}
		gameScene.clearPrevBuffer();
	}

	void deadScene(unsigned int deadBy)
	{
		g_isAnimate = true;
		if (deadBy == 2)
		{
			PlaySound(TEXT("Music\\Bird.wav"), NULL, SND_ASYNC);
			gameScene.deadByBird();
		}
		else if (deadBy == 3)
		{
			PlaySound(TEXT("Music\\Dino.wav"), NULL, SND_ASYNC);
			gameScene.deadByDino();
		}
		else
		{
			PlaySound(TEXT("Music\\Car.wav"), NULL, SND_ASYNC);
			gameScene.deadByVehicle();
		}
		g_isAnimate = false;
	}

	void updatePosPeople(char moveKey)
	{
		if (moveKey == 'W')
			player_.Up();
		else if (moveKey == 'A')
			player_.Left();
		else if (moveKey == 'S')
			player_.Down();
		else if (moveKey == 'D')
			player_.Right();
	}

	void updateRows()
	{
		// Initialize
		if (row.empty())
		{
			row.push_back(new Row(7));
			row.push_back(new Row(12));
			row.push_back(new Row(17));
			row.push_back(new Row(22));
		}

		for (auto& x : row)
		{
			x->AtLevel(level_);
			x->append();
			x->move();
		}
	}
};