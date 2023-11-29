#ifndef GOLDENTRIANGLESCENE_H_
#define GOLDENTRIANGLESCENE_H_
#include "IScene.h"
#include "glm/glm.hpp"
#include "Sprite2D.h"
#include <vector>
constexpr float MaxPlaceTime = 0.0f;

class ChaosGameScene : public IScene
{
public: 
	ChaosGameScene(SceneCreationInfo* creationInfo);
	~ChaosGameScene();
	/*Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;*/

	void EnterScene() override;
	void Update(float dt) override;
	void ExitScene() override;

private:
	glm::vec2 m_cameraBoundsMax;
	float m_currentPlaceTime;
	Material pixelMaterial;
	glm::vec2 currentPosition;
	std::vector<glm::vec2> triangleVertices;
	// pentagon variables
	bool pentagonMode;
	int lastPentagonVertexIndex;

	float sign(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3);
	bool PointInTriangle(glm::vec2 pt, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);
};

#endif
