//-----------------------------------------------------------------------------
// Program Type: Vertex shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Transform.cg"
#include "FFPLib_Common.glsl"
#include "FFPLib_Texturing.cg"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

float4x4	worldviewproj_matrix;
float4x4	texture_matrix;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	iPos_0 : POSITION, 
	 in float2	iTexcoord_0 : TEXCOORD0, 
	 out float4	oPos_0 : POSITION, 
	 out float2	oTexcoord_0 : TEXCOORD0, 
	 out float2	oTexcoord_1 : TEXCOORD1
	)
{
	float4	lColor_0;
	float4	lColor_1;

	FFP_Transform(worldviewproj_matrix, iPos_0, oPos_0);

	lColor_0	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	vec4(0.00000,0.00000,0.00000,0.00000);

	oTexcoord_0	=	iTexcoord_0;

	FFP_TransformTexCoord(texture_matrix, oTexcoord_0, oTexcoord_0);

	oTexcoord_1	=	iTexcoord_0;
}

