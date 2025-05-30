#include <managers\ShaderManager.h>
#include <filesystem>
namespace fs = std::filesystem;
#include <iostream>
#include <fstream>
using std::ifstream;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
	for (auto& shader : m_shaderMap)
	{
		glDeleteShader(shader.second.shaderId);
	}
}

void ShaderManager::LoadShaderList(std::string_view dirPath)
{
	if (fs::is_directory(dirPath)) {
		for (const auto& file : fs::recursive_directory_iterator(dirPath)) {
			if (file.is_regular_file()) {
				std::string filenoExt = file.path().filename().replace_extension().string();
				std::cout << "Found shader: " << filenoExt << '\n';
				// we haven't loaded this shader yet so lets read, compile, and add to the map
				if (m_shaderMap.find(filenoExt) == m_shaderMap.end()) {
					std::cout << "LOADED shader: " << filenoExt << '\n';
					LoadShader(filenoExt);
				}
			}
		}
	}
}

void ShaderManager::LoadShader(const std::string& shaderName)
{
	if (fs::is_directory(SHADER_DIR)) {
		std::string vertexShaderFilename, fragmentShaderFilename;
		vertexShaderFilename = SHADER_DIR + shaderName + ".vs";
		fragmentShaderFilename = SHADER_DIR + shaderName + ".fs";
		if (fs::exists(fs::path(vertexShaderFilename)) && fs::exists(fs::path(fragmentShaderFilename))) {
			// load vertex shader
			ifstream vertexShaderHandle(vertexShaderFilename, std::ios_base::in | std::ios_base::binary);
			char vertexBuffer[SHADER_SIZE_MAX];
			memset(vertexBuffer, 0, SHADER_SIZE_MAX);
			vertexShaderHandle.read(vertexBuffer, SHADER_SIZE_MAX);
			
			// load fragment shader
			ifstream fragmentShaderHandle(fragmentShaderFilename, std::ios_base::in | std::ios_base::binary);
			char fragmentBuffer[SHADER_SIZE_MAX];
			memset(fragmentBuffer, 0, SHADER_SIZE_MAX);
			fragmentShaderHandle.read(fragmentBuffer, SHADER_SIZE_MAX);
			// create the shaders and compile
			// vertex shader
			const char* sourcePtr = vertexBuffer;
			unsigned int vsInt = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vsInt, 1, &sourcePtr, NULL);
			glCompileShader(vsInt);
			int success = 0;
			char errorBuffer[1024];
			memset(errorBuffer, 0, 1024);
			glGetShaderiv(vsInt, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(vsInt, 1024, NULL, errorBuffer);
				std::cout << "Error compiling vertex shader: " + vertexShaderFilename << " msg: " << errorBuffer << '\n';
			}
			// fragment shader
			sourcePtr = fragmentBuffer;
			unsigned int fsInt = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fsInt, 1, &sourcePtr, NULL);
			glCompileShader(fsInt);
			memset(errorBuffer, 0, 1024);
			glGetShaderiv(fsInt, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(fsInt, 1024, NULL, errorBuffer);
				std::cout << "Error compiling fragment shader: " + fragmentShaderFilename << " msg: " << errorBuffer << '\n';
			}

			// create program
			unsigned int newProgram = glCreateProgram();
			glAttachShader(newProgram, vsInt);
			glAttachShader(newProgram, fsInt);
			glLinkProgram(newProgram);
			glGetProgramiv(newProgram, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(newProgram, 1024, NULL, errorBuffer);
				std::cout << "Error Linking Program for: " + shaderName << " msg: " << errorBuffer << '\n';
			}

			// we're linked we dont need to keep the shader compiled code objects anymore
			glDeleteShader(vsInt);
			glDeleteShader(fsInt);

			// create new shaderInfo object
			ShaderInfo newShader = { newProgram, shaderName };
			// add this new program to the shader manager and use shaderEnum as the calling key
			m_shaderMap.insert(std::make_pair(shaderName, newShader));
		}
	}
}

ShaderInfo ShaderManager::GetShaderFromMap(std::string_view shaderName)
{
	ShaderInfo shader = {0, "Unknown"};
	if (m_shaderMap.size() > 0) {
		auto shaderIter = m_shaderMap.find(shaderName.data());
		if (shaderIter != m_shaderMap.end()) {
			shader = (*shaderIter).second;
		}
		else {
			std::cout << "ERR: Could not load shader(" << shaderName.data() << ")\n";
		}
	}
	return shader;
}