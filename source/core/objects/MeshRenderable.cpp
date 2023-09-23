#include "core/objects/MeshRenderable.h"
#include "core/glad/glad.h"
#include "utility/MeshLoader.h"
#include <iostream>

CLASS_DEFINITION(miasma_rtti::Component, MeshRenderable);

MeshRenderable::MeshRenderable(MeshRenderableCreateInfo* pCreateInfo, const Material& mat) : 
	Component(TO_STRING(MeshRenderable))
{
	if (pCreateInfo != nullptr) {
		if (pCreateInfo->meshName.empty()) {
			m_meshName = "Default Mesh Object";
		}
		else {
			// set the mesh name if we have one
			m_meshName = pCreateInfo->meshName;
		}
		utility::MeshLoader::MeshLoaderInformation meshLoaderInformation;
		utility::MeshLoader::LoadMeshFromFile(meshLoaderInformation, pCreateInfo->filename, pCreateInfo->preTransform);
		m_vertices.assign(meshLoaderInformation.vertices.begin(), meshLoaderInformation.vertices.end());
		m_indices.assign(meshLoaderInformation.indices.begin(), meshLoaderInformation.indices.end());
		m_material = mat;
		// create the vbo vao objects since we have some info
		glCreateVertexArrays(1, &m_vao);
		glCreateBuffers(1, &m_vbo);
		// create index buffer
		glCreateBuffers(1, &m_ibo);

		// setup our formatting for each vertex
		glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, xyz_st_xyz_format_size * sizeof(float));

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

		// bind GL_ARRAY_BUFFER (vertex attributes)
		// GL_DYNAMIC_DRAW
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

		// bind GL_ELEMENT_ARRAY_BUFFER (vertex array indices)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

		m_transform = glm::identity<glm::mat4>();
	}
	else {
		std::cout << "MeshRenderable CreateInfo* is NULL\n";
	}
}

MeshRenderable::~MeshRenderable()
{
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

bool MeshRenderable::AttachMaterial(const Material& newMat)
{
	bool success = true;
	m_material = newMat;
	return success;
}

void MeshRenderable::SetPosition(float x, float y, float z)
{
	m_transform[3].x = x;
	m_transform[3].y = y;
	m_transform[3].z = z;
}

void MeshRenderable::SetPosition(glm::vec3 posVector)
{
	m_transform[3] = glm::vec4(posVector, 1.0f);
}

const glm::vec3 MeshRenderable::GetPosition()
{
	glm::vec3 positionVector = m_transform[3];
	return positionVector;
}

void MeshRenderable::Start()
{

}

void MeshRenderable::Update(float dt)
{

}

void MeshRenderable::Shutdown()
{

}