// TEMPLATE_Subclass.h

#ifndef SMAL_CAPPING_MODELVIEW_H
#define SMAL_CAPPING_MODELVIEW_H

#include "Block.h"
#include "SmallCappingModelView.h"

class SmallCappingModelView : public Block
{
public:
	static vec3 size;

	SmallCappingModelView(float cx, float cy, float cz);
	virtual ~SmallCappingModelView();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
private:
	vec3 origin;
	float xmin, xmax, ymin, ymax, zmin, zmax;
};

#endif
