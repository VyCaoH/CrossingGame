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

	//Tan so hieu suat truy van
	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}
	while (running) {
		// Input
		MSG message;

		messageInput(input, message, window);

		running = quit(&input);

		//Simulate

		simulate_game(&input, delta_time);

		//Render
		render_state = getRender();
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		//Thoi gian Frame end
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);

		//FPS ( time theo CPU ),
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;

	}
}

void Game::simulate_game(Input* input, float dt)
{
	render_state = getRender();
	clear_screen(0xffffffff);
	//draw_rect(0, 0, 100, 50, 0xaaaaaa);
	//draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);
	//left_board
	//draw_rect(-(75.f / 2.f +5.f)+, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);
	draw_arena_borders(0,0,arena_half_size_x, arena_half_size_y, 0xff55ff);
	//draw_truck(0, 0, 5, 5);
	//draw_rect(0, 0, 85, 45, 0xff55ff);
	float speed = 50.f;
	playerMove(input, dt, speed);
	updatePosThreat();
	threatMove(dt, speed);
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
		//player.setDDP(player.getDDP() + 2000);
		//player.setDP((player.getDP() + (player.getDDP() * dt)));
		//player.setY(player.getY() + player.getDP() * dt + player.getDDP() * dt * dt*.5f);
		player.up(speed, dt);
	}
	if (is_down(BUTTON_S))
	{
		//player.setDDP(player.getDDP() - 2000);
		//player.setDP((player.getDP() + (player.getDDP() * dt)));
		//player.setY(player.getY() + player.getDP() * dt + player.getDDP() * dt * dt*.5f);
		player.down(speed, dt);
	}

	if (is_down(BUTTON_A))
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

