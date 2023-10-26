#ifndef LIGHT_H_
#define LIGHT_H_
#include <glm/glm.hpp>
#include "components/Component.h"
#include "objects/GameObject.h"


namespace Miasma::RTTI
{
	struct LightCreationInfo
	{
		glm::vec3 pos;
		glm::vec3 color;
		float lightStrength;
	};

	class PointLight : public Component
	{
	public:

		CLASS_DECLARATION(PointLight);

		PointLight(GameObject* owner, LightCreationInfo* lightInfo);
		~PointLight() override;

		glm::vec3 GetLightPosition() const { 
			if (gameObject != nullptr) {
				return gameObject->transform.GetPosition();
			}
			return m_pos; 
		}
		glm::vec3 GetLightColor() const { return m_color; }
		float GetLightStrength() const { return m_lightStrength; }

		void SetLightPosition(float x, float y, float z) {
			if (gameObject != nullptr) {
				gameObject->transform.SetPosition(x, y, z);
			}
		}

		void SetLightPosition(glm::vec3& vec) {
			if (gameObject != nullptr) {
				gameObject->transform.SetPosition(vec);
			}
		}

		void SetLightColor(float r, float g, float b) {
			m_color.x = r;
			m_color.y = g;
			m_color.z = b;
		}

		void SetLightStrength(float strength) { m_lightStrength = strength; }
		/* Component interface methods */
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;
	private:
		glm::vec3 m_pos;
		glm::vec3 m_color;
		float m_lightStrength;
	};
} // Miasma::RTTI
#endif
