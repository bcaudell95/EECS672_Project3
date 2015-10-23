// TEMPLATE_Subclass.h

#ifndef BIG_CAPPING_MODELVIEW_H
#define BIG_CAPPING_MODELVIEW_H

#include "Block.h"

class BigCappingModelView : public Block
{
public:
	static vec3 size;

	BigCappingModelView(float cx, float cy, float cz);
	virtual ~BigCappingModelView();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
private:
	vec3 origin;
	float xmin, xmax, ymin, ymax, zmin, zmax;
};

#endif
