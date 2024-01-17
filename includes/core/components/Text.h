#ifndef TEXT_H_
#define TEXT_H_
#include "Component.h"
#include "glm/glm.hpp"

class GLTtext;
namespace Miasma::Component
{
	class Text : public Component
	{
	public:
		CLASS_DECLARATION(Text);

		Text(GameObject* owner, const std::string& textStr, glm::vec3 textColor, float textScale = 2.0f);
		~Text();

		GLTtext* GetGLTtext() const { return m_gltTextObject; }
		const std::string& GetTextString() { return m_textStr; }
		const glm::vec3 GetTextColor() { return m_textColor; }
		float GetTextScale() { return m_textScale; }

		// behavior functions
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	private:
		GLTtext* m_gltTextObject;
		std::string m_textStr;
		glm::vec3 m_textColor;
		float m_textScale;
	};
}
#endif
