#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glfw3.h>

namespace Buffers
{
	class Texture
	{
	private:
		unsigned int ID;
		int Width = -1;
		int	Height = -1;
		int	Channels = -1;
		bool IsBound = false;
		bool Clamp = false;
		std::string Type;
		std::string Path;
	public:
		Texture();
		Texture(std::string type);
		void Bind();
		void UnBind();
		void Delete();
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

