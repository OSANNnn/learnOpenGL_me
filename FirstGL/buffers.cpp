#include "buffers.hpp"
#include <iostream>
#include <stb_image.h>

using namespace Buffers;

Buffer::Buffer(GLenum bufferT, GLenum dataT) : ID(0)
{	
	BufferType = bufferT;
	DataType = dataT;
	switch (BufferType)
	{
	case GL_ARRAY_BUFFER:
	case GL_ELEMENT_ARRAY_BUFFER:
		glGenBuffers(1, &ID);
		break;
	case GL_TEXTURE_2D:
		glGenTextures(1, &ID);
		break;
	case GL_VERTEX_ARRAY:
		glGenVertexArrays(1, &ID);
		break;
	default:
		break;
	}
}

void Buffer::Bind()
{
	if (ID != 0)
	{
		switch (BufferType)
		{
		case GL_ARRAY_BUFFER:
		case GL_ELEMENT_ARRAY_BUFFER:
			glBindBuffer(BufferType, ID);
			break;
		case GL_TEXTURE_2D:
			glBindTexture(BufferType, ID);
			break;
		case GL_VERTEX_ARRAY:
			glBindVertexArray(ID);
			break;
		default:
			break;
		}
		isBound = true;
	}
	else
	{
		std::cout << "Trying to bind buffer not generated" << std::endl;
	}
}

void Buffer::Data(GLvoid* data, GLsizeiptr size, GLenum usage)
{
	switch (BufferType)
	{
	case GL_ARRAY_BUFFER:
	case GL_ELEMENT_ARRAY_BUFFER:
		glBufferData(BufferType, size, data, usage);
	default:
		break;
	}
}

void Buffers::Buffer::Draw() {}

void Buffer::UnBind()
{
	switch (BufferType)
	{
	case GL_ARRAY_BUFFER:
	case GL_ELEMENT_ARRAY_BUFFER:
		glBindBuffer(BufferType, 0);
		break;
	case GL_TEXTURE_2D:
		glBindTexture(BufferType, 0);
		break;
	case GL_VERTEX_ARRAY:
		glBindVertexArray(0);
		break;
	default:
		break;
	}
	isBound = false;
}

void Buffer::Delete()
{
	switch (BufferType)
	{
	case GL_ARRAY_BUFFER:
	case GL_ELEMENT_ARRAY_BUFFER:
		glDeleteBuffers(1, &ID);
		break;
	case GL_TEXTURE_2D:
		glDeleteTextures(1, &ID);
		break;
	case GL_VERTEX_ARRAY:
		glDeleteVertexArrays(1, &ID);
		break;
	default:
		break;
	}
}

VAO::VAO() : Buffer(GL_VERTEX_ARRAY) { }

void Buffers::VAO::setVertexCount(GLuint count)
{
	vertexCount = count;
}

VBO::VBO() : Buffer(GL_ARRAY_BUFFER) { }

void Buffers::VBO::setVertexCount(GLuint count)
{
	vertexCount = count;
}

GLuint Buffers::VBO::VertexCount()
{
	return vertexCount;
}

void VAO::EnableAttrib(GLint attribute)
{
	glEnableVertexAttribArray(attribute);
}

void VAO::SetAttrib(GLuint index, GLint size, GLsizei stride, int offset, GLboolean normalize)
{
	glVertexAttribPointer(index, size, DataType, normalize, stride, (void*)offset);
	EnableAttrib(index);	
}

void VAO::Draw(GLenum mode)
{
	if (isBound)
	{
		glDrawArrays(mode, 0, vertexCount);
	}
	else
	{
		std::cout << "Trying to draw unbounded vertex buffer" << std::endl;
	}
}

void VAO::DisableAtrrib(GLint attribute)
{
	glDisableVertexAttribArray(attribute);
}

Buffers::Texture::Texture() : Buffer(GL_TEXTURE_2D) { }

Texture::Texture(std::string type) : Buffer(GL_TEXTURE_2D)
{
	Type = type;
}

void Buffers::Texture::setType(std::string type)
{
	Type = type;
}

void Buffers::Texture::setPath(std::string path)
{
	Path = path;
}

GLuint Buffers::Texture::getID()
{
	return ID;
}

void Texture::Activate(int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	Bind();
}

void Texture::TexData(const char* path, const std::string& directory, bool linear)
{
	std::string filename = std::string(path);

	if (directory.length() > 0)
		filename = directory + '/' + filename;

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		GLenum filteringMin;
		GLenum filteringMag;

		if (linear)
		{
			filteringMag = GL_LINEAR;
			filteringMin = GL_LINEAR_MIPMAP_LINEAR;
		}
		else
		{
			filteringMag = GL_NEAREST;
			filteringMin = GL_NEAREST_MIPMAP_NEAREST;
		}

		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filteringMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filteringMag);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		Width = width;
		Height = height;
		Channels = nrChannels;
	}
	else
	{
		std::cout << "Failed to load texture: \"" << filename << "\"" << std::endl;
	}

	stbi_image_free(data);
}

std::string Buffers::Texture::type()
{
	return Type;
}

std::string Buffers::Texture::path()
{
	return Path;
}

Buffers::EBO::EBO() : Buffers::Buffer(GL_ELEMENT_ARRAY_BUFFER) { }

void Buffers::EBO::Draw(GLuint elements, GLenum mode)
{
	glDrawElements(mode, elements, GL_UNSIGNED_INT, 0);
}
