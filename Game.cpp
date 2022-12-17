#include "Game.h"
//dp: derivative of position: Van toc
//ddp:  derivative of derivative of positon: Gia toc
float arena_half_size_x = 85, arena_half_size_y = 45;

int Game::getLv()
{
	return lv;
}

vector<Threat*> Game::getThreat()
{
	return threat;
}
Player Game::getPlayer()
{
	return player;
}
void Game::startGame()
{
	player = Player();
	threat.clear();
	lv = 1;
	score.readHighScore();
	//menu.setMenuMode(NEW_GAME);
}

void Game::setHighScore()
{
	score.writeHighScore();
}
void Game::simulate_menu(Input* input)
{
	menu.loadMenuGame(input);
}
void Game::simulate_game(Input* input, float dt)
{
	render_state = getRender();

	//Renderer::	clear_screen(0xffffffff);

	float speed = 5.f;




	Renderer::draw_Background(0, 0, 73, 45);
	//Renderer::draw_turtleL(0, 0, 1, 1);
	player.move(input, dt, speed);
	player.checkWall(-28.5, 0, 71.5, 45);
	player.isImpact(threat);
	Renderer::draw_trees(0, 0);
	updatePosThreat();
	threatMove(dt);
	score.DisplayScore();
	score.DisplayHighScore();
	next_level();

}



void Game::loadGame(Input* input)
{
	deque<string> listName;
	deque<int> listLevel;

	//Get data
	fstream fin("SaveGame.txt", std::ios::in);
	string name;
	int lvl;
	while (fin.eof() == false)
	{
		fin >> lvl;
		fin.ignore(80, ' ');
		for (int i = 4; i < 40; i++)
			if (pressed(i))
				name += (char)(i + 61);
		if (pressed(BUTTON_ENTER))
		{
			listName.push_back(name);
			listLevel.push_back(lvl);
		}
		
	}
	listName.pop_back();
	listLevel.pop_back();
	fin.close();

	//Update the number of data in the file
	int n = listName.size();
	if (n > 10)
	{
		for (int i = 0; i < n - 10; i++)
		{
			listName.erase(listName.begin());
			listLevel.erase(listLevel.begin());
		}
		n = listName.size();
		std::fstream output("SaveGame.txt", std::ios::out);
		for (int i = 0; i < n; i++)
			output << listLevel[i] << " " << listName[i] << std::endl;
		output.close();
	}

	/*game.drawLoadMenu()
	for (int i = 0; i < n; i++)
	{
		gameScene.setStrToBuffer(38, 11 + i, listName[i]);
		gameScene.setStrToBuffer(52, 11 + i, "level: " + std::to_string(listLevel[i]));
	}
	gameScene.PrintBuffer();

	GotoXY(55, 22); getline(std::cin, name);
	gameScene.clearPrevBuffer();
	gameScene.PrintBuffer();*/

	for (int i = 0; i < n; i++)
		if (name == listName[i])
		{
			lv = listLevel[i];
			reset_game();
			startGame();
		}
}

void saveGame()
{
}

void Game::saveGame(Input*input)
{
	Renderer::draw_rect(0, 0, 20, 10, 0x0000FF);
	Renderer::draw_text(name.c_str(), -15, 0, 0.3f, 0xFFFFFF);
	for (int i = 4; i < 40; i++)
		if (pressed(i))
			name += (char)(i + 61);

	if (pressed(BUTTON_ENTER)) {
		fstream out("SaveGame.txt", std::ios::app);
		out << lv << " " << name << " " << playerScore << endl;
		out.close();
	}
}
void Game::reset_game()
{
	player.setY(-45);
	threat.clear();
}
void Game::restartGame()
{
	startGame();
}
bool Game::next_level()
{
	//Bien tren Y
	if (player.getY() == 40)
	{
		lv++;
		Sound::audioUpScore();
		score.setScore(lv);
		reset_game();
	}
	return false;
}
int Game::overGame(Input* input)
{
	//if (is_down(BUTTON_Y))
	//	return 1;
	//if (pressed(BUTTON_ESC))
	//	return -1;
	return 0;
}
bool Game::quit(Input* input)
{
	if (is_down(BUTTON_ESC))
		return false;
	return true;
}

void Game::threatMove(float dt)
{
	for (auto x : threat)
	{

		x->move(0.5,dt);

	}
	return;
}
void Game::updatePosThreat()
{
	if (threat.empty())
	{
		threat.push_back(new Threat(-28));
		threat.push_back(new Threat(-13));
		threat.push_back(new Threat(13));
		threat.push_back(new Threat(28));
	}
	for (auto x : threat)
	{
		x->setThreatInRow(lv);
		int randomDir = 0 + rand() % 2;
		int randomType;
		if (lv == 1)
		{
			while (true)
			{
				randomType = 0 + rand() % 8;
				if (randomType % 2 == randomDir)
				{
					break;
				}
			}
		}
		if (lv == 2)
		{
			while (true)
			{
				randomType = 8 + rand() % 10;
				if (randomType % 2 == randomDir)
				{
					break;
				}
			}
		}
		if (lv > 2)
		{
			while (true)
			{
				randomType = 0 + rand() % 18;
				if (randomType % 2 == randomDir)
				{
					break;
				}
			}
		}
		x->setListEntity((TYPE)randomType, randomDir);
	}
	// draw traffic light 
}

bool Game::exitGame(thread& t1)
{
	t1.join();
	return true;
}

void Game::pauseGame(HANDLE hd)
{
	//g_pause = true;
	SuspendThread(hd);
}

void Game::resumeGame(HANDLE hd)
{
	//g_pause = false;
	ResumeThread(hd);
}