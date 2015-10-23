// project2.c++: Starter for EECS 672 Project 2

#include "GLFWController.h"
#include "TEMPLATE_Subclass.h"
#include "LaneModelView.h"
#include "MandM.h"
#include "PinModelView.h"

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	/*

	// Set values for eye-center-up to produce a reasonable off-axis
	// view of your scene, then:

	// 1:
	double xmid = 0.5 * (xyz[0] + xyz[1]);
	double ymid = 0.5 * (xyz[2] + xyz[3]);
	double zmid = 0.5 * (xyz[4] + xyz[5]);
	cryph::AffPoint center(xmid, ymid, zmid);

	// 2:
	double maxDelta = xyz[1] - xyz[0];
	double delta = xyz[3] - xyz[2];
	if (delta > maxDelta)
		maxDelta = delta;
	delta = xyz[5] - xyz[4];
	if (delta > maxDelta)
		maxDelta = delta;

	double distEyeCenter = 2.0 * maxDelta;
	cryph::AffPoint eye(xmid, ymid, zmid + distEyeCenter);

	// 3:
	cryph::AffVector up = cryph::AffVector::yu;

	ModelView::setEyeCenterUp(eye, center, up);

	double ecZpp = -(distEyeCenter - 0.5*maxDelta);
	double ecZmin = ecZpp - maxDelta;
	double ecZmax = ecZpp + 0.5*maxDelta;

	ModelView::setProjection(PERSPECTIVE);
	ModelView::setECZminZmax(ecZmin, ecZmax);
	ModelView::setProjectionPlaneZ(ecZpp);

	*/
	double xmid = 0.5 * (xyz[0] + xyz[1]);
	double ymid = 0.5 * (xyz[2] + xyz[3]);
	double zmid = 0.5 * (xyz[4] + xyz[5]);
	cryph::AffPoint center(19.5, 0, 30);

	cryph::AffPoint eye(50.0, 20.0, 20.0);

	cryph::AffVector up = cryph::AffVector::yu;

	ModelView::setEyeCenterUp(eye, center, up);

	double ecZpp = -700.0;
	double ecZmin = -1000.0;
	double ecZmax = -1.0;

	ModelView::setProjection(PERSPECTIVE);
	ModelView::setECZminZmax(ecZmin, ecZmax);
	ModelView::setProjectionPlaneZ(ecZpp);

}

int main(int argc, char* argv[])
{
	GLFWController c("GIVE ME A NICE TITLE", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	PinModelView::initVertexGroups();
	PinModelView::initBaseCoordinates();

	// create your scene, adding things to the Controller....
	c.addModel(new LaneModelView());
	c.addModel(new PinModelView(19.5, 0.0, 30.0));
	//c.addModel(new Block(19.5, 0.0, 30.0, 4.0, 15.0, 4.0));

	glClearColor(.5, .5, .5, 1.0);

	double xyz[6];

	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
