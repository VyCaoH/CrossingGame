#pragma once
//#include<vector>
#include"ConsoleWindow.h"
//#include"Renderer.h"
#include"Player.h"
#include"Animal.h"
#include"Threat.h"
#include"Sound.h"
#include"ConsoleWindow.h"
#include"MenuGame.h"
#include"Score.h"
//#include"Renderer.h"
static bool g_running = true;
static bool g_menu = true;
class Game
{
	Player player;
	std::vector<Threat*> threat;
	Bird bird;
	//vector<Row*> row;
public:
	MenuGame menu;
	Game() 
	{
		player = Player();
		menu = MenuGame();
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
	void simulate_game(Input* input, float dt);
	vector<Threat*> getThreat();
	void startGame();
	//BUTTON menu_game(Input* input);
	void reset_game();
	void restartGame();
	bool next_level();
	int overGame(Input* input);
	bool quit(Input* input);
	void playerMove(Input* input, float dt, float speed);
	void checkWall_player(Player &player);
	//void birdMove(float dt, float speed,int lv);
	void updatePosThreat();
	void threatMove(float dt, float speed);
	//char* vvChar_to_CharPtr(vector<vector<char>> src)
	//{
	//	const int n = src.size();
	//	const int m = src[0].size();
	//}
};

