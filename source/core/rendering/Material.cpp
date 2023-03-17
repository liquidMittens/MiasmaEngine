#include "rendering\Material.h"

Material::Material() : 
	m_textureId(0),
	m_textureName("None")
{

}

Material::~Material()
{

}

Material::Material(const Material& obj)
{
	m_shader = obj.m_shader;
	m_textureId = obj.m_textureId;
	m_textureName = obj.m_textureName;
}

Material& Material::operator=(const Material& obj)
{
	if (this != &obj) {
		m_shader = obj.m_shader;
		m_textureId = obj.m_textureId;
		m_textureName = obj.m_textureName;
	}
	return *this;
}

bool Material::AddTexture(Texture2D* textureInfo)
{
	bool success = true;
	m_textureName = textureInfo->GetTextureName();
	m_textureId = textureInfo->GetTextureId();
	return success;
}

bool Material::AttachShader(ShaderInfo shaderInfo)
{
	bool success = true;
	m_shader = shaderInfo;
	return success;
}
