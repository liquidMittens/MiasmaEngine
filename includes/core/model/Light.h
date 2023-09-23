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

	void SetLightPosition(float x, float y, float z) {
		m_pos.x = x;
		m_pos.y = y;
		m_pos.z = z;
	}

	void SetLightColor(float r, float g, float b) {
		m_color.x = r;
		m_color.y = g;
		m_color.z = b;
	}

	void SetLightStrength(float strength) { m_lightStrength = strength; }

private:
	glm::vec3 m_pos;
	glm::vec3 m_color;
	float m_lightStrength;
};

#endif
