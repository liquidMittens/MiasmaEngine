#include "utility/MeshLoader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "utility/tiny_obj_loader.h"
#include <iostream>

std::vector<float> utility::MeshLoader::LoadMeshFromFile(const std::string& filename, glm::mat4 preTransform)
{
	// full obj mesh information in xyz,st,xyz format
	std::vector<float> vertexFormatData;

	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning, error;
	std::string meshFilename = MESH_DIR + filename;
	if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, meshFilename.c_str(), MATERIAL_DIR)) {
		std::cout << "utility::MeshLoader LoadMeshFromFile Failed: " << warning << error << '\n';
	}

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			glm::vec4 pos(0.0f);
			if (attributes.vertices.size() >= 3 && index.vertex_index >= 0) {
				pos = {
					attributes.vertices[3 * index.vertex_index],
					attributes.vertices[3 * index.vertex_index + 1],
					attributes.vertices[3 * index.vertex_index + 2],
					1
				};
				pos = preTransform * pos;
			}
			// normals
			glm::vec3 normal(0.0f);
			if (attributes.normals.size() >= 3 && index.normal_index >= 0) {
				normal = {
					attributes.normals[3 * index.normal_index],
					attributes.normals[3 * index.normal_index + 1],
					attributes.normals[3 * index.normal_index + 2]
				};

				normal = glm::mat3(preTransform) * normal;
			}

			glm::vec2 texCoords(0.0f);
			if (attributes.texcoords.size() >= 2 && index.texcoord_index >= 0) {
				texCoords = {
					attributes.texcoords[2 * index.texcoord_index],
					attributes.texcoords[2 * index.texcoord_index + 1],
				};
			}

			vertexFormatData.push_back(pos.x);
			vertexFormatData.push_back(pos.y);
			vertexFormatData.push_back(pos.z);
			vertexFormatData.push_back(texCoords.x);
			vertexFormatData.push_back(texCoords.y);
			vertexFormatData.push_back(normal.x);
			vertexFormatData.push_back(normal.y);
			vertexFormatData.push_back(normal.z);
		}
	}
	return vertexFormatData;
}