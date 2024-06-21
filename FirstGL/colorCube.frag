#version 330 core

out vec4 FragColor;

struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * texture(material.diffuse, texCoord).rgb * light.diffuse;

	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectedDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

	vec3 finalColor = ambient + diffuse + specular;

	FragColor = vec4(finalColor, 1.0f);
}