// TEMPLATE_Subclass.c++

#include "PairModelView.h"
#include "ShaderIF.h"

PairModelView::PairModelView(float cx, float cy, float cz, bool enableLeftSmallCapping)
{
	origin[0] = cx;
	origin[1] = cy;
	origin[2] = cz;

	leftLane = new LaneModelView(cx + 34.75, cy, cz);
	rightLane = new LaneModelView(cx - 34.75, cy, cz);
	if(enableLeftSmallCapping)
		leftSmallCapping = new SmallCappingModelView(cx + 64.5, cy, cz);
	else
		leftSmallCapping = NULL;
	rightSmallCapping = new SmallCappingModelView(cx - 64.5, cy, cz);
	middleCapping = new BigCappingModelView(cx, cy, cz);
}

PairModelView::~PairModelView()
{
	delete leftLane;
	delete rightLane;
	delete leftSmallCapping;
	delete rightSmallCapping;
	delete middleCapping;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void PairModelView::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = origin[0] - 65.5; // xmin  Give real values!
	xyzLimits[1] = origin[0] + 65.5;  // xmax         |
	xyzLimits[2] = origin[1]; // ymin         |
	xyzLimits[3] = origin[1] + 4.0; // ymax         |
	xyzLimits[4] = origin[2]; // zmin         |
	xyzLimits[5] = origin[2] + 760.25; // zmax        \_/
}

void PairModelView::render()
{
	leftLane->render();
	rightLane->render();
	if(leftSmallCapping!=NULL)
		leftSmallCapping->render();
	rightSmallCapping->render();
	middleCapping->render();
}
