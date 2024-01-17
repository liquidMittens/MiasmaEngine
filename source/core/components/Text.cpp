#include "Text.h"
#include "glad/glad.h"
#define GLT_IMPLEMENTATION
#include "glText/gltext.h"
using namespace Miasma::Component;

CLASS_DEFINITION(Component, Text);

Text::Text(GameObject* owner, const std::string& textStr, glm::vec3 textColor, float textScale) : 
	Component(owner, TO_STRING(Text)), 
	m_gltTextObject(nullptr), 
	m_textColor(textColor),
	m_textScale(textScale)
{
	m_gltTextObject = gltCreateText();
	gltSetText(m_gltTextObject, textStr.c_str());
}

Text::~Text()
{
	gltDeleteText(m_gltTextObject); // cleanup text object
}

// behavior functions
void Text::Start()
{

}

void Text::Update(float dt)
{
	
}

void Text::Shutdown()
{

}