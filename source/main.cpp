// main 
#include <Miasma/core/app/Engine.h>

int main(int argc, char** argv)
{
	// create and execute out window loop
	Engine game;
	game.InitializeGameEngine();
	game.RunEngineLoop();
	game.ShutdownEngine();
	return 0;
}