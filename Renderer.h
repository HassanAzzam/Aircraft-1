#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "shader.hpp"
#include "Model.hpp"
#pragma once

#ifdef __APPLE__
#define VTXSHADER "/Users/HassanAzzam/Desktop/graphics/graphics/SimpleVertexShader.vertexshader"
#define FRGSHADER "/Users/HassanAzzam/Desktop/graphics/graphics/SimpleFragmentShader.fragmentshader"
#else
#define VTXSHADER "SimpleVertexShader.vertexshader"
#define FRGSHADER "SimpleFragmentShader.fragmentshader"
#endif

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
