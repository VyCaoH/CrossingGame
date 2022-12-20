#pragma once
//#include<vector>
#include<Thread>
#include <deque>
//#include"Renderer.h"
#include"Player.h"
#include"Animal.h"
#include"Threat.h"
#include"ConsoleWindow.h"
#include"MenuGame.h"
#include"Score.h"
//#include"Renderer.h"
static string name="YOUR NAME IS ";
static enum gamemode { GM_MENUGAME, GM_PLAYGAME };
static bool g_running = true;
static bool g_pause=true;
static bool g_save = false;
static gamemode g_mode = GM_MENUGAME;
//static int count_name {}

//static BUTTON hot_button = (BUTTON) NEW_GAME;
class Game
{
	Player player;
	int lv;
	Score score;
	std::vector<Threat*> threat;
	TrafficLight lights;
	int name_count;
public:
	int playerScore = score.getScore();
	MenuGame menu;
	Game() 
	{
		player = Player();
		menu = MenuGame();
		lv = 1;
		score.readHighScore();
		name_count = 0;
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
	int getNameCount();
	void setHighScore();
	void simulate_game(Input* input, float dt);
	void simulate_menu(Input* input);
	vector<Threat*> getThreat();
	void startGame();
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
	bool saveGame(Input* input);
	void loadGame(Input* input, vector<string>listName, vector<int> listLevel);
	void FileLoadGame(vector<string>&listname, vector<int>& listlv);
};

