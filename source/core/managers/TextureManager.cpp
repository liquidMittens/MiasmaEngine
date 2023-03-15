#include "managers/TextureManager.h"
#include <filesystem>
namespace fs = std::filesystem;
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbimage/stb_image.h"
#include "rendering/Texture2D.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
}

bool TextureManager::LoadTexture(std::string filename)
{
	bool success = false;
	std::unique_ptr<Texture2D> newTexture;
	std::string originalFilenameNoExtension;
	if (!fs::is_directory(filename)) {
		if (filename.rfind(".png") == std::string::npos) {
			filename += ".png";
		}
		size_t extensionIndex = filename.find_last_of('.');
		originalFilenameNoExtension = filename.substr(0, extensionIndex);
		if (m_textureMap.find(originalFilenameNoExtension) == m_textureMap.end()) {
			int width = 0, height = 0, channel = 0;
			unsigned int textureId = -1;
			unsigned char* textureData = stbi_load(std::string(TEXTURE_DIR + filename).c_str(), &width, &height, &channel, STBI_rgb_alpha);
			glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
			glTextureStorage2D(textureId, 1, GL_RGBA8, width, height); // creates the storage but hasn't loaded
			glTextureSubImage2D(textureId, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData); // loads the image data
			// set texture parameters
			glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // if you go passed the s (horizontal) repeat (could GL_CLAMP as well)
			glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // if you go passed the t (vertical) repeat
			glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // or GL_NEAREST (more pixelated)
			glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			m_textureMap.insert(std::make_pair(originalFilenameNoExtension, std::unique_ptr<Texture2D>(new Texture2D(originalFilenameNoExtension, width, height, channel, textureData, textureId))));
			success = true;
		}
	}
	return success;
}

unsigned int TextureManager::GetTextureId(std::string_view texturename)
{
	auto texture = m_textureMap.find(texturename.data());
	unsigned int textureId = 0;
	if (texture != m_textureMap.end()) {
		textureId = (*texture).second->GetTextureId();
	}
	return textureId;
}

const Texture2D* TextureManager::GetTextureInfo(std::string_view texturename)
{
	auto texture = m_textureMap.find(texturename.data());
	Texture2D* textureInfo = nullptr;
	if (texture != m_textureMap.end()) {
		textureInfo = texture->second.get();
	}
	return textureInfo;
}