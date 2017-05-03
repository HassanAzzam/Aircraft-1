
#include"../middleware/includes/glm/glm.hpp"
#include"../middleware/includes/glm/gtx/transform.hpp"
#include "../middleware/includes/glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Application Manager\ApplicationManager.h"
float xr = 3.02, yr = 3.02, zr = 3.02;   //intial points to move the aircraft
Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	Cleanup();
}

	void Renderer::Initialize()
	{


		
		//since the triangle is not connected to anything else, so the normal is constant on all the vertices.
		//drawing a square.
		size_of_skybox = 10;
		mySquare = std::unique_ptr<Model>(new Model());


		mySquare->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
		mySquare->VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
		mySquare->VertexData.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));

		mySquare->VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
		mySquare->VertexData.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		mySquare->VertexData.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));



		mySquare->UVData.push_back(glm::vec2(0.0f, 0.0f));
		mySquare->UVData.push_back(glm::vec2(1.0f, 0.0f));
		mySquare->UVData.push_back(glm::vec2(0.0f, 1.0f));
		mySquare->UVData.push_back(glm::vec2(1.0f, 1.0f));


		mySquare->Initialize();

		floorM = glm::scale(400.0f, 4.0f, 400.0f)*glm::translate(0.0f, -0.5f, 0.0f)*glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));//glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		
		
		// Create and compile our GLSL program from the shaders
		programID = LoadShaders("SimpleTransformWithColor.vertexshader", "MultiColor.fragmentshader");

		VPID = glGetUniformLocation(programID, "VP");
		ModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
		// Use our shader
		glUseProgram(programID);

		// Camera
		myCamera = std::unique_ptr<FirstPersonCamera>(new FirstPersonCamera());

		//Load AirCraft
		shader1.LoadProgram();
		model3D = new Model3D();
		model3D->LoadFromFile("data/models/obj/Galaxy/galaxy.obj", true);
		model3D->Initialize();
		myCamera->SetPerspectiveProjection(90.0f, 4.0f / 3.0f, 0.1f, 10000000.0f);


		//Load The skybox
		shader.LoadProgram();
		model13D = new Model3D();
		model13D->LoadFromFile("data/models/obj/skybox/Skybox.obj", true);
		model13D->Initialize();
		// Projection matrix : 
		//shader.LoadProgram();
	
		// View matrix :
		//myCamera->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.9f, 1000.0f);
		myCamera->Reset(
			+0.0f, 80.0f, 160.0f,// Camera Position
			+0.0f, 80.0f, 0.0f,// Look at Point
			+0.0f, +1.0f, +0.0f // Up Vector
			);
		//////////////////////////////////////////////////////////////////////////
		std::string Images_names[6];
	
		Images_names[0] = "right.png";
		Images_names[1] = "left.png";
		Images_names[2] = "top.png";
		Images_names[3] = "bottom.png";
		Images_names[4] = "back.png";
		Images_names[5] = "front.png";
		
		t2 = new Texture("data/models/obj/Galaxy/body middle.tga", 1);
		t = new Texture("sand_light.tga", 1);
		
	
}

void Renderer::Draw()
{

	glUseProgram(programID);

	//Aircraft
	shader1.UseProgram();
	glm::mat4 VP1 = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	t2->Bind();
	shader1.BindVPMatrix(&VP1[0][0]);
	model3D->Render(&shader1, glm::rotate(0.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(2.02f, 2.02f, 2.02f))*glm::translate(glm::vec3(xr, yr, zr))); // scaling the aircraft
	
	
	// Skybox
	shader.UseProgram();
	mat4 view = mat4(mat3(myCamera->GetViewMatrix()));                                
	glm::mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	shader.BindVPMatrix(&VP[0][0]);
	model13D->Render(&shader1, scale(100.0f, 100.0f, 100.0f)); // scaling the skybox
	glm::mat4 VP2 = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix()* floorM;
	t->Bind();
	
	
	glUniformMatrix4fv(VPID, 1, GL_FALSE, &VP2[0][0]);
	//glUniformMatrix4fv(VPID, 1, GL_FALSE, &VP1[0][0]);

	mySquare->Draw();

	//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);

	

	//animated


}

void Renderer::Cleanup()
{
	glDeleteProgram(programID);
}

void Renderer::Update(double deltaTime)
{
//	animModel.UpdateExportedAnimation(&animState, deltaTime);


	//animModel.UpdateVertices(&animState);
}

void Renderer::HandleKeyboardInput(int key, int action)
{
	
	glm::vec3 pos = myCamera->GetEyePosition();
	glm::mat4 VP1 = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	t2->Bind();
	shader1.BindVPMatrix(&VP1[0][0]);

	switch (key)
	{
		//Aircraft Movements	
		case GLFW_KEY_W:
		model3D->Render(&shader1, glm::rotate(0.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(2.02f, 2.02f, 2.02f))*glm::translate(glm::vec3(xr, yr, zr++))); 	 // movement directions 
		break;																																				 	 // movement directions
																																							 	 // movement directions
		case GLFW_KEY_S:																																	 	 // movement directions
		model3D->Render(&shader1, glm::rotate(0.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(2.02f, 2.02f, 2.02f))*glm::translate(glm::vec3(xr, yr, zr--))); 	 // movement directions
		break;																																				 	 // movement directions
																																							 	 // movement directions
		case GLFW_KEY_D:																																	 	 // movement directions
		model3D->Render(&shader1, glm::rotate(0.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(2.02f, 2.02f, 2.02f))*glm::translate(glm::vec3(xr++, yr, zr))); 	 // movement directions
		break;																																				 	 // movement directions
																																							 	 // movement directions
		case GLFW_KEY_A:																																	 	 // movement directions
		model3D->Render(&shader1, glm::rotate(0.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(2.02f, 2.02f, 2.02f))*glm::translate(glm::vec3(xr--, yr, zr))); 	 // movement directions
		break;																																				 	 // movement directions
																																							 	 // movement directions
		case GLFW_KEY_X:																																	 	 // movement directions
		model3D->Render(&shader1, glm::rotate(0.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(2.02f, 2.02f, 2.02f))*glm::translate(glm::vec3(xr, yr++, zr))); 	 // movement directions
		break;																																				 	 // movement directions
																																							 	 // movement directions
		case GLFW_KEY_Z:
		if (yr > -5.0)
		{
			model3D->Render(&shader1, glm::rotate(0.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(2.02f, 2.02f, 2.02f))*glm::translate(glm::vec3(xr, yr--, zr)));   // movement directions
		}
		break;

		//Camera Movements
		//Moving forward
		case GLFW_KEY_UP:
			pos.z += -0.5;
			if (pos.z > -100.0)
			{
				myCamera->Walk(0.5);
			}
			break;

			//Moving backword
		case GLFW_KEY_DOWN:
			pos.z += 0.5;
			if (pos.z > -100)
			{
				myCamera->Walk(-0.5);
			}
			break;

		// Moving right  --Finished
		case GLFW_KEY_RIGHT:
		pos.x += 0.5;
		if ((pos.x > -100))
		{
			myCamera->Strafe(0.5);
		}
		break;

		// Moving left  --Finished
		case GLFW_KEY_LEFT:
		pos.x += -1.0;
		if (pos.x < 90)
		{
			myCamera->Strafe(-1.0);
		}
		break;

		// Moving up  --Finished
		case GLFW_KEY_SPACE:
		case GLFW_KEY_R:
		pos.y += 0.5;
		if ((pos.y > -100 && pos.y < 500))
		{
			myCamera->Fly(0.5);
		}
		break;

		// Moving down  --Finished
		case GLFW_KEY_LEFT_CONTROL:
		case GLFW_KEY_F:
		pos.y += -0.5;
		if (pos.y >= -2.0)
		{
			myCamera->Fly(-1.0);
		}
		break;


		case GLFW_KEY_I:
			myCamera->Pitch(0.1);
			break;

		case GLFW_KEY_K:
			myCamera->Pitch(-0.1);
			break;

		case GLFW_KEY_L:
			myCamera->Yaw(-0.1);
			break;

		case GLFW_KEY_J:
			myCamera->Yaw(0.1);
			break;

		case GLFW_KEY_O:
			myCamera->Roll(-0.1);
			break;

		case GLFW_KEY_U:
			myCamera->Roll(0.1);
			break;

		default:
			break;
		}

		myCamera->UpdateViewMatrix();

}

void Renderer::HandleMouse(double deltaX, double deltaY)
{
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
	myCamera->UpdateViewMatrix();
}