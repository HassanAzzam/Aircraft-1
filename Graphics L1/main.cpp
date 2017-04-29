#include "Application Manager/ApplicationManager.h"

int main(void)
{
	std::unique_ptr<ApplicationManager> appManager (new ApplicationManager());
	if(appManager->InitalizeApplication(800,600) == true)
	{
		appManager->StartMainLoop();
		appManager->CloseApplication();
	}
}


