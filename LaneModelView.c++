// TEMPLATE_Subclass.c++

#include "LaneModelView.h"
#include "ShaderIF.h"

const vec3 LaneModelView::size = {39.0, 1.0, 720.0};
const int LaneModelView::numberOfBlocks = 39 + 38;
vec3 LaneModelView::laneColor = { .8, 0.698, 0.501 };
vec3 LaneModelView::black = {0.0, 0.0, 0.0};
vec3 LaneModelView::ka = {.1, .1, .1};

LaneModelView::LaneModelView()
{
	blocks.reserve(numberOfBlocks);
	float yMax = size[1];
	float zMax = size[2];
	for(int i=0;i<numberOfBlocks;i++)
	{
		float x = (i - (i % 2))/2;
		if(i % 2 == 0) //board block
		{
			blocks.push_back(new Block(x+.05f, 0.0f, 0.0f, .90f, 1.0f, 720.0f));
			blocks.back()->setColor(laneColor);
		}
		else					// crack block
		{
			blocks.push_back(new Block(x+.95f, 0.0f, 0.0f, .1f, 1.0f, 720.0f));
			blocks.back()->setColor(black);
		}
		blocks.back()->setKa(ka);
	}
}

LaneModelView::~LaneModelView()
{
	for(int i=0;i<numberOfBlocks;i++)
		delete blocks.at(i);
}

void LaneModelView::render()
{
	for(int i=0;i<numberOfBlocks;i++)
	{
		blocks.at(i)->render();
	}

}

void LaneModelView::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = 0.0;
	xyzLimits[1] = 0.0;
	xyzLimits[2] = 0.0;
	xyzLimits[3] = size[0];
	xyzLimits[4] = size[1];
	xyzLimits[5] = size[2];
}
