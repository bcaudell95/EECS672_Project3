// Extracted from: ModelView.c++ - an Abstract Base Class for a combined Model and View for OpenGL

#include "ModelView.h"
#include "ProjectionType.h"

void ModelView::addToGlobalRotationDegrees(double rx, double ry, double rz)
{
	std::cout << "For project 3, you must implement ModelView::addToGlobalRotationDegrees in ModelView_Additions.c++\n";
	// TODO: 1. UPDATE dynamic_view
	// TODO: 2. Use dynamic_view in ModelView::getMatrices
}

void ModelView::addToGlobalZoom(double increment)
{
	dynamic_zoomScale += increment;
	// TODO: Project 3: Use dynamic_zoomScale in ModelView::getMatrices
}

void ModelView::getMatrices(cryph::Matrix4x4& mc_ec, cryph::Matrix4x4& ec_lds)
{
	// 1. Create the mc_ec matrix:
	cryph::Matrix4x4 M_ECu = cryph::Matrix4x4::lookAt(eye, center, up);
	mc_ec = M_ECu;

	// 2. Create the ec_lds matrix:
	//Note that positive or negative values don't matter for these three
	const double dx = mcRegionOfInterest[0] - mcRegionOfInterest[1];
	const double dy = mcRegionOfInterest[2] - mcRegionOfInterest[3];
	const double dz = mcRegionOfInterest[4] - mcRegionOfInterest[5];

	const double radius = 0.5*sqrt(dx*dx + dy*dy + dz*dz);

	double ecXmin = -1.0 * radius;
	double ecXmax = radius;
	double ecYmin = -1.0 * radius;
	double ecYmax = radius;

	double vAR = Controller::getCurrentController()->getViewportAspectRatio();

	matchAspectRatio(ecXmin, ecXmax, ecYmin, ecYmax, vAR);

	if (projType == ORTHOGONAL)
		ec_lds = cryph::Matrix4x4::orthogonal(ecXmin, ecXmax, ecYmin, ecYmax, ecZmin, ecZmax);
	else if (projType == PERSPECTIVE)
		ec_lds = cryph::Matrix4x4::perspective(ecZpp, ecXmin, ecXmax, ecYmin, ecYmax, ecZmin, ecZmax);
	else // Must be OBLIQUE
		ec_lds = cryph::Matrix4x4::oblique(ecZpp, ecXmin, ecXmax, ecYmin, ecYmax, ecZmin, ecZmax, obliqueProjectionDir);
}
