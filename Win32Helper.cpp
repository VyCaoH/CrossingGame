#include "Win32Helper.h"

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(SHORT x, SHORT y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetTextColor(SHORT color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GetWindowBufferSize(SHORT& row, SHORT& col)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void ShowConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void ClearConsoleScreen()
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	std::cout.flush();

	if (!GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(hOut, topLeft);
}

void ResizeWindow()
{
	HWND console = GetConsoleWindow();
	RECT r;

	GetWindowRect(console, &r);

	CONSOLE_FONT_INFO font;
	GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 0, &font);

	MoveWindow(console, r.left, r.top, font.dwFontSize.X * 150, (font.dwFontSize.Y + 2) * 30, TRUE);
}

void setConsoleFontSize()
{
	CONSOLE_FONT_INFO OrigFont;
	GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 0, &OrigFont);

	PCONSOLE_FONT_INFOEX NewFont = new CONSOLE_FONT_INFOEX();

	COORD FontSize = { 9, 18 };

	NewFont->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	NewFont->nFont = OrigFont.nFont; // apparently this is Lucida Console (no consts are provided [3])
	NewFont->dwFontSize = FontSize;
	NewFont->FontWeight = FW_NORMAL; // = 400, but should use predefined consts
	NewFont->FontFamily = FF_DONTCARE; // FF_ROMAN didn't work for me

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, NewFont);

	delete NewFont;
}

void SetConsoleColor(unsigned char color)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	SetConsoleTextAttribute(hOut, color);
}

