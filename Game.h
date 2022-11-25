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
static bool g_pause = false;

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
	}
	Player getPlayer();
	int getLv();
	int getScore();
	vector<Threat*> getThreat();
	void startGame();
	void getInput(Input* input);
	void mainBoard();
	virtual void simulate_game(Input* input, float dt);
	void reset_game();
	bool next_level();
	bool quit(Input* input);
	void checkWall_player(Player &player);
	void playerMove(Input* input, float dt, float speed);
	void threatMove(float dt);
	void updatePosThreat();
	void exitGame(HANDLE hd);
	void pauseGame(HANDLE hd);
	void resumeGame(HANDLE hd);
};

