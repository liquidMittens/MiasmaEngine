#ifndef LIGHT_H_
#define LIGHT_H_
#include <glm/glm.hpp>

struct LightCreationInfo
{
	glm::vec3 pos;
	glm::vec3 color;
	float lightStrength;
};

class Light
{
public:
	Light(LightCreationInfo* lightInfo);

	glm::vec3 GetLightPosition() const { return m_pos; }
	glm::vec3 GetLightColor() const { return m_color; }
	float GetLightStrength() const { return m_lightStrength; }

private:
	glm::vec3 m_pos;
	glm::vec3 m_color;
	float m_lightStrength;
};

#endif
