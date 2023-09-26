#include "core/objects/GameObject.h"

void GameObject::UpdateGameObject(float dt)
{
	for (auto&& component : components) {
		component->Update(dt);
	}
}