#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <memory>
#include <string>
#include "managers/ShaderManager.h"

class Texture2D;

class Material
{
public:

	Material();
	~Material();
	Material(const Material& obj);
	Material& operator=(const Material& obj);

	bool AddTexture(std::string_view texturename, const unsigned int& textureId);
	bool AttachShader(ShaderInfo shader);

	unsigned int GetTextureId() const { return m_textureId; }
	std::string GetTextureName() const { return m_textureName; }
	ShaderInfo GetShader() const { return m_shader; }

private:
	unsigned int m_textureId;
	std::string m_textureName;
	ShaderInfo m_shader;
};

#endif
