#ifndef MESHRENDERABLE_H_
#define MESHRENDERABLE_H_

#include "rendering/Material.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

constexpr int xyz_rgb_st_format_size = 8; // pos,color,texcoords
constexpr int xyz_st_xyz_format_size = 8; // pos,texcoords,normals

struct MeshRenderableCreateInfo
{
	const char* filename;
	glm::mat4 preTransform;
	std::string meshName;
};

class MeshRenderable
{
	friend class GUIBuilder;
public:
	MeshRenderable(MeshRenderableCreateInfo *pCreateInfo, const Material& mat);
	~MeshRenderable();

	bool AttachMaterial(const Material& newMat);

	size_t GetVertexCount() const { return m_vertices.size() / xyz_st_xyz_format_size; }
	size_t GetIndicesCount() const { return m_indices.size(); }
	Material GetMaterial() { return m_material; }
	const unsigned int GetVertexBufferObject() { return m_vbo; }
	const unsigned int GetVertexArrayObject() { return m_vao; } 
	const unsigned int GetIndexBufferObject() { return m_ibo; }
	glm::mat4& GetTransform() { return m_transform; }
	// TODO: these should be translations functions in their Transform class
	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 posVector);
	const glm::vec3 GetPosition();
private: 
	std::string m_meshName;
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_ibo;
	Material m_material;
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	glm::mat4 m_transform;
};


#endif
