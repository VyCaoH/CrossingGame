#pragma once
#include<Thread>
#include <deque>
#include"Player.h"
#include"Animal.h"
#include"Threat.h"
#include"ConsoleWindow.h"
#include"MenuGame.h"
#include"Score.h"
static string name="YOUR NAME IS ";
static bool g_running = true;
static bool g_pause=true;
static bool g_save = false;
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

