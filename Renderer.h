#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "shader.hpp"
#include "Model.hpp"
#include "Texture/texture.h"
#include "Texture/Texture Loader/stb_image.h"
#pragma once

#define SKYBOX_TEX "Texture/skybox.jpg"

class Renderer
{
    GLuint vertexArrayID;
    GLuint vertexBufferID;
    glm::mat4 ModelMatrix;
    GLuint MatrixID;
    GLuint programID;
    
    Model Skybox;
    
public:
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
    void Cleanup();
};
