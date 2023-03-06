#include "rendering/Texture2D.h"
#include "stbimage/stb_image.h"
#include "core/glad/glad.h"

Texture2D::Texture2D(std::string textureName, int w, int h, int channel, unsigned char* textureData, unsigned int textureId) :
	m_textureName(textureName),
	m_width(w),
	m_height(h),
	m_channel(channel),
	m_textureData(nullptr),
	m_textureId(textureId)
{
	// allocate new texture buffer
	if (textureData != nullptr) {
		unsigned int incomingBufferSize = w * h * STBI_rgb_alpha;
		m_textureData = new unsigned char[incomingBufferSize];
		memset(m_textureData, 0, incomingBufferSize);
		memcpy(m_textureData, textureData, incomingBufferSize);
	}
}

Texture2D::~Texture2D()
{
	// delete out textureId and our buffer from stbi_load
	glDeleteTextures(1, &m_textureId);
	stbi_image_free(m_textureData);
}