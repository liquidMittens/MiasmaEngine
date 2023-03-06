#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include <memory>
#include <string>

class Texture2D
{
public:

	Texture2D(std::string textureName, int w, int h, int channel, unsigned char* textureData, unsigned int textureId);
	~Texture2D();

	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;

	const std::string& GetTextureName() const { return m_textureName; }
	int GetWidth() const { return m_width; }
	void SetWidth(const int& width) { m_width = width; }
	int GetHeight() const { return m_height; }
	void SetHeight(const int& height) { m_height = height; }
	constexpr unsigned char* GetTextureData() const { return m_textureData; }
	const unsigned int GetTextureId() const { return m_textureId; }
	void SetTextureId(const unsigned int& textureId) { m_textureId = textureId; }

private:
	std::string m_textureName;
	int m_width;
	int m_height;
	int m_channel;
	unsigned char* m_textureData;
	unsigned int m_textureId;
};

#endif