#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
out vec4 FragColor;

struct Material {
	sampler2D texture_diffuse0;
	sampler2D texture_specular1;
};


uniform Material material;

void main ()
{
	FragColor = vec4(texture(material.texture_specular1, TexCoords).rgb, 1.0f);
}