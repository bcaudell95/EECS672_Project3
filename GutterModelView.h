// TEMPLATE_Subclass.h

#ifndef GUTTER_MODELVIEW_H
#define GUTTER_MODELVIEW_H

#include "ModelViewWithPhongLighting.h"

class GutterModelView : public ModelViewWithPhongLighting
{
public:
	GutterModelView(float cx, float cy, float cz);
	virtual ~GutterModelView();

	static void initBaseCoordinates();
	static void initNormals();

	static float r;
	static vec3 kd;
	static vec3 ka;
	static float length;

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	void defineGutter();
	void renderGutter();

	vec3 origin;
	float xmin, xmax, ymin, ymax, zmin, zmax;

	GLuint vao[1];
	GLuint vbo[2]; // first for coordinates, second for normal vector
	GLuint ebo[17]; // 17 faces

	static GLuint indexList[17][4]; // 17 faces
	static vec3 baseCoordinates[36]; // 36 points
	static vec3 normals[36];
};

#endif
