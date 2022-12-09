#pragma once
#include"ConsoleWindow.h"
class MenuGame
{
	BUTTON menuMode;
	BUTTON hotButton;
	bool running;
	void loadSettings(Input* input) {
		render_state = getRender();
		Renderer::draw_Settings(0, 0, 0, 0);
		if (pressed(BUTTON_B)) {
			menuMode = MAIN;
		}
	}
	void loadIntroduction(Input* input) {
		render_state = getRender();
		Renderer::draw_Introduction(0, 0, 0, 0);
		if (pressed(BUTTON_B)) {
			menuMode = MAIN;
		}
	}
public:
	MenuGame() {
		menuMode = (BUTTON)MAIN;
		hotButton = (BUTTON)NEW_GAME;
		running = true;
	}
	bool isRunning() {
		return running;
	}
	BUTTON getMenuMode() {
		return menuMode;
	}
	void setMenuMode(BUTTON newNode) {
		menuMode = newNode;
	}
	void loadMainMenu(Input* input) {
		render_state = getRender();
		if (released(BUTTON_UP))
		{
			/*g_music_menu = !g_music_menu;
			if (g_music_menu)
				Sound::audioMenu();
			else
				Sound::audioStop();*/
		}
		if (pressed(BUTTON_S))
		{
			/*g_music_button = !g_music_button;
			if (g_music_button)
			{
				Sound::audioButton();
			}
			g_music_button = !g_music_button;*/
			hotButton = (BUTTON)(hotButton + 1);
			if (hotButton > 4)hotButton = EXIT;
		}
		if (pressed(BUTTON_W)) {
			/*g_music_button = !g_music_button;
			if (g_music_button)
			{
				Sound::audioButton();
			}
			g_music_button = !g_music_button;*/
			hotButton = (BUTTON)(hotButton - 1);
			if (hotButton < 0)hotButton = NEW_GAME;
		}
		/*Do something in menu*/;
		Renderer::draw_Menu(0, 0, 50, 50, hotButton);
		if (pressed(BUTTON_ENTER))
		{
			menuMode = hotButton;
		}
	}
	void loadMenuGame(Input* input) {
		render_state = getRender();
		switch (menuMode) {
		case MAIN:
			loadMainMenu(input);
			break;
		case NEW_GAME:
			running = false;
			break;
		case LOAD_GAME:
			running = false;
			break;
		case SETTINGS:
			loadSettings(input);
			break;
		case INTRODUCTION:
			loadIntroduction(input);
			break;
		case EXIT:
			break;
		}
	}
};

