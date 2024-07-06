#include "VBO.hpp"

Buffers::VBO::VBO()
{
	glGenBuffers(1, &ID);
}

Buffers::VBO::VBO(GLvoid* data, GLsizeiptr size, GLenum usage)
{
	glGenBuffers(1, &ID);
	Bind();
	Data(data, size, usage);
	UnBind();
}

GLuint Buffers::VBO::GetID() const
{
	return ID;
}

void Buffers::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	IsBound = true;
}

void Buffers::VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	IsBound = false;
}

void Buffers::VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void Buffers::VBO::Data(GLvoid* data, GLsizeiptr size, GLenum usage)
{
	if (!IsBound)
		Bind();

	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}
