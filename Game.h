#pragma once
//#include<vector>
#include"ConsoleWindow.h"
//#include"Renderer.h"
#include"Player.h"
#include"Animal.h"
#include"Threat.h"
//#include"Renderer.h"
static enum gamemode { GM_MENUGAME, GM_PLAYGAME };
static bool g_running = true;

class Game
{
	Player player;
	int lv;
	int score;
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

	void mainBoard();
	virtual void simulate_game(Input* input, float dt);
	void reset_game();
	bool next_level();
	bool quit(Input* input);
	void playerCollision();
	void playerMove(Input* input, float dt, float speed);
	void checkWall_player(Player &player);
	void threatMove(float dt);
	void updatePosThreat();
};

