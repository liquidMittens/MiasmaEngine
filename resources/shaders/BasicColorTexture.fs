#version 450 core
layout (location = 0) in vec3 fragmentColor;
layout (location = 1) in vec2 fragmentTexCoord;
uniform sampler2D textureSample;
out vec4 finalColor;

void main()
{
	vec4 texColor = texture(textureSample, fragmentTexCoord);
	if(texColor.a <= 0.2)
		discard;
	finalColor = vec4(fragmentColor, 1.0) * texColor;
}