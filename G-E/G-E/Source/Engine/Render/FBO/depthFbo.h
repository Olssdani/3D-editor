#pragma once
#include "fbo.h"

class depthFbo : public fbo {
	depthFbo(const uint32_t width, const uint32_t height)
		: fbo() {
		glGenTextures(1, &fboObject);
		glBindTexture(GL_TEXTURE_2D, fboObject);
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 GL_DEPTH_COMPONENT,
					 width,
					 height,
					 0,
					 GL_DEPTH_COMPONENT,
					 GL_FLOAT,
					 NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, fboObject, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
};
