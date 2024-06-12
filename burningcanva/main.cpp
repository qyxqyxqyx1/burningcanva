#include <iostream>
#include "Game.h"
#pragma comment(lib,"Winmm.lib")
using namespace std;
int main()
{
	Game wanna;
	wanna.create_window();
	while (1)
	{
		mciSendString(_T("open music.mp3 alias bkmusic"), NULL, 0, NULL);
		mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
		wanna.game_controll();
	}
}