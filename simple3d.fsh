#version 410 core

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
	vec3(0.5, 0.5, 0.5); // default: white

uniform vec4 p_ecLightSource[] = vec4[1](vec4(100.0, 50.0, 100.0, 0.0));
uniform vec3 lightStrength[] = // "Li" - strength of the light source
	vec3[1](vec3(1.0, 0.0, 0.0)); //default: white light
uniform bool isPositional[] = bool[1](true);

uniform vec3 ia = // "ia" ambient light intensity
	vec3(1.0, 1.0, 1.0);	// default: white ambient light

uniform vec3 ka = 		// "ka" - ambient reflectivity
	vec3(0.3, 0.3, 0.3); // default: minimal ambient reflectivity

in vec4 p_ecPosition;
in vec3 ec_nHat;

out vec4 fragmentColor;

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
		{
			diffusePart = diffusePart + (lightStrength[i] * (kd * diffuseDot));
		}


		vec3 refDirHat = normalize(reflect(iHat, ec_nHat));
		vec3 vHat = normalize(ec_Q); //temporary
		int m = 4; // temporary

		float specularDot = dot(refDirHat, vHat);
		if (specularDot > 0)
		{
				specularPart = specularPart + (ks * pow(specularDot, m));
		}
	}

	vec3 output = ambientPart + diffusePart + specularPart;

	return output;
}


void main()
{
	vec3 color = evaluateLightingModel(vec3(p_ecPosition), ec_nHat);
	fragmentColor = vec4(color, 1.0);
}
