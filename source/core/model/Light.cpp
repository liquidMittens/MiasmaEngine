#include "model/Light.h"

Light::Light(LightCreationInfo* lightInfo) : 
	m_pos(lightInfo->pos), 
	m_color(lightInfo->color),
	m_lightStrength(lightInfo->lightStrength)
{

}

