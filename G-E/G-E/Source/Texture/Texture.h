//!  Texture class
/*! 
 *  Class for handling the texture for an object. The class can read a file and load the image into the gpu.
 */
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <string>
#include <iostream>
class Texture
{
public:
	/**
	   * Default constructor
	   */
	Texture(){
		width = height = nrChannels =0;
		empty = true;
	}

	/**
	   * Constructor for the texture unit
	   * @param url is a pointer to a char of the link to the image.
	   * @param s a constant character pointer.
	   */
	Texture(const char* url){
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char *data = loadImage(url);
		
		if (data){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			empty = false;
		}
		else{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
	/**
   * Fucntion for returning the texture ID
   * \return The texture ID.
   */
	const unsigned int textureId() { 
		return texture; 
	};
	/**
   * Binds the texture
   */
	void bindTexture(){
		glBindTexture(GL_TEXTURE_2D, texture);
	}

private:
	//Variables
	int width, height, nrChannels;
	bool empty;
	unsigned int texture;

	/**
   * Load the an image through the stbi library
   * @param url is a pointer to a char of the link to the image.
   * \return is a pointer to an usigned char where all data is stored.
   */
	unsigned char* loadImage(const char* url){
		return stbi_load(url, &width, &height, &nrChannels, 0);
	}
};


