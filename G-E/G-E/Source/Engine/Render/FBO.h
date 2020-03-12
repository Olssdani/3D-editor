#pragma once
#include <glad/glad.h>
#include <iostream>

class fbo {
private:
	unsigned int fboObject;
	unsigned int texture;
	unsigned int rbo;

public:
	fbo(unsigned int width, unsigned int height) {
		glGenFramebuffers(1, &fboObject);
		glBindFramebuffer(GL_FRAMEBUFFER, fboObject);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(
			GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	~fbo() {
		glDeleteFramebuffers(1, &fboObject);
	}

	void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, fboObject);
	}

	void unBind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	unsigned int get() {
		return fboObject;
	}

	unsigned int getTexture() {
		return texture;
	}
};
