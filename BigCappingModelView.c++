// TEMPLATE_Subclass.c++

#include "BigCappingModelView.h"
#include "ShaderIF.h"

vec3 BigCappingModelView::size = {12.0, 4.0, 760.25};

BigCappingModelView::BigCappingModelView(float cx, float cy, float cz)
: Block(cx - size[0]/2, cy, cz, size[0], size[1], size[2])
{
	origin[0] = cx;
	origin[1] = cx;
	origin[2] = cx;

	vec3 color = {0.8, 0.8, 0.8};
	setColor(color);
}

BigCappingModelView::~BigCappingModelView()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void BigCappingModelView::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = origin[0] - size[0]/2; // xmin  Give real values!
	xyzLimits[1] = origin[0] + size[0]/2;  // xmax         |
	xyzLimits[2] = origin[1]; // ymin         |
	xyzLimits[3] = origin[1] + size[1]; // ymax         |
	xyzLimits[4] = origin[2]; 	// zmin         |
	xyzLimits[5] = origin[2] + size[2]; // zmax        \_/
}
