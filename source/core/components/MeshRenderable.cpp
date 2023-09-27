#include "core/components/MeshRenderable.h"
#include "core/glad/glad.h"
#include "utility/MeshLoader.h"
#include <iostream>
#include "objects/GameObject.h"
using namespace miasma_rtti;

CLASS_DEFINITION(Component, MeshRenderable);

MeshRenderable::MeshRenderable(GameObject* owner, MeshRenderableCreateInfo* pCreateInfo, const Material& mat) :
	Component(owner, TO_STRING(MeshRenderable)),
	m_vbo(0),
	m_vao(0),
	m_ibo(0)
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
	}
	else {
		std::cout << "MeshRenderable CreateInfo* is NULL\n";
	}
}

MeshRenderable::~MeshRenderable()
{
	std::cout << std::format("Cleaning up MeshRenderable{}\n", m_meshName.c_str());
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

void MeshRenderable::Start()
{

}

void MeshRenderable::Update(float dt)
{
	/*gameObject->transform.GetTransform() = glm::rotate(gameObject->transform.GetTransform(), -1.0f * dt, { 0.0f, 1.0f, 0.0f });*/
}

void MeshRenderable::Shutdown()
{

}