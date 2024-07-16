#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform samplerCube skybox;
uniform vec3 viewPos;

void main()
{
	float refractionRatio = 1.0f / 1.52f;
	vec3 newNormal = Normal;
	newNormal.z *= -1;
	vec3 vievDir = normalize(FragPos - viewPos);
	vec3 refraction = refract(vievDir, normalize(newNormal), refractionRatio);
	FragColor = vec4(texture(skybox, refraction).rgb, 1.0f);
}
