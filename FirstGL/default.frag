#version 330 core

out vec4 FragColor;
in vec3 vColor;
in vec2 TexCoord;
in vec3 vPos;

uniform sampler2D texture1;
uniform float mixValue;

void main()
{
	//FragColor = texture(texture1, TexCoord);

	FragColor = vec4(vColor, 1.0f);
}