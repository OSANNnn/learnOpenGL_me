#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

namespace Buffers
{
	class VAO
	{
	private:
		GLuint ID = 0;
		GLboolean IsBound = false;
		GLuint VertexCount = 0;
		void checkBinding();

	public:
		VAO();
		GLuint GetID() const;
		void Bind();
		void UnBind();
		void Delete();
		void setVertexCount(GLuint count);
		void EnableAttrib(GLint attribute);
		void DisableAtrrib(GLint attribute);
		void SetAttrib(GLuint index, GLint size, GLsizei stride, int offset, GLboolean normalize = GL_FALSE);
		void Draw(GLenum mode = GL_TRIANGLES);
	};
}
