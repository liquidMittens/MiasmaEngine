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

const glm::vec3 Transform::GetPosition()
{
	glm::vec3 positionVector = m_transform[3];
	return positionVector;
}