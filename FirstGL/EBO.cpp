#include "EBO.hpp"


Buffers::EBO::EBO()
{
	glGenBuffers(1, &ID);
}

Buffers::EBO::EBO(GLvoid* data, GLsizeiptr size, GLenum usage)
{
	glGenBuffers(1, &ID);
	Bind();
	Data(data, size, usage);
	UnBind();
}

GLuint Buffers::EBO::GetID() const
{
	return ID;
}

void Buffers::EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	IsBound = true;
}

void Buffers::EBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	IsBound = false;
}

void Buffers::EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void Buffers::EBO::Data(GLvoid* data, GLsizeiptr size, GLenum usage)
{
	if (!IsBound)
		Bind();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	Elements = size / sizeof(unsigned int);
}

void Buffers::EBO::Draw(GLenum mode)
{
	if (!IsBound)
		Bind();
	glDrawElements(mode, Elements, GL_UNSIGNED_INT, 0);
	UnBind();
}
