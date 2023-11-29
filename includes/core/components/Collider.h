#ifndef COLLIDER_H_
#define COLLIDER_H_
#include "Component.h"

namespace Miasma::Component
{
	class Collider : public Component
	{
	public:
		CLASS_DECLARATION(Collider);
		// ctor
		Collider(GameObject* owner, std::string&& initialValue);

		~Collider();

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;
	};
}
#endif
