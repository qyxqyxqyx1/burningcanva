#include <iostream>
#include "Game.h"
using namespace std;
int main()
{
	Game wanna;
	wanna.create_window();
	while (1)
	{
		wanna.game_controll();
	}
}