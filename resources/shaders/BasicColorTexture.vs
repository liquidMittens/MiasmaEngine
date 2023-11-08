#version 450 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexTexCoord;
layout (location = 0) out vec3 fragmentColor;
layout (location = 1) out vec2 fragmentTexCoord;
uniform mat4 model;
uniform mat4 viewproj;

void main()
{
	gl_Position = viewproj * model * vec4(vertexPosition, 1.0);
	fragmentColor = vertexColor;
	fragmentTexCoord = vec2(vertexTexCoord.x, 1.0 - vertexTexCoord.y);
}