#pragma once
//#include<vector>
#include<Thread>
//#include"Renderer.h"
#include"Player.h"
#include"Animal.h"
#include"Threat.h"
#include"ConsoleWindow.h"
//#include"Renderer.h"
static enum gamemode { GM_MENUGAME, GM_PLAYGAME };
static bool g_running = true;
static bool g_pause=true;
static bool g_menu=true;
static bool g_music_button = false;
static bool g_music_menu = true;
static int hot_button = 0;
class Game
{
	Player player;
	int lv;
	int score;
	//int time;
	std::vector<Threat*> threat;
	//vector<Row*> row;
public:
	Game() 
	{
		player = Player();
		lv = 1;
		score = 0;
	};
	~Game()
	{
		for (auto x : threat)
			delete x;
		threat.clear();
	}
	Player getPlayer();
	int getLv();
	int getScore();
	void setScore();
	void ScoreChange();
	vector<Threat*> getThreat();
	void startGame();
	void mainBoard();
	virtual void simulate_game(Input* input, float dt);
	bool menu_game(Input* input);
	void reset_game();
	bool next_level();
	bool quit(Input* input);
	void threatMove(float dt);
	void updatePosThreat();
	bool exitGame(thread&t1);
	void pauseGame(HANDLE hd);
	void resumeGame(HANDLE hd);
};

