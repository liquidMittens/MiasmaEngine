#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <vector>
#include <memory>
#include "Component.h"
#include <iostream>
#include <typeinfo>
using namespace miasma_rtti;

class GameObject
{
public:

	template<typename ComponentType, typename... Args>
	void AddComponent(Args&&... parameters);
	
	template<typename ComponentType>
	bool RemoveComponent();

	template<typename ComponentType>
	int RemoveComponents();

	template<typename ComponentType>
	ComponentType& GetComponent();

	template<typename ComponentType>
	std::vector<ComponentType*> GetComponents();

	//template<int idx, typename TType, float flt>
	//void DoSomething();


private:

	std::vector<std::unique_ptr<miasma_rtti::Component>> components;
};

template<typename ComponentType, typename... Args>
void GameObject::AddComponent(Args&&... parameters)
{
	components.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(parameters)...));
}

template<typename ComponentType>
bool GameObject::RemoveComponent()
{
	bool found = false;
	auto removeComponent = std::find_if(components.begin(), components.end(),
		[componentType = ComponentType::Type](miasma_rtti::Component c) {
			return c.IsClassType(componentType);
		});
	if (removeComponent != components.end()) {
		found = true;
		components.erase(removeComponent);
	}
	return found;
}

template<typename ComponentType>
int GameObject::RemoveComponents()
{
	int numComponentsFound = 0;
	bool found = false;
	do {

		auto removeComponent = std::find_if(components.begin(), components.end(),
			[componentType = ComponentType::Type](miasma_rtti::Component c) {
				return c.IsClassType(componentType);
			});

		found = removeComponent != components.end();
		if (found) {
			++numComponentsFound;
			components.erase(removeComponent);
		}

	} while (found);

	return numComponentsFound;
}

template<typename ComponentType >
ComponentType& GameObject::GetComponent() {
	for (auto&& component : components) {
		if (component->IsClassType(ComponentType::Type))
			return *static_cast<ComponentType*>(component.get());
	}

	return *std::unique_ptr<ComponentType>(nullptr);
}

template<typename ComponentType>
std::vector<ComponentType*> GameObject::GetComponents()
{
	std::vector< ComponentType* > componentsOfType;
	for (auto&& component : components) {
		if (component->IsClassType(ComponentType::Type))
			componentsOfType.emplace_back(static_cast<ComponentType*>(component.get()));
	}

	return componentsOfType;
}

//template<int idx, typename TType, float flt>
//void GameObject::DoSomething()
//{
//	std::cout << "DoSomething()\n";
//	int result = idx + (int)flt;
//	std::cout << std::format("Result: {}\n", result);
//	std::cout << "Typeid: " << typeid(TType).name();
//}

#endif