#ifndef MESHLOADER_H_
#define MESHLOADER_H_

#include <vector>
#include <string>
#include <string_view>
#include "glm/glm.hpp"

namespace utility
{
	namespace MeshLoader
	{
		#define MESH_DIR "resources\\models\\"
		#define	MATERIAL_DIR "resources\\materials\\"
		std::vector<float> LoadMeshFromFile(const std::string& filename, glm::mat4 preTransform);
	}
}

#endif
