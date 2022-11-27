#include"ConsoleWindow.h"
#include"Game.h"
#include<thread>
Input MOVING;
Game game;
void subThread(HWND window)
{
	HDC hdc = GetDC(window);
	while (g_running)
	{
		game.simulate_game(&MOVING, 0.016f);
		render_state = getRender();
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}
int main()
{
//	game.startGame();

	HWND window = winMain();
	//HDC hdc = GetDC(window);
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


	thread t1(subThread,window);
	while (g_running) {
		MSG message;
		messageInput(input, message, window);

		if (g_pause == true)
		{
			game.pauseGame(t1.native_handle());
		}
		if (!game.getPlayer().getIsDead())
		{
			if (input.buttons[BUTTON_ESC].is_down )//&& input.buttons[BUTTON_ESC].changed)
			{
				game.exitGame(t1.native_handle());
			}
			else if (input.buttons[BUTTON_P].is_down )//&& !input.buttons[BUTTON_P].changed)
			{
				g_pause = true;
				game.pauseGame(t1.native_handle());
			}
			else
			{
				if (input.buttons[BUTTON_Y].is_down)
				{
					g_pause = false;
					game.resumeGame((HANDLE)t1.native_handle());
				}
				MOVING = input;;
			}
		}
		else
		{
			if (input.buttons[BUTTON_Y].is_down)
			{
				game.startGame();
			}
			else
			{
				game.exitGame(t1.native_handle());
				return 0;
			}
		}
		//Thoi gian Frame end
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);

		//FPS ( time theo CPU ),
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}

	return 0;
}