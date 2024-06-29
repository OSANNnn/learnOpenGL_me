#ifndef BUFFERS_H
#define BUFFERS_H

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glfw3.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


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

	class Texture : public Buffer
	{
	private:
		int Width, Height, Channels;
		bool Clamp = false;
		std::string Type;
		std::string Path;
	public:
		Texture();
		Texture(std::string type);
		void setType(std::string type);
		void setPath(std::string path);
		void setClamp(bool value = true);
		void setRepeat(bool value = true);
		std::string type();
		std::string path();
		GLuint getID();
		void Activate(int index);
		void TexData(const char* path, const std::string& directory = "", bool linear = true);
	};
}
#endif // !BUFFERS_H


