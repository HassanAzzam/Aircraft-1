
#include"../middleware/includes/glm/glm.hpp"
#include"../middleware/includes/glm/gtx/transform.hpp"
#include "../middleware/includes/glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Application Manager\ApplicationManager.h"

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
	size_of_skybox = 1000;
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
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("SimpleTransformWithColor.vertexshader", "MultiColor.fragmentshader");

	VPID = glGetUniformLocation(programID, "VP");
	ModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
	// Use our shader
	glUseProgram(programID);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Camera
	myCamera = std::unique_ptr<FirstPersonCamera>(new FirstPersonCamera());

	//C:\Users\khairy\Desktop\Universty\Third year\Second Term\Graphics\Project\Project Template\Graphics L1\data\models\obj\skybox



	shader.LoadProgram();
	model13D = new Model3D();
	model13D->LoadFromFile("data/models/obj/skybox/Skybox.obj", true);
	model13D->Initialize();
	// Projection matrix : 
	//shader.LoadProgram();
	model3D = new Model3D();
	model3D->LoadFromFile("data/models/obj/Galaxy/galaxy.obj", true);
	model3D->Initialize();
	myCamera->SetPerspectiveProjection(90.0f, 4.0f / 3.0f, 0.1f, 10000000.0f);

	// View matrix : 
	myCamera->Reset(
		+0.0f, +0.0f, +5.0f,// Camera Position
		+0.0f, +0.0f, +0.0f,// Look at Point
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
	t = new Texture(Images_names, 0);
	t2 = new Texture("arrakisday_dn.tga", 1);

	//animated
	/*animModel.LoadModel("data/models/md2/enemy/robot.md2");

	animState = animModel.StartAnimation(animType_t::RUN);
	animatedModelShader.LoadProgram();
	animModelMatrix = glm::translate(glm::vec3(0.0, 0.0, 0))*glm::rotate(-90.0f, glm::vec3(1, 0, 0))*glm::scale(glm::vec3(0.03f, 0.03f, 0.03f));*/
}
void Renderer::Draw()
{

	glUseProgram(programID);

	/*t->Bind();
	glm::mat4 view = glm::mat4(glm::mat3(myCamera->GetViewMatrix()));
	glm::mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	glUniformMatrix4fv(VPID, 1, GL_FALSE, &VP[0][0]);
	mySquare->Draw();*/

	shader.UseProgram();
	mat4 view = mat4(mat3(myCamera->GetViewMatrix()));
	glm::mat4 VP = myCamera->GetProjectionMatrix()*myCamera->GetViewMatrix();
	shader.BindVPMatrix(&VP[0][0]);

	model13D->Render(&shader, scale(100.0f, 100.0f, 100.0f)); // scaling the skybox
	mat4 view1 = mat4(mat3(myCamera->GetViewMatrix()));
	glm::mat4 VP1 = myCamera->GetProjectionMatrix()*myCamera->GetViewMatrix();
	shader.BindVPMatrix(&VP1[0][0]);
	model3D->Render(&shader, scale(2.0f, 2.0f, 2.0f));

	t2->Bind();
	glm::mat4 VP2 = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix()*floorM;
	glUniformMatrix4fv(VPID, 1, GL_FALSE, &VP2[0][0]);
	//drawcrosshair();
	mySquare->Draw();

	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);

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
	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		myCamera->Walk(1);
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		myCamera->Walk(-1);
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		myCamera->Strafe(0.4);
		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		myCamera->Strafe(-0.4);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		myCamera->Fly(0.4);
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		myCamera->Fly(-0.4);
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