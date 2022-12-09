#include "Game.h"

#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)
//dp: derivative of position: Van toc
//ddp:  derivative of derivative of positon: Gia toc
float player_1_p, player_1_dp, player_2_p, player_2_dp;
float arena_half_size_x = 85, arena_half_size_y = 45;
float player_half_size_x = 2.5, player_half_size_y = 12;
float ball_p_x, ball_p_y, ball_dp_x = 130, ball_dp_y, ball_half_size = 1;

int player_1_score, player_2_score;

float player_pos_x = 0.f;
float player_pos_y = 0.f;


void Game::mainBoard()
{
	HWND window = winMain();
	HDC hdc = GetDC(window);
	Input input = {};

	//Time giua 2 Frame
	float delta_time = 0.016666f;

	//Thoi gian Frame begin -> thoi gian Frame end
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

}
//BUTTON Game::menu_game(Input* input) {
//	render_state = getRender();
//	if (released(BUTTON_UP))
//	{
//		g_music_menu = !g_music_menu;
//		if (g_music_menu)
//			Sound::audioMenu();
//		else
//			Sound::audioStop();
//	}
//	if (pressed(BUTTON_S))
//	{
//		g_music_button = !g_music_button;
//		if (g_music_button)
//		{
//			Sound::audioButton();
//		}
//		g_music_button = !g_music_button;
//		hot_button = (BUTTON)(hot_button + 1);
//		if (hot_button > 4)hot_button = EXIT;
//	}
//	if (pressed(BUTTON_W)) {
//		g_music_button = !g_music_button;
//		if (g_music_button)
//		{
//			Sound::audioButton();
//		}
//		g_music_button = !g_music_button;
//		hot_button = (BUTTON)(hot_button - 1);
//		if (hot_button < 0)hot_button = NEW_GAME;
//	}
//	/*Do something in menu*/;
//	Renderer::draw_Menu(0, 0, 50, 50, hot_button);
//	if (pressed(BUTTON_ENTER))
//	{
//		
//		switch (hot_button)
//		{
//		case NEW_GAME:	//NEW GAME
//			return hot_button;
//
//		case LOAD_GAME:		//LOAD GAME
//			return hot_button;
//
//		case SETTINGS: //SETTINGS
//			return hot_button;
//
//		case INTRODUCTION:
//			//Draw Introduction in here.
//
//			return hot_button;
//		case EXIT:
//			return hot_button;
//		}
//	}
//	return BUTTON( - 1);
//}
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
		/*player.setDDP(player.getDDP() - 2000);
		player.setDP((player.getDP() + (player.getDDP() * dt)));
		player.setX(player.getX() + player.getDP() * dt + player.getDDP() * dt * dt*.5f);*/
		player.left(speed, dt);
	}
	if (is_down(BUTTON_D))
	{
		/*player.setDDP(player.getDDP() + 2000);
		player.setDP((player.getDP() + (player.getDDP() * dt)));
		player.setX(player.getX() + player.getDP() * dt + player.getDDP() * dt * dt * .5f);*/
		player.right(speed, dt);
	}
	checkWall_player(player);
	
	draw_truck(player.getX(), player.getY(), player.getHalfX(), player.getHalfY());
	//draw_dino(player.getX(), player.getY() + 40, 1, 10);
	return;
	//draw_rect(player.getX(), player.getY()+40, 1, 10, 0x00ff22);
	//draw_rect(player.getX(), player.getY(), 1.4, 3, 0x00ff22);
	//draw_rect(player.getX(), player.getY()-40, 1, 10, 0x00ff22);
	//draw_rect(player.getX(), player.getY()-25, 10, 5, 0x1820FF);
	//draw_rect(player.getX(), player.getY()-25, 1, 1, 0xaaaaaa);
	//draw_rect(player.getX(), player.getY()-25, 1, 1, 0xbbbbbb);
	//draw_rect(player.getX(), player.getY()-28, 1, 1, 0xbbbbbb);
}
//void Game::birdMove( float dt, float speed,int lv)
//{
//	if (!bird.Right())
//		bird.left(speed, dt,lv);
//	if (bird.Right())
//		bird.right(speed, dt);
//	draw_rect(bird.getX(), 20, 1, 1, 0x00ff22);
//}

void Game::threatMove(float dt, float speed)
{
	for (auto x : threat)
	{
		x->move(dt, speed);
	}
	return;
}
void Game::updatePosThreat()
{
	if (threat.empty())
	{
		threat.push_back(new Threat(-20));
		threat.push_back(new Threat(-5));
		threat.push_back(new Threat(10));
		threat.push_back(new Threat(25));
	}
	for (auto x : threat)
	{
		//int randomType = 3;
		int randomType = 0 + rand() % (10 + 1)%4;
		
		x->setListEntity(randomType);
	}
}

