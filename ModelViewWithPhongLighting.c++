// ModelViewWithPhongLighting.c++

#include <iostream>
#include <math.h>

#include "AffPoint.h"
#include "AffVector.h"
#include "Matrix4x4.h"

#include "ModelViewWithPhongLighting.h"
#include "ShaderIF.h"

ShaderIF* ModelViewWithPhongLighting::shaderIF = NULL;
int ModelViewWithPhongLighting::numInstances = 0;
GLuint ModelViewWithPhongLighting::shaderProgram = 0;
GLint ModelViewWithPhongLighting::pvaLoc_mcPosition = -2;
GLint ModelViewWithPhongLighting::pvaLoc_mcNormal = -2;
GLint ModelViewWithPhongLighting::ppuLoc_kd = -2;
GLint ModelViewWithPhongLighting::ppuLoc_mc_ec = -2;
GLint ModelViewWithPhongLighting::ppuLoc_ec_lds = -2;
GLint ModelViewWithPhongLighting::ppuLoc_lightStrength = -2;
GLint ModelViewWithPhongLighting::ppuLoc_isPositional = -2;
GLint ModelViewWithPhongLighting::ppuLoc_p_ecLightSource = -2;
GLint ModelViewWithPhongLighting::ppuLoc_ia = -2;
GLint ModelViewWithPhongLighting::ppuLoc_ka = -2;

std::string ModelViewWithPhongLighting::vShaderSource = "simple3d.vsh";
std::string ModelViewWithPhongLighting::fShaderSource = "simple3d.fsh";

ModelViewWithPhongLighting::ModelViewWithPhongLighting()
{
	if (shaderProgram == 0)
	{
		shaderIF = new ShaderIF(vShaderSource, fShaderSource);
		shaderProgram = shaderIF->getShaderPgmID();
		fetchGLSLVariableLocations();
	}
	numInstances++;
}

ModelViewWithPhongLighting::~ModelViewWithPhongLighting()
{
	if (--numInstances == 0)
	{
		shaderIF->destroy();
		delete shaderIF;
		shaderIF = NULL;
		shaderProgram = 0;
	}
}

void ModelViewWithPhongLighting::fetchGLSLVariableLocations()
{
	if (shaderProgram > 0)
	{
		pvaLoc_mcPosition = pvAttribLocation(shaderProgram, "mcPosition");
		pvaLoc_mcNormal = pvAttribLocation(shaderProgram, "mcNormal");
		ppuLoc_kd = ppUniformLocation(shaderProgram, "kd");
		ppuLoc_mc_ec = ppUniformLocation(shaderProgram, "mc_ec");
		ppuLoc_ec_lds = ppUniformLocation(shaderProgram, "ec_lds");
		ppuLoc_lightStrength = ppUniformLocation(shaderProgram, "lightStrength");
		ppuLoc_isPositional = ppUniformLocation(shaderProgram, "isPositional");
		ppuLoc_p_ecLightSource = ppUniformLocation(shaderProgram, "p_ecLightSource");
		ppuLoc_ia = ppUniformLocation(shaderProgram, "ia");
		ppuLoc_ka = ppUniformLocation(shaderProgram, "ka");
	}
}

void ModelViewWithPhongLighting::setShaderSources(const std::string& vShaderSrc, const std::string& fShaderSrc)
{
	vShaderSource = vShaderSrc;
	fShaderSource = fShaderSrc;
}

void ModelViewWithPhongLighting::handleCommand(unsigned char key, double ldsX, double ldsY)
{
	if (key=='p')
	{
		projType = PERSPECTIVE;
	}
	else if (key=='o')
	{
		projType = ORTHOGONAL;
	}
	else // Oblique
	{
		projType = OBLIQUE;
	}
}
