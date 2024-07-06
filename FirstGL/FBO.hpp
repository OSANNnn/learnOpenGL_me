#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.hpp"
#include "primitives.hpp"

class FBO
{
	GLuint ID;
	GLuint RBO;
	GLuint TexID;
	Primitives::FrameQuad frame;
	bool hasRBO = false;
	bool hasColor = false;
	void AttachRBO(const unsigned int width, const unsigned int height);
	void CreateColorBuffer(const unsigned int width, const unsigned int height);

public:
	FBO();
	FBO(const unsigned int width, const unsigned int height);
	void Bind();
	void UnBind();
	void Delete();
	void Render(Shader& shaderProgram);
};