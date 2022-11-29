#include"ConsoleWindow.h"
#include"Game.h"
#include<thread>
Input MOVING = {};
Game game;

void subThread(HWND window)
{
	HDC hdc = GetDC(window);
	while (g_running)
	{
		//MOVING = input;
		if (!game.getPlayer().getIsDead())
		{
			g_pause = true;
			game.simulate_game(&MOVING, 0.016f);
			g_pause = false;
		}
		else
			g_running = false;
		//game.menu_game(&MOVING);
		render_state = getRender();
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
	game.setHighScore();
}
int main()
{
//	game.startGame();

	HWND window = winMain();
	HDC hdc = GetDC(window);
	//Input input = {};

	//Time giua 2 Frame
	float delta_time = 50.f;

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
	thread t1(subThread, window);
	game.pauseGame(t1.native_handle());
	while (g_running) {

		MSG message;
		messageInput(MOVING, message, window);

		if (g_menu)
		{
			render_state = getRender();
			StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

			g_pause = g_menu = game.menu_game(&MOVING);
			if (!g_pause)
				game.resumeGame(t1.native_handle());
		}
		else
		{
			if (!game.getPlayer().getIsDead())
			{
				if (!g_pause)
				{

					if (MOVING.buttons[BUTTON_ESC].is_down)
					{
						//Code cua sub_Menu

						//break;
						g_running = false;
						//game.exitGame(t1);
					}
					else if (MOVING.buttons[BUTTON_P].is_down)
					{
						g_pause = true;
						game.pauseGame(t1.native_handle());
					}
					if (MOVING.buttons[BUTTON_Y].is_down)
					{
						//g_pause = false;
						game.resumeGame((HANDLE)t1.native_handle());
					}
				}
				else
				{
					if (MOVING.buttons[BUTTON_ESC].is_down)
					{
						g_running = false;
						game.resumeGame((HANDLE)t1.native_handle());
					}
					if (MOVING.buttons[BUTTON_Y].is_down)
					{
						g_pause = false;
						game.resumeGame((HANDLE)t1.native_handle());
					}
				}
			}
			else {}
		}
		//Thoi gian Frame end
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);

		//FPS ( time theo CPU ),
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}
	game.exitGame(t1);
	return 0;
}