#include "Model.hpp"

Model::Model()
{
    
}

Model::~Model()
{
    Cleanup();
}

void Model::Initialize(int Sx, int Sy, int Sz)
{
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    GLfloat verts[] = {
        //Left
        
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        
        //Down
        
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        
        //Right
        
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
        
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        
        //Up
        
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        
        //Top
        
        -1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
        
        -1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        
        //Bottom
        
        -1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        
        -1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        
        
        
    };
    for(int i=0; i<12*3*3; i++)
    {
        if(i%3==0)
            verts[i]*=Sx;
        else if(i%3==1)
            verts[i]*=Sy;
        else if(i%3==2)
            verts[i]*=Sz;
    }
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts,GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    
    
    float quarter = 256.0f;
    
    UVData.push_back(glm::vec2(quarter*1,quarter*1));
    UVData.push_back(glm::vec2(quarter*0,quarter*2));
    UVData.push_back(glm::vec2(quarter*1,quarter*2));
    
    UVData.push_back(glm::vec2(quarter*1,quarter*1));
    UVData.push_back(glm::vec2(quarter*0,quarter*2));
    UVData.push_back(glm::vec2(quarter*0,quarter*1));
    
    /////
    
    UVData.push_back(glm::vec2(quarter*1,quarter*1));
    UVData.push_back(glm::vec2(quarter*2,quarter*2));
    UVData.push_back(glm::vec2(quarter*1,quarter*2));
    
    UVData.push_back(glm::vec2(quarter*1,quarter*1));
    UVData.push_back(glm::vec2(quarter*2,quarter*2));
    UVData.push_back(glm::vec2(quarter*2,quarter*1));
    
    /////
    
    UVData.push_back(glm::vec2(quarter*2,quarter*1));
    UVData.push_back(glm::vec2(quarter*3,quarter*2));
    UVData.push_back(glm::vec2(quarter*2,quarter*2));
    
    UVData.push_back(glm::vec2(quarter*2,quarter*1));
    UVData.push_back(glm::vec2(quarter*3,quarter*2));
    UVData.push_back(glm::vec2(quarter*3,quarter*1));
    
    /////
    
    UVData.push_back(glm::vec2(quarter*3,quarter*1));
    UVData.push_back(glm::vec2(quarter*4,quarter*2));
    UVData.push_back(glm::vec2(quarter*3,quarter*2));
    
    UVData.push_back(glm::vec2(quarter*3,quarter*1));
    UVData.push_back(glm::vec2(quarter*4,quarter*2));
    UVData.push_back(glm::vec2(quarter*4,quarter*1));
    
    /////
    
    UVData.push_back(glm::vec2(quarter*1,quarter*0));
    UVData.push_back(glm::vec2(quarter*2,quarter*1));
    UVData.push_back(glm::vec2(quarter*1,quarter*1));
    
    UVData.push_back(glm::vec2(quarter*1,quarter*0));
    UVData.push_back(glm::vec2(quarter*2,quarter*1));
    UVData.push_back(glm::vec2(quarter*2,quarter*0));
    
    /////
    
    UVData.push_back(glm::vec2(quarter*1,quarter*2));
    UVData.push_back(glm::vec2(quarter*2,quarter*3));
    UVData.push_back(glm::vec2(quarter*1,quarter*3));
    
    UVData.push_back(glm::vec2(quarter*1,quarter*2));
    UVData.push_back(glm::vec2(quarter*2,quarter*3));
    UVData.push_back(glm::vec2(quarter*2,quarter*2));
    
    /////

    
    glGenBuffers(1, &UVDataBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, UVDataBufferID);
    glBufferData(GL_ARRAY_BUFFER, UVData.size() * sizeof(glm::vec2) , &UVData[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Model::Draw()
{
    ModelTexture->Bind();
    glDrawArrays(GL_TRIANGLES,0,12*3);
    
}

void Model::Cleanup()
{
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID); //the one we didn't used (will be discussed later)
    glDeleteProgram(programID);
}
