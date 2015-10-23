// TEMPLATE_Subclass.h

#ifndef TEN_PINS_MODELVIEW_H
#define TEN_PINS_MODELVIEW_H

#include "PinModelView.h"
#include <vector>

class TenPinsModelView : public ModelViewWithPhongLighting
{
public:
	TenPinsModelView(float headCx, float headCy, float headCz);
	virtual ~TenPinsModelView();

	static vec3 centers[];

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:

	std::vector<PinModelView*> pins;
};

#endif
