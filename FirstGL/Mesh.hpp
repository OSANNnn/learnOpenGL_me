#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "buffers.hpp"
#include "Shader.hpp"


struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh {
public:
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<Buffers::Texture> Textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
		std::vector<Buffers::Texture> textures);
	void Draw(Shader& shader);
	void Delete();

private:
	GLuint VAO, VBO, EBO;

	void setupMesh();
};