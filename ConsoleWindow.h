#pragma once
#include<Windows.h>
#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)


//#define global_variable static

static bool running = true;


struct Render_State {
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};
static Render_State render_state;

#include"Renderer.h"

struct Button_State {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_W,
	BUTTON_S,
	BUTTON_A,
	BUTTON_D,
	BUTTON_P,
	BUTTON_Y,
	BUTTON_B,
	BUTTON_L,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_ESC,
	BUTTON_ENTER,

	BUTTON_COUNT, // Should be the last item
};
struct Input {
	Button_State buttons[BUTTON_COUNT];
};
LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND winMain();
char messageInput(Input& input,MSG &message, HWND &window);
Render_State getRender();
//LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
////HWND winMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
//WNDCLASS createWindowClass(WNDCLASS window_class);
//void ProcessButton(MSG& message, Input& input);

//public:
//	ConsoleWindow();
//	void setRenderHeight(int);
//	void setRenderWidth(int);
//	void setButton_Changed(bool);
//	void setButton_isDown(bool);
//	bool getButton_Changed()
//	{
//		return button_state.changed;
//	}
//	bool getButton_isDown()
//	{
//		return button_state.is_down;
//	}
//	int getRenderHeight()
//	{
//		return render_state.height;
//	}
//	int getRenderWidth()
//	{
//		return render_state.width;
//	}
//	void* getRenderMemory()
//	{
//		return render_state.memory;
//	}
//	BITMAPINFO getRenderBitmap()
//	{
//		render_state.bitmap_info;
//	}



