// TEMPLATE_Subclass.h

#ifndef LANE_MODELVIEW_H
#define LANE_MODELVIEW_H

#include "Block.h"
#include <vector>

class LaneModelView : public ModelViewWithPhongLighting
{
public:
	LaneModelView();
	virtual ~LaneModelView();

	void render();
	void getMCBoundingBox(double* xyzLimits) const;
private:
	const static vec3 size;
	const static int numberOfBlocks;
	static vec3 laneColor;
	static vec3 black;

	std::vector<Block*> blocks;

	vec3 position;
};

#endif
