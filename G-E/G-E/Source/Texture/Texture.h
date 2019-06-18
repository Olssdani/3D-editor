#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>
#include <string>
#include <iostream>
class Texture
{
public:
	Texture()
	{

	}

	Texture(const char* url)
	{
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Load data from file
		unsigned char *data = loadImage(url);
		

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	const unsigned int textureId() { return texture; };

	void bindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}



private:
	int width, height, nrChannels;
	
	unsigned int texture;

	unsigned char* loadImage(const char* url)
	{
		return stbi_load(url, &width, &height, &nrChannels, 0);
	}
};


