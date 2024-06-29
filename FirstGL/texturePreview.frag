#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	sampler2D texture_normals1;
	sampler2D texture_emission;
	float shininess;
	float emissionIntensity;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 viewPos;

vec4 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
    vec4 finalColor = calcDirectionalLight(directionalLight, norm, viewDir);
    FragColor = finalColor;
}


vec4 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0f);


	vec4 ambient = vec4(light.ambient, 1.0f) * texture(material.texture_diffuse1, TexCoords);
	vec4 diffuse = vec4(light.diffuse, 1.0f) * diff * texture(material.texture_diffuse1, TexCoords);

	return (ambient + diffuse);
}