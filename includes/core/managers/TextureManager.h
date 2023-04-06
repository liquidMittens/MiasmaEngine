#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <memory>
#include <string>
#include <map>
#include "rendering/Texture2D.h"

constexpr auto TEXTURE_DIR = "resources\\textures\\";

constexpr auto EXT_PNG = ".png";
constexpr auto EXT_JPG = ".jpg";

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	bool LoadTexturesFromDirectory(std::string dir);
	Texture2D* GetTextureInfo(std::string_view texturename);

private:
	bool LoadTexture(std::string filename);
	
	std::map<std::string, std::unique_ptr<Texture2D>> m_textureMap;
};

#endif