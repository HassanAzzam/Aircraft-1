#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{

public:
	/*unsigned*/ int width, height;
	int numComponents;
	unsigned char * data;
    GLenum TextureTarget;
	int texUnit;
    void Bind(){
        glActiveTexture(texUnit);
        glBindTexture(TextureTarget, m_texture);
    }
    Texture(const std::string &fileName, int texUnit_, GLenum TextureTarget_){
        TextureTarget = TextureTarget_;
        unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
        texUnit = texUnit_;
        if(data == NULL)
            std::cout<< "Unable to load texture: " << fileName << std::endl;
        else std::cout<< "Loaded texture: " << fileName << std::endl << "Width: " << width << ", Height: " << height << std::endl;
        glActiveTexture(texUnit);
        glGenTextures(1, &m_texture);
        glBindTexture(TextureTarget, m_texture);
        
        glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(TextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexImage2D(TextureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(TextureTarget, 0);
        
        stbi_image_free(data);
    }
    virtual ~Texture(){
        glDeleteTextures(1, &m_texture);
    }
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}
	GLuint m_texture;
};


//GLuint loadBMP_custom(const char * imagepath);
