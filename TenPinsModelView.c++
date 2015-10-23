// TEMPLATE_Subclass.c++

#include "TenPinsModelView.h"
#include "ShaderIF.h"

vec3 TenPinsModelView::centers[] =
{
	{0,0,0},
	{-6,0,10.392},
	{6,0,10.392},
	{-12,0,20.784},
	{0,0,20.784},
	{12,0,20.784},
	{-18,0,31.177},
	{-6,0,31.177},
	{6,0,31.177},
	{18,0,31.177},
};

TenPinsModelView::TenPinsModelView(float headCx, float headCy, float headCz)
{
	PinModelView::initVertexGroups();
	PinModelView::initBaseCoordinates();

	for(int i=0;i<10;i++)
	{
		float x = headCx + centers[i][0];
		float y = headCy + centers[i][1];
		float z = headCz + centers[i][2];
		pins.push_back(new PinModelView(x, y, z));
	}
}

TenPinsModelView::~TenPinsModelView()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void TenPinsModelView::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = -21.0; // xmin  Give real values!
	xyzLimits[1] = 21.0;  // xmax         |
	xyzLimits[2] = 0; // ymin         |
	xyzLimits[3] = 15; // ymax         |
	xyzLimits[4] = 0; // zmin         |
	xyzLimits[5] = 35; // zmax        \_/
}

void TenPinsModelView::render()
{
	for(int i=0;i<10;i++)
		pins.at(i)->render();
}
