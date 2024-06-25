#version 330 core

out vec4 FragColor;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
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

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform Material material;

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{	
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 finalColor = calcDirectionalLight(directionalLight, norm, viewDir);
	finalColor += calcPointLight(pointLight, norm, FragPos, viewDir);
	//finalColor = texture(material.texture_specular1, TexCoords).rgb;

	FragColor = vec4(finalColor, 1.0f);
}


vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 ambient = light.ambient * texture(material.texture_diffuse1, TexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.texture_specular1, TexCoords).rgb;

	return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	vec3 ambient = light.ambient * texture(material.texture_diffuse1, TexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.texture_specular1, TexCoords).rgb;

	return (ambient * attenuation + diffuse * attenuation + specular * attenuation);
}