#include "VAO.h"

void Buffers::VAO::checkBinding()
{
	if (!IsBound)
		Bind();
}

Buffers::VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

GLuint Buffers::VAO::GetID() const
{
	return ID;
}

void Buffers::VAO::Bind()
{
	glBindVertexArray(ID);
	IsBound = true;
}

void Buffers::VAO::UnBind()
{
	glBindVertexArray(0);
	IsBound = false;
}

void Buffers::VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
	IsBound = false;
}

void Buffers::VAO::setVertexCount(GLuint count) 
{
	VertexCount = count;
}

void Buffers::VAO::EnableAttrib(GLint attribute)
{
	checkBinding();
	glEnableVertexAttribArray(attribute);
}

void Buffers::VAO::DisableAtrrib(GLint attribute)
{
	checkBinding();
	glDisableVertexAttribArray(attribute);
}

void Buffers::VAO::SetAttrib(GLuint index, GLint size, GLsizei stride, int offset, GLboolean normalize)
{
	checkBinding();
	glVertexAttribPointer(index, size, GL_FLOAT, normalize, stride * sizeof(float), (void*)(offset * sizeof(float)));
	EnableAttrib(index);
}

void Buffers::VAO::Draw(GLenum mode)
{
	checkBinding();
	glDrawArrays(mode, 0, VertexCount);
	UnBind();
}