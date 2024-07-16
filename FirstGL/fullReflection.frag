#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform samplerCube skybox;
uniform vec3 viewPos;

void main()
{
	vec3 vievDir = normalize(FragPos - viewPos);
	vec3 reflection = reflect(vievDir, normalize(Normal));
	FragColor = vec4(texture(skybox, reflection).rgb, 1.0f);
}
