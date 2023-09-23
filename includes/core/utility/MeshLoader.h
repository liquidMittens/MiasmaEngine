#ifndef MESHLOADER_H_
#define MESHLOADER_H_

#include <vector>
#include <string>
#include <string_view>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"
#include "objects/MeshRenderable.h"

namespace utility
{
	namespace MeshLoader
	{
		struct MeshLoaderInformation
		{
			std::vector<float> vertices;
			std::vector<int> indices;
		};

		struct Vertex {
			glm::vec3 pos;
			glm::vec2 texCoords;
			glm::vec3 normal;

			bool operator==(const Vertex& obj) const {
				return pos == obj.pos && texCoords == obj.texCoords && normal == obj.normal;
			}
		};
#ifdef _DEBUG
#define MESH_DIR "resources\\models\\"
#define	MATERIAL_DIR "resources\\materials\\"
#else
#define MESH_DIR "..\\..\\resources\\models\\"
#define	MATERIAL_DIR "..\\..\\resources\\materials\\"
#endif // DEBUG

		
		void LoadMeshFromFile(MeshLoaderInformation& meshLoaderInformation, const std::string& filename, glm::mat4 preTransform);
	}
}

namespace std {
	template<> 
	struct hash<utility::MeshLoader::Vertex> {
		size_t operator()(utility::MeshLoader::Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^
				(hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.texCoords) << 1);
		}
	};
}

#endif
