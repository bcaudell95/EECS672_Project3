// ModelViewWithPhongLighting.h

#ifndef MODELVIEWWITHPHONGLIGHTING_H
#define MODELVIEWWITHPHONGLIGHTING_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "ModelView.h"
#include "ShaderIF.h"
#include "Matrix4x4.h"
#include "ProjectionType.h"

typedef float vec3[3];

class ModelViewWithPhongLighting : public ModelView
{
public:
	ModelViewWithPhongLighting();
	virtual ~ModelViewWithPhongLighting();

	static void setShaderSources(const std::string& vShader, const std::string& fShader);
	virtual void handleCommand(unsigned char key, double ldsX, double ldsY);

protected:

	static ShaderIF* shaderIF;
	static int numInstances;
	static GLuint shaderProgram;
	static GLint pvaLoc_mcPosition, pvaLoc_mcNormal;
	static GLint ppuLoc_kd,
		ppuLoc_ka;
	static GLint ppuLoc_ia;
	static GLint ppuLoc_mc_ec, ppuLoc_ec_lds;
	static GLint ppuLoc_lightStrength,
		ppuLoc_isPositional,
		ppuLoc_p_ecLightSource;

	static void fetchGLSLVariableLocations();

private:
	static std::string vShaderSource, fShaderSource;;
};

#endif
