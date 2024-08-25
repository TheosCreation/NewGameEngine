#include "Framebuffer.h"
#include <glew.h>
#include <glfw3.h>

// Constructor: Initialize the framebuffer and create a texture
Framebuffer::Framebuffer(Rect _windowSize)
{
    // Generate and bind the framebuffer
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // Generate and bind the texture
    glGenTextures(1, &RenderTexture);
    glBindTexture(GL_TEXTURE_2D, RenderTexture);

    // Define the texture parameters
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _windowSize.width, _windowSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Attach the texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderTexture, 0);

    // Generate and bind the renderbuffer for depth and stencil
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _windowSize.width, _windowSize.height);

    // Attach the renderbuffer to the framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    // Check if the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Framebuffer is not complete!" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

// Destructor: Clean up resources
Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &RenderTexture);
    glDeleteRenderbuffers(1, &RBO);
}

// Bind the framebuffer
void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

// Unbind the framebuffer
void Framebuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
