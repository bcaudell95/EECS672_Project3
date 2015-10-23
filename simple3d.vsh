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

// There are MANY ways to deal with the basic object color.
// For now we will  simply assume:
uniform vec3 kd = // "kd" - diffuse reflectivity; basic object color
	vec3(1.0, 1.0, 1.0); // default: white

uniform vec3 lightStrength = // "Li" - strength of the light source
	vec3(1.0, 1.0, 1.0); //default: white light

uniform vec3 ambientIntensity = // "ia" ambient light intensity
	vec3(1.0, 1.0, 1.0);	// default: white ambient light

uniform vec3 ambientReflectivity = 		// "ka" - ambient reflectivity
	vec3(0.3, 0.3, 0.3); // default: minimal ambient reflectivity


// There are also MANY ways to deal with light sources (number, type,
// strength, etc.).  For now we simply assume one directional source.
// You will generalize this in future projects.
uniform vec4 p_ecLightSource = vec4(.5, 1.0, 0, 0.0);

// Per-vertex attributes
// 1. incoming vertex position in model coordinates
layout (location = 0) in vec3 mcPosition;
// 2. incoming vertex normal vector in model coordinates
in vec3 mcNormal; // incoming normal vector in model coordinates

out vec3 colorToFS;

vec3 evaluateLightingModel(in vec3 ec_Q, in vec3 ec_nHat)
{

	vec3 ambientPart = ambientReflectivity * ambientIntensity;
	vec3 diffusePart = vec3(0.0, 0.0, 0.0);
	float dot = dot(normalize(p_ecLightSource.xyz), ec_nHat);
	if (dot > 0)
		diffusePart = lightStrength * (kd * dot);

	return ambientPart + diffusePart;
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
