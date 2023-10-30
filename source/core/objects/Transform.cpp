#include "objects/Transform.h"

Transform::Transform() :
	m_transform(1.0f)
{

}

Transform::Transform(const Transform& obj)
{
	m_transform = obj.m_transform;
}

Transform::~Transform()
{

}

glm::mat4 Transform::operator=(const glm::mat4& rhsMat)
{
	m_transform = rhsMat;
	return m_transform;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_transform[3].x = x;
	m_transform[3].y = y;
	m_transform[3].z = z;
}

void Transform::SetPosition(glm::vec3 posVector)
{
	m_transform[3] = glm::vec4(posVector, 1.0f);
}

glm::vec3 Transform::GetPosition()
{
	glm::vec3 positionVector = m_transform[3];
	return positionVector;
}

void Transform::translate(const glm::vec3& pos)
{
	m_transform = glm::translate(m_transform, pos);
}

void Transform::resetTransformMatrix()
{
	m_transform = glm::identity<glm::mat4>();
}