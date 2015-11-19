#include "DynamicController.h"

DynamicController::DynamicController(const std::string& windowTitle, int rcFlags)
: GLFWController(windowTitle, rcFlags)
{

  isLeftMouseButtonPressed = false;
  lastMouseX = 0;
  lastMouseY = 0;
}
DynamicController::~DynamicController() {



}


void DynamicController::handleAsciiChar(unsigned char theChar, int x, int y)
{
  if (theChar=='p' || theChar=='q' || theChar=='o')
  {
    for(int i=0;i<getNumModels();i++)
    {
      getModel(i)->handleCommand(theChar, x, y);
    }
  }
}


void DynamicController::handleMouseButton(MouseButton button, bool pressed, int x, int y, int mods)
{
  isLeftMouseButtonPressed = (button == LEFT_BUTTON && pressed);
  if (isLeftMouseButtonPressed)
  {
    lastMouseX = x;
    lastMouseY = y;
  }
}

void DynamicController::handleMouseMotion(int x, int y)
{
  if (isLeftMouseButtonPressed)
  {
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;
    lastMouseX = x;
    lastMouseY = y;

    //TODO: apply rotation
    ModelView::addToGlobalRotationDegrees(dx/3.0, dy/3.0, 0);
  }
}

void DynamicController::handleScroll(bool up)
{
  ModelView::addToGlobalZoom(up ? .90 : 1.10);
}
