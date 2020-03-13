#pragma once
#include <glad/glad.h>
#include <iostream>

class fbo {
protected:
	uint32_t fboObject;
	uint32_t texture;

public:
	fbo() {
		glGenFramebuffers(1, &fboObject);
		glBindFramebuffer(GL_FRAMEBUFFER, fboObject);
	}

	virtual ~fbo() = 0 {
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
