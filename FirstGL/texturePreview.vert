#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


out vec2 TexCoord;
out vec3 Pos;


void main()
{
	TexCoord = aTexCoord;
	vec3 Pos = aPos;
	gl_Position = vec4(aPos, 1.0);
}