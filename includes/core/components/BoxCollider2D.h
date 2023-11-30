#ifndef BOXCOLLIDER2D_H_
#define BOXCOLLIDER2D_H_
#include "Component.h"
#include "glm/glm.hpp"

namespace Miasma::Component
{

	class BoxCollider2D : public Component
	{
	public:
		CLASS_DECLARATION(BoxCollider2D);

		BoxCollider2D(GameObject* owner);
		~BoxCollider2D();

		// behavior functions
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	private:

	};
}

#endif
