#include "rendering\MeshRenderable.h"
#include "core/glad/glad.h"
#include "utility/MeshLoader.h"

MeshRenderable::MeshRenderable(MeshRenderableCreateInfo* pCreateInfo, const Material& mat)
{
	if (pCreateInfo->meshName.empty()) {
		m_meshName = "Default Mesh Object";
	}
	else {
		// set the mesh name if we have one
		m_meshName = pCreateInfo->meshName;
	}
	m_vertices = utility::MeshLoader::LoadMeshFromFile(pCreateInfo->filename, pCreateInfo->preTransform);
	m_material = mat;
	// create the vbo vao objects since we have some info
	glCreateBuffers(1, &m_vbo);
	glCreateVertexArrays(1, &m_vao);
	// setup our formatting for each vertex
	glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, xyz_rgb_st_format_size * sizeof(float));
	glNamedBufferStorage(m_vbo, m_vertices.size() * sizeof(float), m_vertices.data(), GL_DYNAMIC_STORAGE_BIT);
	
	// position info
	glEnableVertexArrayAttrib(m_vao, 0);
	glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(m_vao, 0, 0);
	// s,t texture info (texcoords)
	glEnableVertexArrayAttrib(m_vao, 1);
	glVertexArrayAttribFormat(m_vao, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribBinding(m_vao, 1, 0);
	//normal info
	glEnableVertexArrayAttrib(m_vao, 2);
	glVertexArrayAttribFormat(m_vao, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));
	glVertexArrayAttribBinding(m_vao, 2, 0);
	m_transform = glm::identity<glm::mat4>();
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