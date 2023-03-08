#version 450 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexCoord;
layout (location = 2) in vec3 vertexNormal;

out vec2 fragmentTexCoord;
out vec3 fragmentPosition;
out vec3 fragmentNormal; 

uniform mat4 model;
uniform mat4 camera;

void main()
{
	gl_Position = camera * model * vec4(vertexPosition, 1.0);
	fragmentTexCoord = vec2(vertexTexCoord.x, 1.0 - vertexTexCoord.y);
	fragmentPosition = (model * vec4(vertexPosition, 1.0)).xyz;
	fragmentNormal = mat3(model) * vertexNormal;
}