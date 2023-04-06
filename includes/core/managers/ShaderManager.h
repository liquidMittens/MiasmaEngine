#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include <map>
#include <string_view>
#include "ShaderManager.h"

constexpr int SHADER_SIZE_MAX = 5000;
constexpr auto SHADER_DIR = "resources\\shaders\\";

enum class ShaderType
{
	BasicColor = 0,
	BasicTexture,
	BasicColorTexture,
	BlinnPhong,
	Diffuse,
	Unknown,
	MaxShaders
};

struct ShaderInfo
{
	unsigned int shaderId;
	std::string shaderName;
};

using ShaderMapType = std::map<std::string, ShaderInfo>;
using ProgramEnum = enum class ShaderType;

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void LoadShaderList(std::string_view dirPath);
	void LoadShader(const std::string& shaderName);
	ShaderInfo GetShaderFromMap(std::string_view shaderName);

private:
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;

	ShaderMapType m_shaderMap;
};

#endif
