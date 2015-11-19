#version 410 core

// simple3d.vsh - A simplistic vertex shader that illustrates ONE WAY
//                to handle transformations along with a simple 3D
//                lighting model.

// Naming convention for variables holding coordinates:
// mc - model coordinates
// ec - eye coordinates
// lds - logical device space
// "p_" prefix on any of the preceding indicates the coordinates have been
//      embedded in projective space
// (gl_Position would be called something like: p_ldsPosition)

// Transformation Matrices
uniform mat4 mc_ec =   // (dynamic rotations) * (ViewOrientation(E,C,up))
	mat4(1.0, 0.0, 0.0, 0.0, // initialize to identity matrix
	     0.0, 1.0, 0.0, 0.0, // ==> no dynamic rotations -AND- MC = EC
	     0.0, 0.0, 1.0, 0.0,
	     0.0, 0.0, 0.0, 1.0);
uniform mat4 ec_lds = // (W-V map) * (projection matrix)
	mat4(1.0, 0.0, 0.0, 0.0, // initialize to (almost) identity matrix
	     0.0, 1.0, 0.0, 0.0, // ==> ORTHOGONAL projection -AND- EC = LDS
	     0.0, 0.0, -1.0, 0.0,
	     0.0, 0.0, 0.0, 1.0);

uniform vec3 kd = // "kd" - diffuse reflectivity; basic object color
	vec3(1.0, 1.0, 1.0); // default: white

uniform vec3 ks = // "ks" - specular reflectivity
	vec3(1.0, 1.0, 1.0); // default: white

uniform vec4 p_ecLightSource[] = vec4[1](vec4(0.0, 0.0, -1.0, 0.0));
uniform vec3 lightStrength[] = // "Li" - strength of the light source
	vec3[1](vec3(1.0, 1.0, 1.0)); //default: white light
uniform bool isPositional[] = bool[1](false);

uniform vec3 ia = // "ia" ambient light intensity
	vec3(1.0, 1.0, 1.0);	// default: white ambient light

uniform vec3 ka = 		// "ka" - ambient reflectivity
	vec3(0.3, 0.3, 0.3); // default: minimal ambient reflectivity


// Per-vertex attributes
// 1. incoming vertex position in model coordinates
layout (location = 0) in vec3 mcPosition;
// 2. incoming vertex normal vector in model coordinates
in vec3 mcNormal; // incoming normal vector in model coordinates

out vec3 colorToFS;

vec3 evaluateLightingModel(in vec3 ec_Q, in vec3 ec_nHat)
{

	vec3 ambientPart = ka * ia;
	vec3 iHat = vec3(0.0,0.0,0.0);
	vec3 diffusePart = vec3(0.0, 0.0, 0.0);
	vec3 specularPart= vec3(0.0, 0.0, 0.0);
	for(int i=0;i<p_ecLightSource.length();i++)
	{
		iHat = isPositional[i]
		? normalize(p_ecLightSource[i].xyz - ec_Q)
		: normalize(p_ecLightSource[i].xyz);

		float diffuseDot = dot(iHat, ec_nHat);
		if (diffuseDot > 0)
			diffusePart = diffusePart + (lightStrength[i] * (kd * diffuseDot));

		vec3 refDirHatPar = (ec_nHat, iHat)*ec_nHat;
		vec3 refDirHatPerp = -1 * (iHat - refDirHatPar);
		vec3 refDirHat = refDirHatPar + refDirHatPerp;
		vec3 vHat = normalize(-1 * ec_Q); //temporary
		int m = 20; // temporary

		float specularDot = dot(refDirHat, vHat);
		if (specularDot > 0)
		{
				specularPart = specularPart + (ks * pow(specularDot, m));
		}
	}

	vec3 output = specularPart;
	if (length(output)>1.0)
	{
		// adjusts vector by dividing by largest component
		output = (1.0/max(output[0], max(output[1], output[2]))) * output;
	}

	return output;
}

void main ()
{
	// convert current vertex and its associated normal to eye coordinates
	vec4 p_ecPosition = mc_ec * vec4(mcPosition, 1.0);
	mat3 normalMatrix = transpose( inverse( mat3x3(mc_ec) ) );
	vec3 ec_nHat = normalize(normalMatrix * mcNormal);

	colorToFS = evaluateLightingModel(p_ecPosition.xyz, ec_nHat);

	// apply the projection matrix to compute the projective space representation
	// of the 3D logical device space coordinates of the input vertex:
	gl_Position = ec_lds * p_ecPosition;
}
