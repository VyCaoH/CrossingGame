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
	//Menu
}

void Game::getInput(Input* input)
{
	playerMove(input, 0.1f, 50.f);
}

void Game::mainBoard()
{

}

void Game::simulate_game(Input* input, float dt)
{
	render_state = getRender();
	clear_screen(0xffffffff);
	float speed = 50.f;
	playerMove(input, dt, speed);
	player.isImpact(threat);
	g_running = !player.getIsDead();
	//g_running = false;
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
	if (is_down(BUTTON_ENTER))
		return false;
	return true;
}
void Game::checkWall_player(Player &player)
{
	if (player.getX() + player.getHalfX() > arena_half_size_x)
	{
		player.setX(arena_half_size_x - player.getHalfX());
		player.setDP(0);
	}
	if (player.getY() + player.getHalfY() > arena_half_size_y)
	{
		player.setY(arena_half_size_y - player.getHalfY());
		player.setDP(0);
	}
	if (player.getX() - player.getHalfX() < -arena_half_size_x)
	{
		player.setX(-arena_half_size_x + player.getHalfX());
		player.setDP(0);
	}
	if (player.getY() - player.getHalfY() < -arena_half_size_y)
	{
		player.setY(-arena_half_size_y + player.getHalfY());
		player.setDP(0);
	}
}
void Game::playerMove(Input* input, float dt, float speed)
{
	if (is_down(BUTTON_W))
	{
		player.up(speed, dt);
	}
	if (is_down(BUTTON_S))
	{
		player.down(speed, dt);
	}

	if (is_down(BUTTON_A))
	{
		player.left(speed, dt);
	}
	if (is_down(BUTTON_D))
	{
		player.right(speed, dt);
	}
	checkWall_player(player);
	
	draw_titan(player.getX(), player.getY(),player.getHalfX(),player.getHalfY());
	return;
	//draw_dino(player.getX(), player.getY() + 40, 1, 10);
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
		do {
			randomType = 0 + rand() % 10;
			if (randomType % 2 == randomDir)
			{
				if (randomType == 7)
					continue;
				if (randomType == 6)
					continue;
				break;
			}
		}
		while (true);
		x->setListEntity((TYPE)randomType,randomDir);
		//x->setListEntity(CAR2_LEFT, 1);
	}
}

void Game::exitGame(HANDLE hd)
{
	ExitThread((DWORD)hd);
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
