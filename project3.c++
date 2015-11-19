// project2.c++: Starter for EECS 672 Project 2

#include "DynamicController.h"
#include "PairModelView.h"

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	double xmid = 0.5 * (xyz[0] + xyz[1]);
	double ymid = 0.5 * (xyz[2] + xyz[3]);
	double zmid = 0.5 * (xyz[4] + xyz[5]);
	const float cx = -2.5*129.0;
	cryph::AffPoint center(cx, 50.0, 300.0);

	cryph::AffPoint eye(cx, 50.0, -80.0);

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
	DynamicController c("Bowling Lane Mock-up", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	GutterModelView::initBaseCoordinates();
	GutterModelView::initNormals();

	// create your scene, adding things to the Controller....
	const float pairWidthWithoutLeftCapping = 129.0;
	for(int pair=0;pair<6;pair++){
		c.addModel(new PairModelView(-pair*pairWidthWithoutLeftCapping, 0, 0, pair==0));
	}
	c.addModel(new PinModelView(-2.5*129.0, 50, -50));

	glClearColor(0, 0, .6, 1.0);

	double xyz[6];

	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
