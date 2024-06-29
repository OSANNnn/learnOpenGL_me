#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

namespace Buffers
{
	class VBO
	{
	private:
		GLuint ID = 0;
		GLboolean IsBound = false;

	public:
		VBO();
		VBO(GLvoid* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
		GLuint GetID() const;
		void Bind();
		void UnBind();
		void Delete();
		void Data(GLvoid* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
	};
}

