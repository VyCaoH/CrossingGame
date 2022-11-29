#include "Game.h"
//dp: derivative of position: Van toc
//ddp:  derivative of derivative of positon: Gia toc
float arena_half_size_x = 85, arena_half_size_y = 45;

int Game::getLv()
{
	return lv;
}

//int Game::getScore()
//{
//	return score;
//}
//void Game::setScore()
//{
//
//	if (lv > 1)
//		score = (lv - 1) * 100;
//}
//void Game::scoreChange()
//{
//	setScore();
//	Renderer::draw_number(score, 78, 31, 1.3, 0xFF3131);
//}

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
}

void Game::setHighScore()
{
	score.writeHighScore();
}
void Game::simulate_game(Input* input, float dt)
{
	render_state = getRender();
	Renderer::	clear_screen(0xffffffff);

	float speed = 25.f;

	Renderer::draw_Background(0, 0, 73, 45);
	//Renderer::draw_turtleL(0, 0, 1, 1);
	player.move(input, dt, speed);
	player.checkWall(0, 0, arena_half_size_x, arena_half_size_y);
	player.isImpact(threat);
	Renderer::draw_trees(0, 0);
	updatePosThreat();
	threatMove(dt);
	score.DisplayScore();
	score.DisplayHighScore();
	next_level();


	if (pressed(BUTTON_W)) player.up(speed, dt);
	if (is_down(BUTTON_S)) player.down(speed, dt);
	if (is_down(BUTTON_D)) player.right(speed, dt);
	if (is_down(BUTTON_A)) player.left(speed, dt);
}
bool Game::menu_game(Input* input) {
	render_state = getRender();
	if (released(BUTTON_UP))
	{
		g_music_menu = !g_music_menu;
		if (g_music_menu)
			Sound::audioMenu();
		else
			Sound::audioStop();
	}
	if (pressed(BUTTON_S))
	{
		g_music_button = !g_music_button;
		if (g_music_button)
		{
			Sound::audioButton();
		}
		g_music_button = !g_music_button;
		hot_button++;
		if (hot_button > 4)hot_button = 4;
	}
	if (pressed(BUTTON_W)) {
		g_music_button = !g_music_button;
		if (g_music_button)
		{
			Sound::audioButton();
		}
		g_music_button = !g_music_button;
		hot_button--;
		if (hot_button < 0)hot_button = 0;

	}
	/*Do something in menu*/;
	Renderer::draw_Menu(0, 0, 50, 50, hot_button);
	if (pressed(BUTTON_ENTER))
	{
		switch (hot_button)
		{
		case 0:	//NEW GAME
			return false;
		case 1:		//LOAD GAME
			break;
		case 2: //SETTINGS
			break;
		case 3:
			//draw_Menu_Introduction(0, 0, 50, 50);
			break;

		}//==hot_button;
	}
	return true;
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
		score.setScore(lv);
		reset_game();
	}
	return false;
}
int Game::overGame(Input* input)
{
	Renderer::draw_rect(0, 0, 20, 10, 0xFFFA);
	if (pressed(BUTTON_Y))	//restart game
		return 1;
	if (pressed(BUTTON_ESC))
		return -1;
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
		x->setListEntity((TYPE)randomType,randomDir);
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
