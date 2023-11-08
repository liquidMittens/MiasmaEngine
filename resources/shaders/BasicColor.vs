#version 450 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexCoord;
layout (location = 2) in vec3 vertexColor;
layout (location = 0) out vec3 fragmentColor;
uniform mat4 model;
uniform mat4 viewproj;

void main()
{
	gl_Position = viewproj * model * vec4(vertexPosition, 1.0);
	fragmentColor = vec3(1.0f, 0.5f, 0.25f);
	//fragmentColor = vertexColor;
}