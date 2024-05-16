#include "DoomScene.h"
#include "GameObject.h"
#include "MeshRenderable.h"
#include "Material.h"
#include "Quad.h"
#include "FPSCameraMovement.h"
#include "RigidBody.h"
#include "physics/PhysicsController.h"
using namespace Miasma::Physics;

static int map[8 * 8] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

DoomScene::DoomScene(SceneCreationInfo* pSceneCreationInfo) : 
	IScene(pSceneCreationInfo)
{

}

DoomScene::~DoomScene()
{

}

void DoomScene::EnterScene()
{
	IScene::EnterScene();

	// turn off gravity in this scene
	PhysicsController::GetInstance().GetPhysicsWorld()->setGravity(reactphysics3d::Vector3(0.0f, 0.0f, 0.0f));

	// attach fps camera movement to the camera
	m_camera->AddComponent<FPSCameraMovement>(m_camera.get(), m_glfwWindow);
	m_camera->AddComponent<RigidBody>(m_camera.get(), rp3d::BodyType::DYNAMIC);
	//m_camera->GetComponent<RigidBody>().GetRigidBody()->setMass(0.0f);

	// load a quad
	MeshRenderableCreateInfo quadMeshInfo;
	quadMeshInfo.filename = "Wall";
	quadMeshInfo.meshName = "Wall";
	quadMeshInfo.preTransform = glm::identity<glm::mat4>();

	Material greyWallMaterial;
	greyWallMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("red"));
	greyWallMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicTexture"));

	std::shared_ptr<GameObject> wallTest = std::make_shared<GameObject>();
	wallTest->tag = "wall";
	wallTest->transform.translate(glm::vec3(0.0f, 0.0f, 0.0f));
	wallTest->AddComponent<MeshRenderable>(wallTest.get(), Quad::vertices, Quad::indices, &quadMeshInfo, greyWallMaterial);

	m_gameObjectsList.push_back(wallTest);
}

void DoomScene::Update(float dt) 
{
	IScene::Update(dt);
}

void DoomScene::ExitScene()
{
	IScene::ExitScene();
}