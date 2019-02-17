#version 330 core
layout (location = 0) in vec3 inPosition;//położenie wierzchołka
layout (location = 1) in vec3 inNormal;//wektor normali, wskazujący kierunek odbicia światła
layout (location = 2) in vec2 inTextureCoord;//współrzędne tekstury

out vec3 outPos;
out vec3 outNormal;
out vec2 outTextureCoord;

uniform mat4 projection;//macierz projekcji
uniform mat4 view;//macierz widoku
uniform mat4 model;//macierz transformacji obiektu

void main()
{
	outPos = vec3(model * vec4(inPosition, 1.0));
	outNormal = mat3(transpose(inverse(model))) * inNormal;
	outTextureCoord = inTextureCoord;
	
	gl_Position = projection * view * vec4(outPos, 1.0);
	
	//ourColor = inColor;
	//outTextureCoord = vec2(inTextureCoord.x, inTextureCoord.y);
}