// TEMPLATE_Subclass.c++

#include "GutterModelView.h"
#include "ShaderIF.h"

float GutterModelView::r = 4.625;
float GutterModelView::length = 760.0;
vec3 GutterModelView::kd = {.3, .3, .3};
vec3 GutterModelView::ka = {.2, .2, .2};

vec3 GutterModelView::baseCoordinates[36];
vec3 GutterModelView::normals[36];
GLuint GutterModelView::indexList[17][4];

void GutterModelView::initBaseCoordinates(){
	vec3 vertex;
	vec3 normal;

	for(int arc=0; arc<2;arc++)
	{
		for(int i=0; i<18;i++)
		{
			vertex[0] = r * cos(M_PI * (i/18.0));
			vertex[1] = r * -sin(M_PI * (i/18.0));
			vertex[2] = arc*length;

			for(int j=0;j<3;j++)
				baseCoordinates[(18*arc)+i][j] = vertex[j];

			normal[0] = cos(M_PI * ((i+.5)/18.0));
			normal[1] = sin(M_PI * ((i+.5)/18.0));

			for(int j=0;j<3;j++)
				normals[(18*arc)+i][j] = -1*normal[j];

		}
	}
}

void GutterModelView::initNormals()
{
	for(int i=0;i<17;i++){
		indexList[i][0] = i;
		indexList[i][1] = i+1;
		indexList[i][2] = i+18;
		indexList[i][3] = i+19;
	}
}

GutterModelView::GutterModelView(float cx, float cy, float cz)
{
	origin[0] = cx;
	origin[1] = cy;
	origin[2] = cz;

	xmin = cx - r; xmax = cx + r;
	ymin = cy - r; ymax = cy;
	zmin = cz; zmax = cz + length;

	defineGutter();
}

void GutterModelView::defineGutter()
{
	vec3 vtx[36];
	for(int i=0;i<36;i++) // vertex number
	{
		for(int j=0;j<3;j++) // x y or z
			vtx[i][j] = origin[j] + baseCoordinates[i][j];
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 36*sizeof(vec3), vtx, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_mcPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_mcPosition);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 36*sizeof(vec3), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_mcNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_mcNormal);


	glGenBuffers(17, ebo);
	for (int i=0 ; i<17 ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}

}

GutterModelView::~GutterModelView()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void GutterModelView::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = -1000.0; // xmin  Give real values!
	xyzLimits[1] = 1000.0;  // xmax         |
	xyzLimits[2] = -1234.5; // ymin         |
	xyzLimits[3] = -1011.2; // ymax         |
	xyzLimits[4] = -3000.0; // zmin         |
	xyzLimits[5] = -2000.0; // zmax        \_/
}

void GutterModelView::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderProgram);

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(ppuLoc_mc_ec, 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(ppuLoc_ec_lds, 1, false, ec_lds.extractColMajor(mat));

	renderGutter();

	glUseProgram(pgm);
}

void GutterModelView::renderGutter()
{

	glBindVertexArray(vao[0]);

	glUniform3fv(ppuLoc_kd, 1, kd);
	glUniform3fv(ppuLoc_ambientReflectivity, 1, ka);

	// draw 1080 faces using ebo's for vertex data
	for(int i=0;i<17;i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, NULL);
	}

}
