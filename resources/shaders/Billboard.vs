#version 450 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexCoord;
layout (location = 2) in vec3 vertexNormal;

layout (location = 0) out vec2 fragmentTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// lets lock the Y axis of the model matrix to rotate around it
	mat4 modifiedModel = model;
	modifiedModel[0][0] = 1.0; 
	modifiedModel[0][1] = 0.0; 
	modifiedModel[0][2] = 0.0; 

	modifiedModel[2][0] = 0.0; 
	modifiedModel[2][1] = 0.0; 
	modifiedModel[2][2] = 1.0;

	// get world origin 
	vec4 world_origin = modifiedModel * vec4(0, 0, 0, 1);
	// get view origin
	vec4 view_origin = view * modifiedModel * vec4(0, 0, 0, 1);
	// get vertex world position
	vec4 world_pos = modifiedModel * vec4(vertexPosition, 1);

	vec4 view_pos = world_pos - world_origin + view_origin;
	
	gl_Position = proj * view_pos;
	fragmentTexCoord = vec2(vertexTexCoord.x, 1.0 - vertexTexCoord.y);
}