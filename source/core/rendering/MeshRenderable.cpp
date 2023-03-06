#include "rendering\MeshRenderable.h"
#include "core/glad/glad.h"

MeshRenderable::MeshRenderable(std::vector<float> vertices, const Material& mat)
{
	m_vertices.assign(vertices.begin(), vertices.end());
	m_material = mat;
	// create the vbo vao objects since we have some info
	glCreateBuffers(1, &m_vbo);
	glCreateVertexArrays(1, &m_vao);
	// setup our formatting for each vertex
	glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, xyz_rgb_st_format_size * sizeof(float));
	glNamedBufferStorage(m_vbo, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_STORAGE_BIT);
	
	// position info
	glEnableVertexArrayAttrib(m_vao, 0);
	glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(m_vao, 0, 0);
	//color info
	glEnableVertexArrayAttrib(m_vao, 1);
	glVertexArrayAttribFormat(m_vao, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribBinding(m_vao, 1, 0);
	// s,t texture info 
	glEnableVertexArrayAttrib(m_vao, 2);
	glVertexArrayAttribFormat(m_vao, 2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float));
	glVertexArrayAttribBinding(m_vao, 2, 0);
	m_transform = glm::mat4(1.0f);
}

MeshRenderable::~MeshRenderable()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

bool MeshRenderable::AttachMaterial(const Material& newMat)
{
	bool success = true;
	m_material = newMat;
	return success;
}