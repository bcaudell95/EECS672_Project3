#include "DynamicController.h"

DynamicController::DynamicController(const std::string& windowTitle, int rcFlags)
: GLFWController(windowTitle, rcFlags)
{
  glfwSetKeyCallback(theWindow, keyboardCB);

}
DynamicController::~DynamicController() {



}


void DynamicController::keyboardCB(GLFWwindow* window, int key, int scanCode, int action, int mods) {

  if (curController != NULL)
	{
		DynamicController* theC = dynamic_cast<DynamicController*>(curController);
		if (key == GLFW_KEY_P)
			theC->sendCommandToModels('P', theC->lastPixelPosX, theC->lastPixelPosY);
    else if (key == GLFW_KEY_O)
			theC->sendCommandToModels('O', theC->lastPixelPosX, theC->lastPixelPosY);
    else if (key == GLFW_KEY_Q)
			theC->sendCommandToModels('Q', theC->lastPixelPosX, theC->lastPixelPosY);
    GLFWController::keyboardCB(window, key, scanCode, action, mods);
	}
}

void DynamicController::handleAsciiChar(unsigned char theChar, int x, int y)
{

}

void DynamicController::sendCommandToModels(unsigned char command, double x, double y)
{
  for(int i=0;i<getNumModels();i++)
  {
    getModel(i)->handleCommand(command, x, y);
  }
}
