#include "model/ChaosGameScene.h"
#include "objects/GameObject.h"
#include <random>

ChaosGameScene::ChaosGameScene(SceneCreationInfo* creationInfo) :
	IScene(creationInfo),
	m_currentPlaceTime(0.0f),
	pentagonMode(true),
	lastPentagonVertexIndex(-1)
{

}

ChaosGameScene::~ChaosGameScene()
{

}

void ChaosGameScene::EnterScene()
{
	IScene::EnterScene();
	pixelMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("circletest"));
	pixelMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));
	float scaler = 300.0f;
	float horzScaler = 500.0f;
	m_cameraBoundsMax = m_camera->GetComponent<Camera>().viewport();
	if (!pentagonMode) {
		triangleVertices.push_back({ (scaler+horzScaler), m_cameraBoundsMax.y-scaler });
		triangleVertices.push_back({ m_cameraBoundsMax.x-(scaler+horzScaler), m_cameraBoundsMax.y-scaler });
		triangleVertices.push_back({ (m_cameraBoundsMax.x) / 2.0f, scaler });
	}
	else {
		triangleVertices.push_back({ 500.0f, 880.0f });
		triangleVertices.push_back({ 1420.0f, 880.0f });
		triangleVertices.push_back({ 500.0f, 500.0f });
		triangleVertices.push_back({ (m_cameraBoundsMax.x) / 2.0f, 100.0f });
		triangleVertices.push_back({ 1420.0f, 500.0f });
	}

	std::shared_ptr<GameObject> test = std::make_shared<GameObject>();
	// choose initial random position 
	std::random_device randDevice;
	std::mt19937 mt(randDevice());
	std::uniform_real_distribution<double> randomizerX(0.0, m_cameraBoundsMax.x);
	std::uniform_real_distribution<double> randomizerY(0.0, m_cameraBoundsMax.y);
	glm::vec2 newPos({ randomizerX(mt), randomizerY(mt) });
	//while (!PointInTriangle(newPos, triangleVertices[0], triangleVertices[1], triangleVertices[2])) {
	newPos.x = randomizerX(mt);
	newPos.y = randomizerY(mt);
	//}
	currentPosition = newPos;
	test->transform.translate({ currentPosition.x, currentPosition.y, 1.0f });
	test->AddComponent<Sprite2D>(test.get(), pixelMaterial);
	m_gameObjectsList.push_back(test);

}
void ChaosGameScene::Update(float dt)
{
	//IScene::Update(dt);
	m_currentPlaceTime += dt;
	if (m_currentPlaceTime >= MaxPlaceTime) {
		m_currentPlaceTime = 0.0f;
		// do the sierpinski triangle loop
		std::random_device randDevice;
		std::mt19937 mt(randDevice());
		int vertIndex = 0;
		glm::vec2 randomVertexPosition;
		if (!pentagonMode) {
			std::uniform_int_distribution<int> vertRandom(0, 2);
			//Randomly select any one of the three vertex points.
			vertIndex = vertRandom(mt);
			randomVertexPosition.x = triangleVertices[vertIndex].x;
			randomVertexPosition.y = triangleVertices[vertIndex].y;
		}
		else {
			std::uniform_int_distribution<int> vertRandom(0, 4);
			//Randomly select any one of the three vertex points.
			// cannot be the same as previous vertex picked
			vertIndex = vertRandom(mt);
			while (vertIndex == lastPentagonVertexIndex) {
				std::uniform_int_distribution<int> vertRandom(0, 4);
				vertIndex = vertRandom(mt);
			}
			randomVertexPosition.x = triangleVertices[vertIndex].x;
			randomVertexPosition.y = triangleVertices[vertIndex].y;
			lastPentagonVertexIndex = vertIndex;
		}
		//Move half the distance from your current position to the selected vertex.
		float xM = (currentPosition.x + randomVertexPosition.x) / 2.0f;
		float yM = (currentPosition.y + randomVertexPosition.y) / 2.0f;
		glm::vec2 halfwayPosition(xM, yM);
		// put a sprite there
		std::shared_ptr<GameObject> newPoint = std::make_shared<GameObject>();
		newPoint->transform.translate({ halfwayPosition.x, halfwayPosition.y, 1.0f });
		newPoint->AddComponent<Sprite2D>(newPoint.get(), pixelMaterial);
		m_gameObjectsList.push_back(newPoint);
		currentPosition = halfwayPosition;
	}
	std::cout << std::format("points: {}\n", m_gameObjectsList.size());
}

void ChaosGameScene::ExitScene()
{
	IScene::ExitScene();
}

float ChaosGameScene::sign(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool ChaosGameScene::PointInTriangle(glm::vec2 pt, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}