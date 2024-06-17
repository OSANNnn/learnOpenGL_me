#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{
	float ambientStrenght = 0.1f;
	vec3 ambientLight = lightColor * ambientStrenght;
	vec3 norm = normalize(normal);

	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	float specularStrenght = 0.5f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectedDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0f), 32);
	vec3 specular = specularStrenght * spec * lightColor;

	vec3 newCol = (ambientLight + diffuse + specular) * objectColor;

	FragColor = vec4(newCol, 1.0f);
}