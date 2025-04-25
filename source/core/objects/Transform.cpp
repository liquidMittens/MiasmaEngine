#include "objects/Transform.h"

Transform::Transform() :
	m_transform(1.0f),
	_verticalAngle(0.0f),
	_horizontalAngle(0.0f),
	m_dirtyMatrix(false)
{

}

Transform::Transform(const Transform& obj)
{
	m_transform = obj.m_transform;
}

Transform::Transform(const glm::mat4 mat) :
	m_transform(1.0f),
	_verticalAngle(0.0f),
	_horizontalAngle(0.0f),
	m_dirtyMatrix(false)
{
	m_transform = mat;
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
	m_dirtyMatrix = true;
}

glm::vec3 Transform::GetPosition()
{
	glm::vec3 positionVector = m_transform[3];
	return positionVector;
}

void Transform::translate(const glm::vec3& pos)
{
	m_transform = glm::translate(m_transform, pos);
	m_dirtyMatrix = true;
}

void Transform::translate(const glm::vec2& pos)
{
	m_transform = glm::translate(m_transform, glm::vec3(pos.x, pos.y, 1.0f));
	m_dirtyMatrix = true;
}

void Transform::rotate(float deg, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, glm::radians(deg), axis);
	m_dirtyMatrix = true;
}

void Transform::rotate(glm::quat rot)
{
	m_transform = m_transform * glm::toMat4(rot);
}

void Transform::scale(glm::vec3 scaleVec)
{
	m_transform = glm::scale(m_transform, scaleVec);
	m_dirtyMatrix = true;
}

void Transform::resetTransformMatrix()
{
	m_transform = glm::identity<glm::mat4>();
	m_dirtyMatrix = true;
}

glm::vec3 Transform::forward() const {
	glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(forward);
}

glm::vec3 Transform::right() const {
	glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(right);
}

glm::vec3 Transform::up() const {
	glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(up);
}


/** private matrix calculation methods **/
glm::mat4 Transform::orientation() const {
	glm::mat4 orientation(1.0f);
	orientation = glm::rotate(orientation, glm::radians(_verticalAngle), glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0, 1, 0));
	return orientation;
}