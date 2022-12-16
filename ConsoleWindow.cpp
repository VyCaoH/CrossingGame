#pragma once
#include "ConsoleWindow.h"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		int size = render_state.width * render_state.height * sizeof(unsigned int);

		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
		render_state.bitmap_info.bmiHeader.biPlanes = 1;
		render_state.bitmap_info.bmiHeader.biBitCount = 32;
		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;

	} break;

	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}

HWND winMain() {
	HINSTANCE hInstance = nullptr; HINSTANCE hPrevInstance = nullptr; LPSTR lpCmdLine = nullptr; int nShowCmd = 0;
	ShowCursor(FALSE);

	// Create Window Class
	const WCHAR className[] = L"Crossing Game";
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = className;
	window_class.lpfnWndProc = window_callback;
	window_class.lpfnWndProc = window_callback;

	// Register Class
	RegisterClass(&window_class);

	// Create Window
	HWND window = CreateWindowEx(0, className, L"CrossingGame", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	//{
	//	//Fullscreen
	//	SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
	//	MONITORINFO mi = { sizeof(mi) };
	//	GetMonitorInfo(MonitorFromWindow(window, MONITOR_DEFAULTTOPRIMARY), &mi);
	//	SetWindowPos(window, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	//}
	return window;
}
char messageInput(Input&input,MSG &message,HWND &window)
{
	for (int i = 0; i < BUTTON_COUNT; i++) {
		input.buttons[i].changed = false;
	}

	while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

		switch (message.message) {
		case WM_KEYUP:
		{
			u32 vk_code = (u32)message.wParam;
			if ('A' <= vk_code	&& vk_code <= 'Z' 
				&& vk_code != 'A'
				&& vk_code != 'S'
				&& vk_code != 'D'
				&& vk_code != 'W'
				&& vk_code != 'Y'
				&& vk_code != 'P')
			{
				return (char)vk_code;
				break;
			}
		}
		case WM_KEYDOWN: {
			u32 vk_code = (u32)message.wParam;
			bool is_down = ((message.lParam & (1 << 31)) == 0);

			//Ham xu li chung ( genenal function ): xu li phim nhan
#define process_button(b, vk)\
case vk: {\
input.buttons[b].changed = is_down!=input.buttons[b].is_down;\
input.buttons[b].is_down = is_down;\
} break;

					//Xu li phim nhan

			switch (vk_code) {
				process_button(BUTTON_UP, VK_UP);
				process_button(BUTTON_DOWN, VK_DOWN);
				process_button(BUTTON_W, 'W');
				process_button(BUTTON_S, 'S');
				process_button(BUTTON_A, 'A');
				process_button(BUTTON_D, 'D');

				process_button(BUTTON_Y, 'Y');
				process_button(BUTTON_P, 'P');
				process_button(BUTTON_B, 'B');
				process_button(BUTTON_L, 'L');
				process_button(BUTTON_ESC, 27);
				process_button(BUTTON_ENTER,VK_RETURN)
				process_button(BUTTON_LEFT, VK_LEFT);
				process_button(BUTTON_RIGHT, VK_RIGHT);
				//process_button(BUTTON_ENTER, VK_RETURN);
			}
			return (char)vk_code;
		} break;
		default: {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		}
	}
	return 0;
}
Render_State getRender()
{
	return render_state;
}
