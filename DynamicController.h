#ifndef DYNAMIC_CONTROLLER_H
#define DYNAMIC_CONTROLLER_H

#include "GLFWController.h"
#include "ModelViewWithPhongLighting.h"


class DynamicController : public GLFWController
{
public:
	DynamicController(const std::string& windowTitle, int rcFlags = 0);
	virtual ~DynamicController();

private:
  static void keyboardCB(GLFWwindow* window, int key, int scanCode, int action, int mods);
  virtual void handleAsciiChar(unsigned char theChar, int x, int y);
	void sendCommandToModels(unsigned char command, double x, double y);
};

#endif
