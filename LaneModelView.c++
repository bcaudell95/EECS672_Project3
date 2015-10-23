// TEMPLATE_Subclass.c++

#include "LaneModelView.h"
#include "ShaderIF.h"

const vec3 LaneModelView::size = {39.0, 1.0, 720.0};
const int LaneModelView::numberOfBlocks = 39 + 38;
vec3 LaneModelView::laneColor = { .8, 0.698, 0.501 };
vec3 LaneModelView::black = {0.0, 0.0, 0.0};
vec3 LaneModelView::ka = {.1, .1, .1};

LaneModelView::LaneModelView(float cx, float cy, float cz)
{
	blocks.reserve(numberOfBlocks);
	float yMax = size[1];
	float zMax = size[2];
	for(int i=0;i<numberOfBlocks;i++)
	{
		float x = cx + (i - (i % 2))/2 - (size[0]/2.0);
		if(i % 2 == 0) //board block
		{
			blocks.push_back(new Block(x+.05f, cy+0.0f, cz+0.0f, .90f, 1.0f, 720.0f));
			blocks.back()->setColor(laneColor);
		}
		else					// crack block
		{
			blocks.push_back(new Block(x+.95f, cy+0.0f, cz+0.0f, .1f, 1.0f, 720.0f));
			blocks.back()->setColor(black);
		}
		blocks.back()->setKa(ka);
	}

	//add the pin deck as another block
	blocks.push_back(new Block(cx - size[0]/2, cy, cz+size[2], size[0], 1.0, 40.25));
	blocks.back()->setColor(laneColor);

	//add the pins
	pins = new TenPinsModelView(cx, cy + 1.0, cz + 722.5);
}

LaneModelView::~LaneModelView()
{
	for(int i=0;i<numberOfBlocks;i++)
		delete blocks.at(i);
	delete pins;
}

void LaneModelView::render()
{
	for(int i=0;i<blocks.size();i++)
	{
		blocks.at(i)->render();
	}
	pins->render();
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
