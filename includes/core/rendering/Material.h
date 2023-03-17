#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <memory>
#include <string>
#include "managers/ShaderManager.h"
#include "rendering/Texture2D.h"

class Material
{
public:

	Material();
	~Material();
	Material(const Material& obj);
	Material& operator=(const Material& obj);

	bool AddTexture(Texture2D* textureInfo);
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
