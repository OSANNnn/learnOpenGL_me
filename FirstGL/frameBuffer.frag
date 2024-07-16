#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D bufferTex;

void main()
{
	FragColor = vec4(texture(bufferTex, TexCoords).rgb, 1.0f);
	//FragColor = vec4(TexCoords, 1.0, 1.0);
}