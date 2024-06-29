#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

namespace Buffers
{
	class EBO
	{
	private:
		GLuint ID = 0;
		GLboolean IsBound = false;
		GLuint Elements = 0;

	public:
		EBO();
		EBO(GLvoid* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
		GLuint GetID() const;
		void Bind();
		void UnBind();
		void Delete();
		void Data(GLvoid* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
		void Draw(GLenum mode = GL_TRIANGLES);
	};
}