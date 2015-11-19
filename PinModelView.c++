// Block.c++

#include <iostream>
#include <math.h>

#include "PinModelView.h"
#include "ShaderIF.h"
#include <math.h>

typedef float vec3[3];

vec3 PinModelView::size = {4.78, 15.0, 4.78};
vec3 PinModelView::baseCoordinates[1116];
vec3 PinModelView::normals[1116];
GLuint PinModelView::indexList[1080][4];
float PinModelView::diameterByHeight[]
	= {
		2.031, 2.5, 	// 0in
		3.0, 3.375, 	// 1in
		3.75, 4.0,		// 2in
		4.2, 4.4, 		// 3in
		4.6, 4.6, 		// 4in
		4.6, 4.55,		// 5in
		4.5, 4.1,			// 6in
		3.75, 3.25,		// 7in
		2.75, 2.4,		// 8in
		2.1, 1.95,		// 9in
		1.797, 1.85,	// 10in
		1.9, 2.0,			// 11in
		2.1, 2.3,			// 12in
		2.45, 2.2,		// 13in
		1.9, 1.4,			// 14in
		0							// 15in
	};

void PinModelView::initBaseCoordinates()
{

	vec3 vertex;
	vec3 normal;

	//load coordinates for 1116 points and 1080 faces
	for(int ring=0; ring<31;ring++)
	{
		for(int i=0; i<36;i++)
		{
			vertex[0] = radiusAtHeight(ring) * cos(M_PI * (i/18.0));
			vertex[1] = ring/2.0;
			vertex[2] = radiusAtHeight(ring) * sin(M_PI * (i/18.0));

			for(int j=0;j<3;j++)
				baseCoordinates[(36*ring)+i][j] = vertex[j];

			normal[0] = -cos(M_PI * ((i+.5)/18.0));
			normal[2] = -sin(M_PI * ((i+.5)/18.0));
			float y = (ring==30 || ring==0) ? 0
				: sin(atan(.5/(radiusAtHeight(ring+1)-radiusAtHeight(ring-1))));
			float nYAbove = (ring == 30) ? 1 : sin(atan(.5/(radiusAtHeight(ring+1)-radiusAtHeight(ring))));
			float nYBelow = (ring == 0) ? 0 : sin(atan(.5/(radiusAtHeight(ring)-radiusAtHeight(ring-1))));
			normal[1] = y;
			float mag = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);

			for(int j=0;j<3;j++)
				normals[(36*ring)+i][j] = -1*normal[j]/mag; // dividing by mag normalizes

		}
	}
}

float PinModelView::radiusAtHeight(float height)
{
	int i = (int)height;
	return diameterByHeight[i]/2.0;
}

void PinModelView::initVertexGroups()
{
	int vertices[4];

	//load vertex data for 1080 faces
	for(int ring=0; ring<30;ring++)
	{
		for(int i=0; i<36;i++)
		{
			vertices[0] = (36 * ring) + i; // first vertex for face
			if(vertices[0] % 36 < 35)
			{
				vertices[1] = vertices[0] + 1; //second vertex for face
				vertices[3] = vertices[0] + 37; //fourth vertex for face
			}
			else
			{
				vertices[1] = vertices[0] - 35; //second vertex for face
				vertices[3] = vertices[0] + 1; //fourth vertex for face
			}
			vertices[2] = vertices[0] + 36; //third vertex for face

			for(int j=0;j<4;j++)
			{
				indexList[(36*ring)+i][j] = vertices[j];
			}
		}
	}
}

PinModelView::PinModelView(float cx, float cy, float cz)
{
	origin[0] = cx;
	origin[1] = cy;
	origin[2] = cz;

	xmin = cx - (size[0]/2); xmax = cx + (size[0]/2);
	ymin = cy; ymax = cy + size[1];
	zmin = cz - (size[2]/2); zmax = cz + (size[2]/2);

	definePin();
}

void PinModelView::definePin()
{
	vec3 vtx[1116];
	for(int i=0;i<1116;i++) // vertex number
	{
		for(int j=0;j<3;j++) // x y or z
			vtx[i][j] = origin[j] + baseCoordinates[i][j];
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 1116*sizeof(vec3), vtx, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_mcPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_mcPosition);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 1116*sizeof(vec3), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_mcNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_mcNormal);


	glGenBuffers(1080, ebo);
	for (int i=0 ; i<1080 ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}

}

PinModelView::~PinModelView()
{
	glDeleteBuffers(1080,ebo);
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void PinModelView::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void PinModelView::handleCommand(unsigned char key, double ldsX, double ldsY)
{

}

void PinModelView::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderProgram);

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(ppuLoc_mc_ec, 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(ppuLoc_ec_lds, 1, false, ec_lds.extractColMajor(mat));

	renderPin();

	glUseProgram(pgm);
}

void PinModelView::renderPin()
{

	vec3 white = {1.0, 1.0, 1.0};
	vec3 red = {1.0, 0, 0};
	vec3 ka_white = {.4, .4, .4};
	vec3 ka_red = {.4, 0, 0};

	glBindVertexArray(vao[0]);

	// draw 1080 faces using ebo's for vertex data
	for(int i=0;i<1080;i++)
	{
		glUniform3fv(ppuLoc_kd, 1, isFaceOnStripe(i) ? red : white);
		glUniform3fv(ppuLoc_ka, 1, isFaceOnStripe(i) ? ka_red : ka_white);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, NULL);
	}

}

bool PinModelView::isFaceOnStripe(int face)
{
	return ((face>= (36*20) && face < (36*21)) || (face>= (36*22) && face < (36*23)));
}
