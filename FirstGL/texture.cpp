#include "texture.hpp"

#include <stb_image.h>

Buffers::Texture::Texture()
{
	glGenTextures(1, &ID);
}

Buffers::Texture::Texture(std::string type)
{
	glGenTextures(1, &ID);
	Type = type;
}

void Buffers::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
	IsBound = true;
}

void Buffers::Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	IsBound = false;
}

void Buffers::Texture::Delete()
{
	glDeleteTextures(1, &ID);
	IsBound = false;
}

void Buffers::Texture::setType(std::string type)
{
	Type = type;
}

void Buffers::Texture::setPath(std::string path)
{
	Path = path;
}

void Buffers::Texture::setClamp(bool value)
{
	Clamp = value;
	Bind();
	if (Clamp)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	UnBind();
}

void Buffers::Texture::setRepeat(bool value)
{
	setClamp(!value);
}

std::string Buffers::Texture::type()
{
	return Type;
}

std::string Buffers::Texture::path()
{
	return Path;
}

GLuint Buffers::Texture::getID()
{
	return ID;
}

void Buffers::Texture::Activate(int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	Bind();
}

void Buffers::Texture::TexData(const char* path, const std::string& directory, bool linear)
{
	std::string filename = std::string(path);

	if (directory.length() > 0)
		filename = directory + '/' + filename;

	int width, height, nrChannels;
	std::cout << "Loading texture data: \"" << filename << '"';
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);


	if (data)
	{
		GLenum format = GL_RGB;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		GLenum filteringMin;
		GLenum filteringMag;
		GLenum repeat;

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
		if (Clamp)
		{
			repeat = GL_CLAMP_TO_EDGE;
		}
		else
		{
			repeat = GL_REPEAT;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filteringMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filteringMag);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		Width = width;
		Height = height;
		Channels = nrChannels;
	std::cout << "... LOADED!" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture: \"" << filename << "\"" << std::endl;
	}
	stbi_image_free(data);
}

//---------------------------------------------------------------------------cube map

Buffers::CubeMap::CubeMap(std::vector<std::string> paths)
{
	int width = 0, height = 0, channels = 0;
	unsigned char* data = NULL;
	int i = 0;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	for (auto& path : paths)
	{
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			i++;
		}
		else
		{
			std::cout << "FAILED TO LOAD CUBEMAP TEXTURE: " << path << std::endl;
			stbi_image_free(data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Buffers::CubeMap::Bind()
{
	IsBound = true;
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void Buffers::CubeMap::UnBind()
{
	IsBound = false;
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Buffers::CubeMap::Delete()
{
	glDeleteTextures(1, &ID);
}

GLuint Buffers::CubeMap::getID()
{
	return ID;
}

void Buffers::CubeMap::Activate(int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	Bind();
}
