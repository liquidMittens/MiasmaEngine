// main 
#include "app/GameApp.h"

int main(int argc, char** argv)
{
	// create and execute out window loop
	GameApp game;
	game.InitializeGameApp();
	game.RunGameAppLoop();
	game.ShutdownGameApp();
	return 0;
}