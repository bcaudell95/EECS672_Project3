// TEMPLATE_Subclass.h

#ifndef PAIR_MODELVIEW_H
#define PAIR_MODELVIEW_H

#include "LaneModelView.h"
#include "SmallCappingModelView.h"
#include "BigCappingModelView.h"

class PairModelView : public ModelViewWithPhongLighting
{
public:
	PairModelView(float cx, float cy, float cz, bool enableLeftSmallCapping = true);
	virtual ~PairModelView();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	vec3 origin;

	LaneModelView* leftLane;
	LaneModelView* rightLane;
	SmallCappingModelView* leftSmallCapping;
	SmallCappingModelView* rightSmallCapping;
	BigCappingModelView* middleCapping;
};

#endif
