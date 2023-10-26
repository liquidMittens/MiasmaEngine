#include "core/components/Sprite2D.h"
#include "core/glad/glad.h"
#include "objects/GameObject.h"
using namespace Miasma::RTTI;


CLASS_DEFINITION(Component, Sprite2D);

Sprite2D::Sprite2D(GameObject* owner, const Material& mat) : 
	Component(owner, TO_STRING(Sprite2D)),
	m_vbo(0),
	m_vao(0),
	m_ibo(0)
{
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	};

	std::vector<unsigned int> indices = {
		0, 1, 2, 2, 3, 0
	};

	m_spriteName = "SpriteName";
	m_vertices.assign(vertices.begin(), vertices.end());
	m_indices.assign(indices.begin(), indices.end());
	m_material = mat;
	// create the vbo vao objects since we have some info
	glCreateVertexArrays(1, &m_vao);
	glCreateBuffers(1, &m_vbo);
	// create index buffer
	glCreateBuffers(1, &m_ibo);

	// setup our formatting for each vertex
	glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, xyz_st_format * sizeof(float));

	// position info
	glEnableVertexArrayAttrib(m_vao, 0);
	glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(m_vao, 0, 0);
	// s,t texture info (texcoords)
	glEnableVertexArrayAttrib(m_vao, 1);
	glVertexArrayAttribFormat(m_vao, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribBinding(m_vao, 1, 0);

	// bind GL_ARRAY_BUFFER (vertex attributes)
	// GL_DYNAMIC_DRAW
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

	// bind GL_ELEMENT_ARRAY_BUFFER (vertex array indices)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
}

Sprite2D::Sprite2D(GameObject* owner, const std::string& spriteName, const Material& mat) :
	Component(owner, TO_STRING(Sprite2D)),
	m_vbo(0),
	m_vao(0),
	m_ibo(0)
{
	std::vector<float> vertices = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	};

	std::vector<unsigned int> indices = {
		0, 1, 2, 2, 3, 0
	};

	m_spriteName = spriteName;
	m_vertices.assign(vertices.begin(), vertices.end());
	m_indices.assign(indices.begin(), indices.end());
	m_material = mat;
	// create the vbo vao objects since we have some info
	glCreateVertexArrays(1, &m_vao);
	glCreateBuffers(1, &m_vbo);
	// create index buffer
	glCreateBuffers(1, &m_ibo);

	// setup our formatting for each vertex
	glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, xyz_st_format * sizeof(float));

	// position info
	glEnableVertexArrayAttrib(m_vao, 0);
	glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(m_vao, 0, 0);
	// s,t texture info (texcoords)
	glEnableVertexArrayAttrib(m_vao, 1);
	glVertexArrayAttribFormat(m_vao, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribBinding(m_vao, 1, 0);

	// bind GL_ARRAY_BUFFER (vertex attributes)
	// GL_DYNAMIC_DRAW
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

	// bind GL_ELEMENT_ARRAY_BUFFER (vertex array indices)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
}

Sprite2D::~Sprite2D()
{

}

void Sprite2D::Start()
{

}

void Sprite2D::Update(float dt)
{
	
}

void Sprite2D::Shutdown()
{

}