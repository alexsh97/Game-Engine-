#version 330 core

out vec4 FragmentColor;

in vec2 outTextureCoord;

uniform sampler2D objectTexture;

void main()
{
	FragmentColor =  texture(objectTexture, outTextureCoord);
}






