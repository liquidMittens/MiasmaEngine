#include "utility/MeshLoader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "utility/tiny_obj_loader.h"
#include <iostream>
#include <unordered_map>


void utility::MeshLoader::LoadMeshFromFile(MeshLoaderInformation& meshLoaderInformation, const std::string& filename, glm::mat4 preTransform)
{
	std::map<int, int> temp;
	// full obj mesh information in xyz,st,xyz format
	std::vector<float> vertexFormatData;
	// indices
	std::vector<int> indices;

	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning, error;
	std::string meshFilename = MESH_DIR + filename;
	
	if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, meshFilename.c_str(), MATERIAL_DIR)) {
		std::cout << "utility::MeshLoader LoadMeshFromFile Failed: " << warning << error << '\n';
	}

	// this is our map to keep track of our non-unique vertex information
	std::unordered_map<Vertex, unsigned int> uniqueVertexMap;

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex{};
			// position
			if (attributes.vertices.size() >= 3 && index.vertex_index >= 0) {
				vertex.pos = {
					attributes.vertices[3 * index.vertex_index],
					attributes.vertices[3 * index.vertex_index + 1],
					attributes.vertices[3 * index.vertex_index + 2]
				};
				vertex.pos = glm::mat3(preTransform) * vertex.pos;
			}

			// texCoords
			if (attributes.texcoords.size() >= 2 && index.texcoord_index >= 0) {
				vertex.texCoords = {
					attributes.texcoords[2 * index.texcoord_index],
					attributes.texcoords[2 * index.texcoord_index + 1],
				};
			}

			// normals
			if (attributes.normals.size() >= 3 && index.normal_index >= 0) {
				vertex.normal = {
					attributes.normals[3 * index.normal_index],
					attributes.normals[3 * index.normal_index + 1],
					attributes.normals[3 * index.normal_index + 2]
				};

				vertex.normal = glm::normalize(glm::mat3(preTransform) * vertex.normal);
			}

			if (uniqueVertexMap.count(vertex) == 0) {
				uniqueVertexMap[vertex] = (unsigned int)meshLoaderInformation.vertices.size() / Miasma::Component::xyz_st_xyz_format_size;
				meshLoaderInformation.vertices.push_back(vertex.pos.x);
				meshLoaderInformation.vertices.push_back(vertex.pos.y);
				meshLoaderInformation.vertices.push_back(vertex.pos.z);
				meshLoaderInformation.vertices.push_back(vertex.texCoords.x);
				meshLoaderInformation.vertices.push_back(vertex.texCoords.y);
				meshLoaderInformation.vertices.push_back(vertex.normal.x);
				meshLoaderInformation.vertices.push_back(vertex.normal.y);
				meshLoaderInformation.vertices.push_back(vertex.normal.z);
			}

			meshLoaderInformation.indices.push_back(uniqueVertexMap[vertex]);
		}
	}
}