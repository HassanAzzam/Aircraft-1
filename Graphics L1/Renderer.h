#ifndef Renderer_h__
#define Renderer_h__

#include "../middleware/includes/gl/glew.h"
#include "../middleware/includes/gl/glfw3.h"

#include "Shaders/shader.hpp"
#include "Model.h"
#include <memory>
#include "FirstPersonCamera.h"
#include "Model3D.h"
#include "ShaderProgram.h"
#include <string.h>
#include <iostream>

class Renderer
{
	
	GLuint programID;
	ShaderProgram shader;
	//ShaderProgram shader;
	//Model3D* model3D;
	GLuint VPID;
	GLuint ModelMatrixID;
	Model3D* model13D;  //skybox
	Model3D* model3D; //Aircraft
	std::unique_ptr<Model> mySquare;
	std::unique_ptr<FirstPersonCamera> myCamera;
	Texture *t, *t2;
	glm::mat4 floorM;
	float size_of_skybox;
	

public:
	Renderer();
	~Renderer();

	void Initialize();
	void Draw();
	void HandleKeyboardInput(int key, int action);
	void HandleMouse(double deltaX, double deltaY);
	void Update(double deltaTime);
	void Cleanup();
};

#endif 
