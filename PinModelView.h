// Block.h

#ifndef PIN_MODEL_VIEW_H
#define PIN_MODEL_VIEW_H

#include <GL/gl.h>

#include "ModelViewWithPhongLighting.h"

class PinModelView : public ModelViewWithPhongLighting
{
public:
	PinModelView(float cx, float cy, float cz);// center of the base
	virtual ~PinModelView();

	static void initBaseCoordinates();
	static void initVertexGroups();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void handleCommand(unsigned char key, double ldsX, double ldsY);
	void definePin();
	void render();
	void renderPin();

protected:

private:
	GLuint vao[1];
	GLuint vbo[2]; // first for coordinates, second for normal vector
	GLuint ebo[1080];

	vec3 origin;
	float xmin, xmax, ymin, ymax, zmin, zmax;

	static GLuint indexList[1080][4]; // 1080 faces

	static vec3 size;
	static float radiusAtHeight(float height);
	static vec3 baseCoordinates[1116]; // 1116 points
	static vec3 normals[1116];
	static float diameterByHeight[];
	static bool isFaceOnStripe(int face);

};

#endif
