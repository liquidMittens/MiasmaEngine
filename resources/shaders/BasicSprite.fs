#version 450 core
layout (location = 0) in vec2 fragmentTexCoord;
uniform sampler2D textureSample;
out vec4 finalColor;

void main()
{
	finalColor = texture(textureSample, fragmentTexCoord);
	if(finalColor.a <= 0.1f)
		discard;
}