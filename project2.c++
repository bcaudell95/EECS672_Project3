// project2.c++: Starter for EECS 672 Project 2

#include "GLFWController.h"
#include "TEMPLATE_Subclass.h"
#include "LaneModelView.h"
#include "MandM.h"
#include "TenPinsModelView.h"
#include "GutterModelView.h"

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	double xmid = 0.5 * (xyz[0] + xyz[1]);
	double ymid = 0.5 * (xyz[2] + xyz[3]);
	double zmid = 0.5 * (xyz[4] + xyz[5]);
	cryph::AffPoint center(0, 0, 300.0);

	cryph::AffPoint eye(25.0, 5.0, -10.0);

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

	GutterModelView::initBaseCoordinates();
	GutterModelView::initNormals();

	// create your scene, adding things to the Controller....
	c.addModel(new LaneModelView(0,0,0));
	c.addModel(new GutterModelView(19.5 + 4.625, 1.0, 0));

	glClearColor(0, 0, .6, 1.0);

	double xyz[6];

	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
