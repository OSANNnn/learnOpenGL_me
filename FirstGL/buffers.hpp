#ifndef BUFFERS_H
#define BUFFERS_H

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glfw3.h>


namespace Buffers
{
	class Buffer
	{
	protected:
		GLuint ID;
		GLenum DataType;
		GLenum BufferType;
		GLboolean isBound;

		Buffer(GLenum bufferT = 0, GLenum dataT = GL_FLOAT);
	public:
		virtual void Bind();
		virtual void Data(GLvoid* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
		virtual void Draw();
		virtual void UnBind();
		virtual void Delete();
	
	};

	class VAO : public Buffer
	{
	private:
		GLuint vertexCount;
	public:
		VAO();
		void setVertexCount(GLuint count);
		void EnableAttrib(GLint attribute);
		void SetAttrib(GLuint index, GLint size, GLsizei stride, int offset, GLboolean normalize = GL_FALSE);
		void Draw(GLenum mode = GL_TRIANGLES);
		void DisableAtrrib(GLint attribute);
	};

	class VBO : public Buffer
	{
	private:
		GLuint vertexCount;
	public:
		VBO();
		void setVertexCount(GLuint count);
		GLuint VertexCount();
	};

	class EBO : public Buffer
	{
	public:
		EBO();
		void Draw(GLenum mode = GL_TRIANGLES);
	};

	class Texture : public Buffer
	{
	private:
		int Width, Height, Channels;
		std::string _Type;
	public:
		Texture(std::string type);
		GLuint getID();
		void Activate(int index);
		void TexData(const char* filename, bool linear = true);
		std::string Type();
	};
}
#endif // !BUFFERS_H


