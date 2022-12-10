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
		//MOVING = MOVING;
		if (game.menu.isRunning())
		{
			continue;
		}
		if (!game.getPlayer().getIsDead())
		{
			game.simulate_game(&MOVING, delta_time);
		}
		else
			continue;
		//MOVING = ' ';
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
	while (g_running) {

		MSG message;
		char key = messageInput(MOVING, message, window);
		if (game.menu.isRunning())
		{
			if (game.menu.isRunning()) {
				game.menu.loadMenuGame(&MOVING);
				if (game.menu.getMenuMode() == NEW_GAME) {
					g_pause = false;
					game.restartGame();
					game.resumeGame(t1.native_handle());
				}
				else if (game.menu.getMenuMode() == LOAD_GAME) {
					g_pause = false;
					game.resumeGame(t1.native_handle());
				}
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
						g_pause = true;
						game.pauseGame(t1.native_handle());
						continue;
					}
					if (MOVING.buttons[BUTTON_Y].is_down)
					{
						game.resumeGame((HANDLE)t1.native_handle());
						continue;
					}
				}
				else
				{
					game.menu.setMenuMode(MAIN);
					continue;
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
				MOVING;
			}
			else
			{
				if(g_pause)
					game.pauseGame(t1.native_handle());
				StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
				if (game.overGame(&MOVING) == 1)
				{
					g_pause = false;
					game.restartGame();
					game.resumeGame((HANDLE)t1.native_handle());
				}
				else if(game.overGame(&MOVING) == -1)
				{
					//g_pause = false;
					g_running = false;
					game.resumeGame((HANDLE)t1.native_handle());
				}
			}
		}
		if (MOVING.buttons[BUTTON_ESC].is_down)
		{
			g_running = false;
			game.resumeGame((HANDLE)t1.native_handle());
		}
		//Thoi gian Frame end
		Sleep(15);
	}
	game.exitGame(t1);
	return 0;
}