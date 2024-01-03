#ifndef SANDBOXSCENE_H_
#define SANDBOXSCENE_H_
#include "IScene.h"
#include "components/PointLight.h"
#include "objects/GameObject.h"

class SandboxScene : public IScene
{
	friend class Miasma::UI::GUIBuilder;

public:
	SandboxScene(SceneCreationInfo* creationInfo);
	~SandboxScene();
	/*Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;*/

	void EnterScene() override;
	void Update(float dt) override;
	void ExitScene() override;

private:
};

#endif
