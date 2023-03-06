#include "rendering\Material.h"

Material::Material() : 
	m_shaderType(ShaderType::BasicColor),
	m_shader(0),
	m_textureId(0),
	m_textureName("None")
{

}

Material::~Material()
{

}

Material::Material(const Material& obj)
{
	m_shaderType = obj.m_shaderType;
	m_shader = obj.m_shader;
	m_textureId = obj.m_textureId;
	m_textureName = obj.m_textureName;
}

Material& Material::operator=(const Material& obj)
{
	if (this != &obj) {
		m_shaderType = obj.m_shaderType;
		m_shader = obj.m_shader;
		m_textureId = obj.m_textureId;
		m_textureName = obj.m_textureName;
	}
	return *this;
}

bool Material::AddTexture(std::string_view texturename, const unsigned int& textureId)
{
	bool success = true;
	m_textureName = texturename;
	m_textureId = textureId;
	return success;
}

bool Material::AttachShader(ShaderType shaderType, const unsigned int& shader)
{
	bool success = true;
	m_shaderType = shaderType;
	m_shader = shader;
	return success;
}
