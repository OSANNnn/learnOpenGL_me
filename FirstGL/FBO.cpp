#include "FBO.hpp"
#include <iostream>

void FBO::AttachRBO(const unsigned int width, const unsigned int height)
{
    hasRBO = true;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

FBO::FBO()
{
    glGenFramebuffers(1, &ID);
}

FBO::FBO(const unsigned int width, const unsigned int height)
{
    glGenFramebuffers(1, &ID);
    Bind();
    CreateColorBuffer(width, height);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER::INCOMPLETE" << std::endl;
    }
    UnBind();
}

void FBO::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void FBO::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Delete()
{
    glDeleteFramebuffers(1, &ID);
    if (hasColor)
    {
        glDeleteTextures(1, &TexID);
    }
    if (hasRBO)
    {
        glDeleteRenderbuffers(1, &RBO);
    }
}

void FBO::CreateColorBuffer(const unsigned int width, const unsigned int height)
{
    hasColor = true;
    glGenTextures(1, &TexID);
    glBindTexture(GL_TEXTURE_2D, TexID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TexID, 0);
    AttachRBO(width, height);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void FBO::Render(Shader& shaderProgram)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.Use();
    glBindTexture(GL_TEXTURE_2D, TexID);
    frame.Draw();
    glBindTexture(GL_TEXTURE_2D, 0);
}
