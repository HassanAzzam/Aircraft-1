#include "Renderer.h"

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
    
    Skybox.ModelTexture = new Texture("/Users/HassanAzzam/Desktop/graphics/graphics/Texture/skybox.jpg",1,GL_TEXTURE_CUBE_MAP);
    Skybox.Initialize(1,1,1);
    
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f  , 0.1f, 100.0f);
    glm::mat4 Camera = glm::lookAt(
            glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
                            
    ModelMatrix = Projection * Camera;

	programID = LoadShaders(VTXSHADER, FRGSHADER);
	MatrixID = glGetUniformLocation(programID, "ModelMatrix");
	glUseProgram(programID);
}

void Renderer::Draw()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programID);
    
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    Skybox.Draw();
		
}

void Renderer::Cleanup()
{
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID); //the one we didn't used (will be discussed later)
    glDeleteProgram(programID);
}
