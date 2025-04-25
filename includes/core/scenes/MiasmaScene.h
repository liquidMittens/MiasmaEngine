#ifndef MIASMASCENE_H_
#define MIASMASCENE_H_
#include "IScene.h"

class MiasmaScene : public IScene
{
public:
	MiasmaScene(SceneCreationInfo* creationInfo);
	~MiasmaScene();

	void EnterScene() override;
	void Update(float dt) override;
	void ExitScene() override;

private:

};

#endif
