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
static string name;
static enum gamemode { GM_MENUGAME, GM_PLAYGAME };
static bool g_running = true;
static bool g_pause=true;
static gamemode g_mode = GM_MENUGAME;

//static BUTTON hot_button = (BUTTON) NEW_GAME;
class Game
{
	Player player;
	int lv;
	Score score;
	//int time;
	std::vector<Threat*> threat;
	//vector<Row*> row;
	TrafficLight lights;
	Truck *truck;
	Car *car;
	Bird *bird;
	Dinosaur *dino;
	int curVH, curAN;
	
public:
	int playerScore = score.getScore();
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
	void simulate_game(char key, float dt);
	void simulate_menu(Input* input);
	vector<Threat*> getThreat();
	void startGame();
	//BUTTON menu_game(Input* input);
	void reset_game();
	void restartGame();
	bool next_level();
	int overGame(char key);
	bool quit(Input* input);
	void threatMove(float dt);
	void updatePosThreat();
	bool exitGame(thread&t1);
	void pauseGame(HANDLE hd);
	void resumeGame(HANDLE hd);
	void saveGame(char key);
	void loadGame(char key);
};

