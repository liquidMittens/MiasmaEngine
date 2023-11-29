#ifndef SCENE_H_
#define SCENE_H_
#include "IScene.h"
#include "components/PointLight.h"
#include "objects/GameObject.h"

class Scene : public IScene
{
	friend class Miasma::UI::GUIBuilder;

public:
	Scene(SceneCreationInfo* creationInfo);
	~Scene();
	/*Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;*/

	void EnterScene() override;
	void Update(float dt) override;
	void ExitScene() override;

private:
};

#endif
