#ifndef COLLIDER_H_
#define COLLIDER_H_
#include "Component.h"

namespace miasma_rtti
{
	class Collider : public Component
	{
	public:
		CLASS_DECLARATION(Collider);
		// ctor
		Collider(std::string&& initialValue) :
			Component(std::move(initialValue))
		{

		}

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;
	};
}
#endif
