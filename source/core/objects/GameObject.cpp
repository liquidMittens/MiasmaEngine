#include "core/objects/GameObject.h"

void GameObject::UpdateGameObject(float dt)
{
	for (auto&& component : components) {
		if (component->IsActive()) {
			component->Update(dt);
		}
	}
}

void GameObject::SetActive(bool isActive) {
	active = isActive;
	for (auto&& component : components) {
		component->SetActive(active);
	}
}