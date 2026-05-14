#ifndef MAINSCENE_H_
#define MAINSCENE_H_

#include <Miasma/core/scenes/IScene.h>

class MainScene : public IScene
{
public:

	MainScene(SceneCreationInfo* creationInfo);
	~MainScene();

	void EnterScene(Engine* eng) override;
	void Update(float dt) override;
	void ExitScene() override;

private:

};

#endif
