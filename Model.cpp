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
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
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
    
    
    
    
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));

    
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));

    
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));
    UVData.push_back(glm::vec2(0.0f,256.0f));

    
    
    glGenBuffers(1, &UVDataBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, UVDataBufferID);
    glBufferData(GL_ARRAY_BUFFER, UVData.size() * sizeof(glm::vec2) , &UVData[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    }

void Model::Draw()
{
    Texture->Bind();
    glDrawArrays(GL_TRIANGLES,0,12*3);
    
}

void Model::Cleanup()
{
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID); //the one we didn't used (will be discussed later)
    glDeleteProgram(programID);
}
