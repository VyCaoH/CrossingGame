#include "Game.h"

//dp: derivative of position: Van toc
//ddp:  derivative of derivative of positon: Gia toc
float arena_half_size_x = 85, arena_half_size_y = 45;



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
	//g_running = false;
	updatePosThreat();
	threatMove(dt);
	next_level();

	//if (is_down(BUTTON_W)) player.up(speed, dt);
	//if (is_down(BUTTON_S)) player.down(speed, dt);
	//if (is_down(BUTTON_D)) player.right(speed, dt);
	//if (is_down(BUTTON_A)) player.left(speed, dt);
	//draw_rect(player.getX(), player.getY(), 1, 1, 0xddd);
}
void Game::menu_game(Input* input) {
	render_state = getRender();
	if (pressed(BUTTON_S))// || pressed(BUTTON_W))
	{
		hot_button++;
		if (hot_button > 4)hot_button = 4;
	}
	if (pressed(BUTTON_W)) {
		hot_button--;
		if (hot_button < 0)hot_button = 0;
	}
	/*Do something in menu*/;
	draw_Menu(0, 0, 50, 50, hot_button);
	if (pressed(BUTTON_ENTER))
	{
		switch (hot_button)
		{
		case 0:
			g_menu = !g_menu;
			g_pause = !g_pause;
		}
	}
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
