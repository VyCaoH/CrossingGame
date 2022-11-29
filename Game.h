#pragma once
//#include<vector>
#include<Thread>
//#include"Renderer.h"
#include"Player.h"
#include"Animal.h"
#include"Threat.h"
#include"Sound.h"
#include"ConsoleWindow.h"
#include"Score.h"
//#include"Renderer.h"
static enum gamemode { GM_MENUGAME, GM_PLAYGAME };
static bool g_running = true;
static bool g_pause=true;
static gamemode g_mode = GM_MENUGAME;
static bool g_sound = true;
static bool g_music_button = false;
static bool g_music_menu = false;
static BUTTON hot_button = NEW_GAME;
class Game
{
	Player player;
	int lv;
	Score score;
	//int time;
	std::vector<Threat*> threat;
	//vector<Row*> row;
public:
	Game() 
	{
		player = Player();
		lv = 1;
		score.readHighScore();
		threat.clear();
	};
	~Game()
	{
		for (auto x : threat)
			delete x;
		threat.clear();
	}
	Player getPlayer();
	int getLv();
	void setHighScore();
	vector<Threat*> getThreat();
	void startGame();
	void simulate_game(Input* input, float dt);
	BUTTON menu_game(Input* input);
	void reset_game();
	void restartGame();
	bool next_level();
	int overGame(Input* input);
	bool quit(Input* input);
	void threatMove(float dt);
	void updatePosThreat();
	bool exitGame(thread&t1);
	void pauseGame(HANDLE hd);
	void resumeGame(HANDLE hd);
};

