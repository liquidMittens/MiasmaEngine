#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <memory>
#include <string>
#include <map>
#include "rendering/Texture2D.h"

constexpr auto TEXTURE_DIR = "resources\\textures\\";

constexpr auto EXT_PNG = ".png";
constexpr auto EXT_JPG = ".jpg";

using TextureMapType = std::map<std::string, std::unique_ptr<Texture2D>>;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	TextureManager(const TextureManager& obj) = delete;
	TextureManager& operator=(const TextureManager& obj) = delete;

	static TextureManager& GetInstance() {
		if (m_instance == nullptr) {
			m_instance = std::make_unique<TextureManager>();
		}
		return (*m_instance.get());
	}

	bool LoadTexturesFromDirectory(std::string dir);
	Texture2D* GetTextureInfo(std::string_view texturename);

private:
	static std::unique_ptr<TextureManager> m_instance;
	bool LoadTexture(std::string filename);
	TextureMapType m_textureMap;
};

#endif