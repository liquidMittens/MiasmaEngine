#include "components/PointLight.h"
#include "objects/GameObject.h"
using namespace miasma_rtti;

CLASS_DEFINITION(Component, PointLight);

PointLight::PointLight(GameObject* owner, LightCreationInfo* lightInfo) :
	Component(owner, TO_STRING(PointLight)),
	m_pos(lightInfo->pos), 
	m_color(lightInfo->color),
	m_lightStrength(lightInfo->lightStrength)
{

}

PointLight::~PointLight()
{
	std::cout << "Light Destroyed\n";
}


void PointLight::Start()
{

}

void PointLight::Update(float dt)
{
	/*gameObject->transform.GetTransform() = glm::rotate(gameObject->transform.GetTransform(), -1.0f * dt, { 0.0f, 1.0f, 0.0f });*/
}

void PointLight::Shutdown()
{

}