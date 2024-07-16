#version 330 core

out vec4 FragColor;

uniform int xRes;
uniform int yRes;

void main()
{
	float x = (gl_FragCoord.x / xRes);
	float y = (gl_FragCoord.y / yRes);
	FragColor = vec4(x, y, 0.5f, 1.0f);
}