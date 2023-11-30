#ifndef MAINSCENE_H_
#define MAINSCENE_H_

#include "IScene.h"

class MainScene : public IScene
{
public:

	MainScene(SceneCreationInfo* creationInfo);
	~MainScene();

	void EnterScene() override;
	void Update(float dt) override;
	void ExitScene() override;

private:

};

#endif
