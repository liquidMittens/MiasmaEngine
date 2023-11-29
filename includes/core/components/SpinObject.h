#ifndef SPINOBJECT_H_
#define SPINOBJECT_H_
#include "Component.h"

class GameObject;

namespace Miasma::Component
{
	class SpinObject : public Component
	{
	public:
		CLASS_DECLARATION(SpinObject);

		SpinObject(GameObject* owner, float spinSpeed = 5.0f);
		~SpinObject() override;

		// behavior functions
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	private:

		float m_spinSpeed;
	};

}

#endif