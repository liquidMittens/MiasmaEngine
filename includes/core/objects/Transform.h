#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "glm/gtc/matrix_transform.hpp"

class Transform
{
public:

	Transform();
	Transform(const Transform& obj);
	~Transform();

	glm::mat4 operator=(const glm::mat4& rhsMat);

	glm::mat4& GetTransform() { return m_transform; }
	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 posVector);
	glm::vec3 GetPosition();

	// methods 
	void translate(const glm::vec3& pos);
	void rotate(float angle, glm::vec3 axis);
	void scale(glm::vec3 scaleVec);
	void resetTransformMatrix();

private:
	glm::mat4 m_transform;
};

#endif