#ifndef BOXCOLLIDER_H_
#define BOXCOLLIDER_H_
#include "Collider.h"

namespace miasma_rtti
{
	class BoxCollider : public Collider
	{
	public:
		CLASS_DECLARATION(BoxCollider);

		BoxCollider(std::string&& initialValue) : 
			Collider(std::move(initialValue))
		{}

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	};
}

#endif
