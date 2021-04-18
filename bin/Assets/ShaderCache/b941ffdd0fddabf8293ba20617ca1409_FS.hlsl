//-----------------------------------------------------------------------------
// Program Type: Fragment shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Common.glsl"
#include "FFPLib_Texturing.cg"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

SAMPLER2D(gTextureSampler0, 0);

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	oPos_0 : POSITION, 
	 in float4	iColor_0 : COLOR, 
	 in float2	iTexcoord_0 : TEXCOORD0, 
	 out float4	oColor_0 : COLOR
	)
{
	float4	lColor_0;
	float4	texel_0;

	lColor_0	=	vec4(0.000000,0.000000,0.000000,0.000000);

	oColor_0	=	iColor_0;

	texel_0	=	texture2D(gTextureSampler0, iTexcoord_0);

	oColor_0	=	texel_0*oColor_0;

	oColor_0.xyz	=	oColor_0.xyz+lColor_0.xyz;
}

