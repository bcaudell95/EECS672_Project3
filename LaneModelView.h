// TEMPLATE_Subclass.h

#ifndef LANE_MODELVIEW_H
#define LANE_MODELVIEW_H

#include "Block.h"
#include "TenPinsModelView.h"
#include "GutterModelView.h"
#include <vector>

class LaneModelView : public ModelViewWithPhongLighting
{
public:
	LaneModelView(float cx, float cy, float cz); // coordinates for the center of the foul line
	virtual ~LaneModelView();

	void render();
	void getMCBoundingBox(double* xyzLimits) const;
private:
	vec3 origin;
	const static vec3 size;
	const static int numberOfBlocks;
	static vec3 ka;
	static vec3 laneColor;
	static vec3 black;

	std::vector<Block*> blocks;
	TenPinsModelView* pins;
	GutterModelView* gutters[2];

	vec3 position;
};

#endif
