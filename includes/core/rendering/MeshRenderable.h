#ifndef MESHRENDERABLE_H_
#define MESHRENDERABLE_H_

#include "rendering/Material.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

constexpr int xyz_rgb_st_format_size = 8;

class MeshRenderable
{
public:
	MeshRenderable(std::vector<float> vertices, const Material& mat);
	~MeshRenderable();

	bool AttachMaterial(const Material& newMat);

	size_t GetVertexCount() const { return m_vertices.size() / xyz_rgb_st_format_size; }
	Material GetMaterial() { return m_material; }
	const unsigned int GetVertexBufferObject() { return m_vbo; }
	const unsigned int GetVertexArrayObject() { return m_vao; } 
	glm::mat4& GetTransform() { return m_transform; }
private: 
	unsigned int m_vbo;
	unsigned int m_vao;
	Material m_material;
	std::vector<float> m_vertices;
	glm::mat4 m_transform;
};


#endif
