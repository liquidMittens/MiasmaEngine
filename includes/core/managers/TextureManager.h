#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <memory>
#include <string>
#include <map>

#ifdef _DEBUG
#define TEXTURE_DIR "resources\\textures\\"
#else
#define TEXTURE_DIR "..\\..\\resources\\textures\\"
#endif

class Texture2D;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	bool LoadTexture(std::string filename);
	unsigned int GetTextureId(std::string_view texturename);
	const Texture2D* GetTextureInfo(std::string_view texturename);

private:
	std::map<std::string, std::unique_ptr<Texture2D>> m_textureMap;
};

#endif