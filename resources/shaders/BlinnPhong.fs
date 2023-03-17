#version 450 core

struct PointLight {
	vec3 color;
	vec3 position;
	float strength;
};

in vec2 fragmentTexCoord;
in vec3 fragmentPosition;
in vec3 fragmentNormal;

uniform sampler2D textureSample;
#define MAX_POINT_LIGHTS 2
uniform PointLight light[MAX_POINT_LIGHTS];
uniform vec3 cameraPosition;

out vec4 finalColor;

vec3 calculatePointLight(PointLight light, vec3 normalizedNormal, vec3 fragPos, vec3 viewDir);

void main()
{
	// normalize fragment normal 
	vec3 normalized_normal = normalize(fragmentNormal);
	// get view direction
	vec3 viewDir = normalize(cameraPosition - fragmentPosition);

	// lighting
	vec3 specPointlight;
	for(unsigned int i = 0; i < MAX_POINT_LIGHTS; ++i) {
		specPointlight += calculatePointLight(light[i], normalized_normal, fragmentPosition, viewDir);
	}
	finalColor = vec4(specPointlight, 1.0f);
	if(finalColor.a <= 0.1f)
		discard;
}

vec3 calculatePointLight(PointLight light, vec3 normalizedNormal, vec3 fragPos, vec3 viewDir) {

	// get light direction
	vec3 lightDir = normalize(light.position - fragmentPosition);
	// diffuse shading 
	float diffDot = max(0.0, dot(normalizedNormal, lightDir));
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normalizedNormal);
	float spec = pow(max(0.0, dot(viewDir, reflectDir)), 32);
	// attenuation
	float distance = length(light.position - fragmentPosition);
	float attenuation = light.strength / (distance * distance);

	// ambient result (fragment texturecoord + ambient value)
	vec3 ambient = 0.2f * texture(textureSample, fragmentTexCoord).rgb;
	vec3 diffuse = light.color * diffDot * texture(textureSample, fragmentTexCoord).rgb;
	vec3 specular = vec3(1.0) * spec * texture(textureSample, fragmentTexCoord).rgb;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}