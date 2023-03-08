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
uniform PointLight light;
uniform vec3 cameraPosition;

out vec4 finalColor;

vec3 calculateDiffuse();

void main()
{
	// ambient 
	vec3 temp = 0.2f * texture(textureSample, fragmentTexCoord).rgb;
	// lighting
	temp += calculateDiffuse();
	finalColor = vec4(temp, 1.0f);
	if(finalColor.a <= 0.1f)
		discard;
}

vec3 calculateDiffuse() {
	
	vec3 baseTexture = texture(textureSample, fragmentTexCoord).rgb;

	// geometric data 
	vec3 normalizedNormal = normalize(fragmentNormal);
	vec3 lightDir = light.position - fragmentPosition;
	float distance = length(lightDir);

	// diffuse (basic rough surface)
	vec3 lightingResult = light.color * baseTexture * max(0.0, dot(normalizedNormal, lightDir)) * light.strength / (distance * distance);

	return lightingResult;
}