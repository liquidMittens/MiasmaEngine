#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "glm/gtc/matrix_transform.hpp"

class Transform
{
public:

	Transform();
	Transform(const Transform& obj);
	Transform(const glm::mat4 mat);
	~Transform();

	glm::mat4 operator=(const glm::mat4& rhsMat);

	glm::mat4& GetTransform() { return m_transform; }
	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 posVector);
	glm::vec3 GetPosition();

	// methods 
	void translate(const glm::vec3& pos);
	void translate(const glm::vec2& pos);
	void rotate(float angle, glm::vec3 axis);
	void scale(glm::vec3 scaleVec);
	void resetTransformMatrix();
	bool isDirty() { return m_dirtyMatrix; }
	void setIsDirty(bool dirtyMatrix) { m_dirtyMatrix = dirtyMatrix; }

	glm::vec3 forward() const;
	glm::vec3 right() const;
	glm::vec3 up() const;

private:
	glm::mat4 m_transform;
	float _horizontalAngle;
	float _verticalAngle;
	bool m_dirtyMatrix;

	// private methods to do matrix calculations
	glm::mat4 orientation() const;

};

#endif
