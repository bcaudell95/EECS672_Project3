#include "DynamicController.h"

DynamicController::DynamicController(const std::string& windowTitle, int rcFlags)
: GLFWController(windowTitle, rcFlags)
{
  glfwSetKeyCallback(theWindow, keyboardCB);

}
DynamicController::~DynamicController() {



}


void DynamicController::keyboardCB(GLFWwindow* window, int key, int scanCode, int action, int mods) {

  // if (curController != NULL)
	// {
	// 	DynamicController* theC = dynamic_cast<DynamicController*>(curController);
	// 	if (key == GLFW_KEY_P)
	// 		std::cout << "P received!\n";
  //   else if (key == GLFW_KEY_O)
	// 		std::cout << "O received!\n";
  //   else if (key == GLFW_KEY_Q)
  // 		std::cout << "Q received!\n";
	// }
  //GLFWController::keyboardCB(window, key, scanCode, action, mods);
}

void DynamicController::handleAsciiChar(unsigned char theChar, int x, int y)
{

}
