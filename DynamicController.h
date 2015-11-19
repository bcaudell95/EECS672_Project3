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
	virtual void handleAsciiChar(unsigned char theChar, int x, int y);
	virtual void handleMouseButton(MouseButton button, bool pressed, int x, int y, int mods);
	virtual void handleMouseMotion(int x, int y);
		virtual void handleScroll(bool up);

	bool isLeftMouseButtonPressed;
	int lastMouseX, lastMouseY;
};

#endif
