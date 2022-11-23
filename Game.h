#pragma once
//#include<vector>
#include"ConsoleWindow.h"
//#include"Renderer.h"
#include"Player.h"
#include"Animal.h"
#include"Threat.h"
//#include"Renderer.h"
static bool g_running = true;
static bool g_menu = true;
class Game
{
	Player player;
	std::vector<Threat*> threat;
	//Bird bird;
	//vector<Row*> row;
public:
	Game() 
	{
		player = Player();
		//player = Player("People.txt");
		//bird = Bird("People.txt");
	/*	threat.push_back(new Threat(7));
		threat.push_back(new Threat(13));
		threat.push_back(new Threat(19));
		threat.push_back(new Threat(25));*/
	};
	enum gamemode{ GM_MENUGAME,GM_PLAYGAME};
	void mainBoard();
	virtual void simulate_game(Input* input, float dt);
	bool quit(Input* input);
	void playerMove(Input* input, float dt, float speed);
	void checkWall_player(Player &player);
	//void birdMove(float dt, float speed,int lv);
	void updatePosThreat();
	void playerCollision();
	void threatMove(float dt, float speed);
	//char* vvChar_to_CharPtr(vector<vector<char>> src)
	//{
	//	const int n = src.size();
	//	const int m = src[0].size();
	//}
};

