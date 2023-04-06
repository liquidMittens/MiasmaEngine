#version 450 core

vec3 colorA = vec3(0.5f, 0.5f, 0.5f);
vec3 outlineColor = vec3(1.0f, 1.0f, 1.0f);
float litOutlineThickness = 0.01f;
float unlitOutlineThickness = 0.8f;


struct PointLight {
	vec3 color;
	vec3 position;
	float strength;
};

in vec2 fragmentTexCoord;
in vec3 fragmentPosition;
in vec3 fragmentNormal;

uniform sampler2D textureSample;
uniform vec3 cameraPosition;
uniform PointLight light;

out vec4 finalColor;

void main()
{	
	vec3 normalDirection = normalize(fragmentNormal);
	normalDirection += normalize(normalDirection);
	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
	vec3 lightDirection;
	float attenuation = 5.0f;
	vec3 vertexToLightSource = light.position - fragmentPosition;
	float distance = length(vertexToLightSource);
	attenuation = distance / 1.0f;
	lightDirection = normalize(vertexToLightSource);

	// sample default texture information;
	finalColor = texture(textureSample, fragmentTexCoord);

	// low priority: diffuse illumination		
	//if (attenuation * max(0.0, dot(normalDirection, lightDirection)) >= 0.1f)
	//{
	//	finalColor = vec4(vec3(light.color) * vec3(colorA), 1.0f); 
	//}

	// higher priority: outline
	if (dot(viewDirection, normalDirection) <= mix(unlitOutlineThickness, litOutlineThickness, max(0.0, dot(viewDirection, normalDirection))))
	{
		finalColor = vec4(vec3(light.color) * vec3(outlineColor), 1.0f); 
	}

	if(finalColor.a <= 0.1f)
		discard;
}