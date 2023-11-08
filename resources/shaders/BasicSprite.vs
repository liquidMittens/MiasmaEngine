#version 450 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexCoord;

layout (location = 0) out vec2 fragmentTexCoord;

uniform mat4 model;
uniform mat4 viewproj;

void main()
{
	gl_Position = viewproj * model * vec4(vertexPosition, 1.0);
	fragmentTexCoord = vec2(vertexTexCoord.x, vertexTexCoord.y);
}