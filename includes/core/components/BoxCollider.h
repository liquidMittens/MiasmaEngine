#ifndef BOXCOLLIDER_H_
#define BOXCOLLIDER_H_
#include "Collider.h"

namespace Miasma::RTTI
{
	class BoxCollider : public Collider
	{
	public:
		CLASS_DECLARATION(BoxCollider);

		BoxCollider(GameObject* owner, std::string&& initialValue) : 
			Collider(owner, std::move(initialValue))
		{}

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	};
}

#endif
