#include "managers/TextureManager.h"
#include <filesystem>
namespace fs = std::filesystem;
#include <iostream>
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbimage/stb_image.h"
#include "rendering/Texture2D.h"
#include <format>

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::LoadTexturesFromDirectory(std::string dir)
{
	bool success = false;
	if (fs::is_directory(dir)) {
		for (const auto& file : fs::recursive_directory_iterator(dir)) {
			if (file.is_regular_file()) {
				std::cout << std::format("Loading Texture: {}\n", file.path().filename().string());
				LoadTexture(file.path().filename().string());
			}
		}
	}
	return success;
}

bool TextureManager::LoadTexture(std::string filename)
{
	bool success = true;
	std::unique_ptr<Texture2D> newTexture;
	std::string originalFilenameNoExtension;
	if (!fs::is_directory(filename)) {
		if (filename.rfind(EXT_PNG) == std::string::npos) {
			filename += EXT_PNG;
		}
		// no jpgs right now 
		if (filename.rfind(EXT_JPG) != std::string::npos) {
			success = false;
		}
		if (success) {
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
			}
		}
	}
	return success;
}

Texture2D* TextureManager::GetTextureInfo(std::string_view texturename)
{
	auto texture = m_textureMap.find(texturename.data());
	Texture2D* textureInfo = nullptr;
	if (texture != m_textureMap.end()) {
		textureInfo = texture->second.get();
	}
	else {
		textureInfo = m_textureMap.find("missing")->second.get();
	}
	return textureInfo;
}