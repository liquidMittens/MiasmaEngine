#include <Miasma/core/ecs/FollowTransform.h>
#include <Miasma/core/objects/GameObject.h>
#include <Miasma/core/glm/gtc/matrix_transform.hpp>
#include <Miasma/core/glm/gtx/quaternion.hpp>
#include <Miasma/core/camera/Camera.h>
using namespace Miasma::Component;
using namespace tdogl;

CLASS_DEFINITION(Component, FollowTransform);

FollowTransform::FollowTransform(GameObject* owner, GameObject* target) :
	Component(owner, TO_STRING(FollowTransform))
{
	m_target = target;
}

FollowTransform::~FollowTransform() {

}

void FollowTransform::Start() {

}

void FollowTransform::Update(float dt) {
	auto& camera = gameObject->GetComponent<Camera>();
	camera.lookAt(m_target->transform.GetPosition());
	//camera.lookAt(glm::vec3(5.0f, 5.0f, 5.0f));
}

void FollowTransform::Shutdown() {

}
