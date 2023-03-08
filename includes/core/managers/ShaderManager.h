#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include <map>
#include <string_view>
#include "ShaderManager.h"

constexpr int SHADER_SIZE_MAX = 5000;
#define SHADER_DIR "resources\\shaders\\"

enum class ShaderType
{
	BasicColor = 0,
	BasicTexture,
	BasicColorTexture,
	BlinnPhong,
	Diffuse,
	Unknown
};

using ShaderMapType = std::map<ShaderType, unsigned int>;
using ProgramEnum = enum class ShaderType;

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void LoadShaderList(std::string_view dirPath);
	void LoadShader(const std::string& shaderName, ShaderType shaderEnum);
	int GetShaderFromMap(ShaderType shaderName);

private:
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;

	ShaderMapType m_shaderMap;
};

#endif
