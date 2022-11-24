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
	std::vector<Threat*> threat;
	Bird bird;
	//vector<Row*> row;
public:
	Game() 
	{
		player = Player();
		
	};

	void mainBoard();
	virtual void simulate_game(Input* input, float dt);
	bool quit(Input* input);
	void playerMove(Input* input, float dt, float speed);
	void checkWall_player(Player &player);
	void updatePosThreat();
	void threatMove(float dt, float speed);
};

