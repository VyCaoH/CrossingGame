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

bool Game::saveGame(Input*input)
{
	Renderer::draw_rect(0, 0, 20, 10, 0x0000FF);
	Renderer::draw_text(name.c_str(), -15, 0, 0.3f, 0xFFFFFF);
	for (int i = 4; i < 40; i++)
		if (pressed(i))
			name += (char)(i + 61);

	if (pressed(BUTTON_ENTER)) {
		string load = name.erase(0,12) + ".txt";
		fstream file(load, ios::out);
		file << lights.getState() << " " << lights.getTime() << " " << lv << " " << playerScore << " "
			<< player.getX() << " " << player.getY() << " "
			<< player.getIsDead() << " " << player.getDP() << " ";
		file << curVH << " ";
		for (unsigned int i = 0; i < curVH; i++)
		{
			file << truck[i].getX() << " " << truck[i].getY() << " " << truck[i].getDP() << " ";
		}
		for (unsigned int i = 0; i < curVH; i++)
		{
			file << car[i].getX() << " " << car[i].getY() << " " << car[i].getDP() << " ";
		}
		file << curAN << " ";
		for (unsigned int i = 0; i < curAN; i++)
		{
			file << bird[i].getX() << " " << bird[i].getY() << " " << bird[i].getDP() << " ";
		}
		for (unsigned int i = 0; i < curAN; i++)
		{
			file << dino[i].getX() << " " << dino[i].getY() << " " << dino[i].getDP() << " ";
		}
		name = "YOUR NAME IS ";
		file.close();
		return true;
	}
	return false;
}

void Game::loadGame(char key)
{
	system("cls");
	string name;
	Renderer::draw_text("INPUT NAME ", 5, 5, 5, 0xFF3333);
	cin >> name;
	//system("cls");
	string load = name + ".txt";
	fstream file(load, ios::in);
	short x, y, s, t;
	file >> x;
	file >> y;
	lights =  TrafficLight();
	file >> lv;
	file >> playerScore;
	file >> x;
	file >> y;
	file >> s;
	player = Player();
	file >> curVH;
	truck = new Truck[curVH]();
	for (unsigned int i = 0; i < curVH; i++)
	{
		file >> x;
		file >> y;
		file >> s;
		truck[i].setX(x);
		truck[i].setY(y);
		truck[i].setDP(s);
	}
	car = new Car[curVH]();
	for (unsigned int i = 0; i < curVH; i++)
	{
		file >> x;
		file >> y;
		file >> s;
		car[i].setX(x);
		car[i].setY(y);
		car[i].setDP(s);
	}
	file >> curAN;
	bird = new Bird[curAN]();
	for (unsigned int i = 0; i < curAN; i++)
	{
		file >> x;
		file >> y;
		file >> s;
		bird[i].setX(x);
		bird[i].setY(y);
		bird[i].setDP(s);
	}
	dino = new Dinosaur[curAN]();
	for (unsigned int i = 0; i < curAN; i++)
	{
		file >> x;
		file >> y;
		file >> s;
		dino[i].setX(x);
		dino[i].setY(y);
		dino[i].setDP(s);
	}
	file.close();
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

		x->move(0.5,0.5*lv*dt);

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