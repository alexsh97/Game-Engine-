#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoord;


out vec2 outTextureCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(inPosition,1.0f);
	
	outTextureCoord = vec2(inTextureCoord.x, inTextureCoord.y);
}