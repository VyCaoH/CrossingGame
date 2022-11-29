#pragma comment(lib,"winmm.lib")
#include <iostream>
#include <Windows.h>
#include "MMSystem.h"

using namespace std;
class Sound {
public:
	static bool audioMenu();
	static bool audioUpScore();
	static bool audioButton();
	static bool audioDie();
	static void audioStop();
	static bool audioEnter();
	static bool audioGamePlay();

};
