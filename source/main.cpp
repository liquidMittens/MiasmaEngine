// main 
#include "app/GameApp.h"
#include "core/objects/Component.h"
#include "core/objects/Collider.h"
#include "core/objects/BoxCollider.h"
#include "core/objects/MeshRenderable.h"
#include "core/objects/GameObject.h"
using namespace miasma_rtti;

int main(int argc, char** argv)
{
	// create and execute out window loop
	GameApp game;
	game.InitializeGameApp();
	game.RunGameAppLoop();
	game.ShutdownGameApp();
	return 0;
}