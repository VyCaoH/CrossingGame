#pragma once
#include <Windows.h>
#include <iostream>

#define FOREGROUND_BLACK			0x0
#define FOREGROUND_BLUE				0x1		
#define FOREGROUND_GREEN			0x2
#define FOREGROUND_AQUA				0x3
#define FOREGROUND_RED				0x4
#define FOREGROUND_PURPLE			0x5 
#define FOREGROUND_YELLOW			0x6
#define FOREGROUND_WHITE			0x7
#define FOREGROUND_GRAY				0x8
#define FOREGROUND_LIGHT_BLUE		0x9 
#define FOREGROUND_LIGHT_GREEN		0xA
#define FOREGROUND_LIGHT_AQUA		0xB
#define FOREGROUND_LIGHT_RED		0xC
#define FOREGROUND_LIGHT_PURPLE		0xD
#define FOREGROUND_LIGHT_YELLOW		0xE
#define FOREGROUND_BRIGHT_WHITE		0xF

#define BACKGROUND_BLACK			0x00
#define BACKGROUND_BLUE				0x10
#define BACKGROUND_GREEN			0x20
#define BACKGROUND_AQUA				0x30
#define BACKGROUND_RED				0x40
#define BACKGROUND_PURPLE			0x50
#define BACKGROUND_YELLOW			0x60
#define BACKGROUND_WHITE			0x70
#define BACKGROUND_GRAY				0x80
#define BACKGROUND_LIGHT_BLUE		0x90
#define BACKGROUND_LIGHT_GREEN		0xA0
#define BACKGROUND_LIGHT_AQUA		0xB0
#define BACKGROUND_LIGHT_RED		0xC0
#define BACKGROUND_LIGHT_PURPLE		0xD0
#define BACKGROUND_LIGHT_YELLOW		0xE0
#define BACKGROUND_BRIGHT_WHITE		0xF0

void FixConsoleWindow();

void GotoXY(SHORT x, SHORT y);

void SetTextColor(SHORT color);

void GetWindowBufferSize(SHORT& row, SHORT& col);

void ShowConsoleCursor(bool showFlag);

void ClearConsoleScreen();

void ResizeWindow();

void setConsoleFontSize();

void SetConsoleColor(unsigned char color);

void noCursorType();

void noScrollbar();

void SetColor(int backgound_color, int text_color);

void DisableSelection();