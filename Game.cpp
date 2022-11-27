#include "Game.h"

//#define is_down(b) input->buttons[b].is_down
//#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
//#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)
//dp: derivative of position: Van toc
//ddp:  derivative of derivative of positon: Gia toc
float arena_half_size_x = 85, arena_half_size_y = 45;
static gamemode g_mode = GM_MENUGAME;//=GM_PLAYGAME;//; = gamemode::GM_MENUGAME;
static int hot_button = 0;


int Game::getLv()
{
	return lv;
}

int Game::getScore()
{
	return score;
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
	score = 0;
}

void Game::mainBoard()
{

}

void Game::simulate_game(Input* input, float dt)
{
	render_state = getRender();
	clear_screen(0xffffffff);
	float speed = 50.f;
	//draw_Background(0, 0, 73, 45);
	//draw_rect(0, 0, 6.f, 4.f,0xdddd);
	//draw_turtleL(0, 0, 1, 1);
	player.move(*&input, dt, speed);
	player.checkWall(0, 0, arena_half_size_x, arena_half_size_y);
	player.isImpact(threat);
	g_running = !player.getIsDead();
	g_running = false;
	updatePosThreat();
	threatMove(dt);
	next_level();
	// 
	// 
	//draw_entities(CAR2_RIGHT, 0, 0, 0.5,0xfffff);
}
void Game::menu_game(Input* input) {
	if (is_down(BUTTON_S))// || pressed(BUTTON_W))
	{
		hot_button++;
		if (hot_button > 4)hot_button = 4;
	}
	if (is_down(BUTTON_W)) {
		hot_button--;
		if (hot_button < 0)hot_button = 0;
	}
	/*Do something in menu*/;
	draw_Menu(0, 0, 50, 50, hot_button);
	//draw_entities(BUS_RI, 0, 0, 0.5,0xfffff);

}
void Game::reset_game()
{
	player = Player();
	threat.clear();
}
bool Game::next_level()
{
	//Bien tren Y
	if (player.getY() == 40)
	{
		lv++;
		reset_game();
	}
	return false;
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
		x->move(dt,2* lv);
	}
	return;
}
void Game::updatePosThreat()
{
	if (threat.empty())
	{
		threat.push_back(new Threat(-30));
		threat.push_back(new Threat(-10));
		threat.push_back(new Threat(10));
		threat.push_back(new Threat(30));
	}
	for (auto x : threat)
	{
		//int randomType = 3;
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
				randomType = 8 + rand() % 4;
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
				randomType = 0 + rand() % 11;
				if (randomType % 2 == randomDir)
				{
					break;
				}
			}
		}

		x->setListEntity((TYPE)randomType,randomDir);
	//x->setListEntity(TURTLE_LEFT, 1);
	}
}

bool Game::exitGame(thread &t1)
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
