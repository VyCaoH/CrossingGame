#include"ConsoleWindow.h"
#include"Game.h"
#include<thread>
char MOVING;
Game game;

void subThread(HWND window)
{
	HDC hdc = GetDC(window);
	float delta_time=0.1f;

	while (g_running)
	{
		//input = input;
		if (g_mode==GM_MENUGAME)
		{
			continue;
		}
		if (!game.getPlayer().getIsDead())
		{
			game.simulate_game(MOVING, delta_time);
		//MOVING = ' ';
		}
		else
			continue;
		render_state = getRender();
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
		cout << MOVING << endl;

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

	Input input = {};
	thread t1(subThread, window);
	while (g_running) {

		MSG message;
		MOVING=messageInput(input, message, window);

		//if (MOVING == 'W')
			//cout << 1 << endl;
		if (g_mode==GM_MENUGAME)
		{
			switch (game.menu_game(&input))
			{
			case NEW_GAME:
				g_pause = false;
				g_mode = GM_PLAYGAME;
				game.restartGame();
				game.resumeGame(t1.native_handle());
				break;
			case LOAD_GAME:
				g_pause = false;
				g_mode = GM_PLAYGAME;
				game.resumeGame(t1.native_handle());
				break;
			case SETTINGS:
				break;
			case INTRODUCTION:
				break;
			case EXIT:
				g_running = false;
			default:
			{}
			}
			render_state = getRender();
			StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
		}
		else
		{
			if (!game.getPlayer().getIsDead())
			{
				if (!g_pause)
				{
					if (input.buttons[BUTTON_ESC].is_down)
					{
						g_running = false;
					}
					else if (input.buttons[BUTTON_P].is_down)
					{
						g_pause = true;
						game.pauseGame(t1.native_handle());
						continue;
					}
					if (input.buttons[BUTTON_Y].is_down)
					{
						game.resumeGame((HANDLE)t1.native_handle());
						continue;
					}
				}
				else
				{
					g_mode = GM_MENUGAME;
					continue;
					if (input.buttons[BUTTON_ESC].is_down)
					{
						g_running = false;
						game.resumeGame((HANDLE)t1.native_handle());
					}
					if (input.buttons[BUTTON_Y].is_down)
					{
						g_pause = false;
						game.resumeGame((HANDLE)t1.native_handle());
					}
				}
				MOVING;
			}
			else
			{
				if(g_pause)
					game.pauseGame(t1.native_handle());
				StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				if (game.overGame(&input) == 1)
				{
					g_pause = false;
					game.restartGame();
					game.resumeGame((HANDLE)t1.native_handle());
				}
				else if(game.overGame(&input) == -1)
				{
					//g_pause = false;
					g_running = false;
					game.resumeGame((HANDLE)t1.native_handle());
				}
			}
		}
		if (input.buttons[BUTTON_ESC].is_down)
		{
			g_running = false;
			game.resumeGame((HANDLE)t1.native_handle());
		}
		//Thoi gian Frame end
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);

		//FPS ( time theo CPU ),
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		cout <<"Delta time = "<< delta_time << endl;
		Sleep(25);
		frame_begin_time = frame_end_time;
	}
	game.exitGame(t1);
	return 0;
}