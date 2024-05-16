#ifndef DOOMSCENE_H_
#define DOOMSCENE_H_
#include "IScene.h"

class DoomScene : public IScene
{
public:
	DoomScene(SceneCreationInfo* creationInfo);
	~DoomScene();

	void EnterScene() override;
	void Update(float dt) override;
	void ExitScene() override;

private: 

};

#endif
