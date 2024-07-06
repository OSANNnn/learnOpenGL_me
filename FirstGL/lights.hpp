#pragma once

#include <glm/glm.hpp>
#include "buffers.hpp"

struct DirectionalLight {
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	DirectionalLight(glm::vec3 dir, glm::vec3 color, glm::vec3 amb = glm::vec3(1.0f))
		: direction(dir), ambient(amb), diffuse(color), specular(color) {}
};

struct PointLight {
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	glm::vec3 position;
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float cutOff;
	float outerCutOff;
};