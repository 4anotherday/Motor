//-----------------------------------------------------------------------------
// Program Type: Vertex shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Transform.glsl"
#include "SGXLib_PerPixelLighting.glsl"
#include "FFPLib_Common.glsl"
#include "FFPLib_Texturing.glsl"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

float4x4	worldviewproj_matrix;
float3x3	normal_matrix;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	iPos_0 : POSITION, 
	 in float3	iNormal_0 : NORMAL, 
	 out float4	oPos_0 : POSITION, 
	 out float3	oTexcoord_0 : TEXCOORD0
	)
{
	float4	lColor_0;
	float4	lColor_1;

	FFP_Transform(worldviewproj_matrix, iPos_0, oPos_0);

	lColor_0	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	vec4(0.000000,0.000000,0.000000,0.000000);

	FFP_Transform(normal_matrix, iNormal_0, oTexcoord_0);
}

