#include "core/components/Collider.h"
using namespace Miasma::RTTI;

CLASS_DEFINITION(Component, Collider);

Collider::Collider(GameObject* owner, std::string&& initialValue) :
	Miasma::RTTI::Component(owner, std::move(initialValue))
{

}

Collider::~Collider()
{

}

void Collider::Start()
{

}


void Collider::Update(float dt)
{

}

void Collider::Shutdown()
{

}