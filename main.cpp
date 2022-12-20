#include"ConsoleWindow.h"
#include"Game.h"
#include<thread>
Input MOVING;
Game game;

void subThread(HWND window)
{
	HDC hdc = GetDC(window);

	float delta_time = .2f;
	while (g_running)
	{

		if (game.menu.isRunning())
		{
			continue;
		}
		if (!game.getPlayer().getIsDead())
		{
			if (!g_save && !g_pause)
				game.simulate_game(&MOVING, delta_time);
		}
		else
			continue;
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


	thread t1(subThread, window);
	game.pauseGame(t1.native_handle());
	while (g_running) {

		MSG message;
		char key = messageInput(MOVING, message, window);
		if (game.menu.isRunning())
		{
				game.simulate_menu(&MOVING);
				switch(game.menu.getMenuMode())
				{case NEW_GAME:
				{
					g_pause = false;
					game.restartGame();
					game.resumeGame(t1.native_handle());
				}break;
				case LOAD_GAME:
				{
					g_pause = false;
					game.resumeGame(t1.native_handle());
				}break;
				default:;
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
					if (MOVING.buttons[BUTTON_ESC].is_down)
					{
						g_running = false;
					}
					else if (MOVING.buttons[BUTTON_P].is_down)
					{
						MOVING.buttons[BUTTON_P].is_down = false;
						g_pause = true;
						game.pauseGame(t1.native_handle());
						continue;
					}
					else if (MOVING.buttons[BUTTON_Y].is_down)
					{
						MOVING.buttons[BUTTON_Y].is_down = false;
						game.resumeGame((HANDLE)t1.native_handle());
						continue;
					}
					else if (MOVING.buttons[BUTTON_T].is_down)
					{
						MOVING.buttons[BUTTON_T].is_down = false;
						g_pause = g_save = true;
						continue;
					}
				}
				else
				{
					if (g_save && g_pause)
					{
						if (game.saveGame(&MOVING))
						{
							g_save = g_pause = false;
							MOVING.buttons[BUTTON_T].is_down = false;
							game.menu.setMenuMode(MAIN);
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
			}
			else
			{
				if(g_pause)
					game.pauseGame(t1.native_handle());
				StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

				if (game.overGame(&MOVING) == 1)
				{
					g_pause = false;
					g_running = true;
					game.restartGame();
					game.resumeGame((HANDLE)t1.native_handle());
				}
				else if(game.overGame(&MOVING) == -1)
				{
					g_running = false;
					game.resumeGame((HANDLE)t1.native_handle());
				}
				else
				{
					//GAME OVER
				}

			}

		}
		if (MOVING.buttons[BUTTON_ESC].is_down)
		{
			g_running = false;
			game.resumeGame((HANDLE)t1.native_handle());
		}
		//Thoi gian Frame end
		Sleep(20);
	}
	exit_game:
	game.exitGame(t1);
	return 0;
}