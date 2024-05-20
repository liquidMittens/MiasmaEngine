#include "Quad3D.h"
#include "core/glad/glad.h"
#include "MeshRenderable.h"

CLASS_DEFINITION(Component, Quad3d);

Quad3d::Quad3d(GameObject* owner, const Material& mat) :
	Component(owner, TO_STRING(Quad3d)),
	m_vbo(0),
	m_vao(0),
	m_ibo(0),
	m_defaultScale(5.0f)
{
	m_material = mat;
	// create the vertices 
	m_vertices = {
		-m_defaultScale, -m_defaultScale, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		m_defaultScale, -m_defaultScale, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		m_defaultScale, m_defaultScale, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-m_defaultScale, m_defaultScale, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	};
	// indices
	m_indices = {
		0, 1, 2, 2, 3, 0
	};

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

Quad3d::~Quad3d()
{
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void Quad3d::Resize(float x0, float x1) 
{

}

void Quad3d::Start()
{

}

void Quad3d::Update(float dt)
{

}

void Quad3d::Shutdown()
{

}