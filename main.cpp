#include "Game.h"

#include <iostream>
#include <thread>
#include <conio.h>
#include <ctime>

char MOVING;
Game* game;
bool getchNext;

void SubThread()
{
	int deadBy = 0;
	while (g_isRunning)
	{
		if (!getchNext)
		{
			continue;
		}

		if (g_isMainMenu)
		{
			game->mainMenu();
			continue;
		}
		if (g_isDeadMenu)
		{
			game->deadScene(deadBy);
			game->playerDead();
			getchNext = false;
			continue;
		}

		if (!game->getPlayer().isPlayerDead())
			game->updatePosPeople(MOVING);

		deadBy = 0;
		MOVING = ' ';
		game->updateRows();
		game->drawNormalGame();

		if ((deadBy = game->getPlayer().isImpact(game->getRow())))
		{
			deadBy--;
			game->setPlayerDead();
			game->resetLevel();
			g_isDeadMenu = true;
		}
		if (game->getPlayer().isAtFinishLine())
		{
			game->levelUp();
			game->resetGame();
			game->startGame();
		}

		//Sleep(50);
	}
}

void main()
{	
	game = new Game();
	getchNext = true;

	int tmp = 0;

	FixConsoleWindow();
	setConsoleFontSize();
	ResizeWindow();
	ShowConsoleCursor(false);

	game->playMusic();
	game->startGame();

	std::thread t1(SubThread);
	while (g_isRunning)
	{
		tmp = toupper(_getch());

		if (g_isAnimate)
			continue;
		if (g_isMainMenu)
		{
			game->atMainMenu(tmp, t1.native_handle());
			continue;
		}
		if (g_isPause)
		{
			g_isPause = false;
			game->resumeSystem(t1.native_handle());
		}
		if (g_isDeadMenu)
		{
			g_isDeadMenu = false;

			if (tmp == 'Y')
			{
				game->resetGame();
				game->startGame();
				game->playMusic();
			}
			else
				g_isRunning = false;

		}

		if (!game->getPlayer().isPlayerDead())
		{
			if (tmp == 27)
			{
				g_isRunning = false;
			}
			else if (tmp == 'P')
			{
				game->pauseSystem(t1.native_handle());
				game->pauseGame();
				g_isPause = true;
				MOVING = tmp;
			}
			else
			{
				game->resumeSystem(t1.native_handle());
				MOVING = tmp;
			}
			if (tmp == 'T')
			{
				game->pauseSystem(t1.native_handle());
				game->loadGame();
				game->resumeSystem(t1.native_handle());
			}
			if (tmp == 'L')
			{
				game->pauseSystem(t1.native_handle());
				game->saveGame();
				game->resumeSystem(t1.native_handle());
			}
		}

		getchNext = true;
	}

	game->exitGame(t1);
	game->stopMusic();
	return;
}