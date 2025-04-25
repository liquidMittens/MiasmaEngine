#ifndef _SCROLLVIEW_H_
#define _SCROLLVIEW_H_
#include "Component.h"
#include "glm/glm.hpp"

namespace Miasma::Component
{
	class ScrollView : Component
	{
	public:
		CLASS_DECLARATION(ScrollView);

		ScrollView(GameObject* owner, glm::vec2 size);
		~ScrollView();

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	private:
		glm::vec2 m_scrollviewSize;

	};
}

#endif
