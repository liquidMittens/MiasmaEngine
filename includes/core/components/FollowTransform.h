#ifndef FOLLOWTRANSFORM_H_
#define FOLLOWTRANSFORM_H_
#include "Component.h"
#include "glm/glm.hpp"

namespace Miasma::Component
{
	class FollowTransform : public Component
	{
	public: 
		CLASS_DECLARATION(FollowTransform);

		FollowTransform(GameObject* owner, GameObject* target);
		~FollowTransform();

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	private: 
		GameObject* m_target;
	};
}
#endif
