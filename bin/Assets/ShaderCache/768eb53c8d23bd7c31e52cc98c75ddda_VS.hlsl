//-----------------------------------------------------------------------------
// Program Type: Vertex shader
// Language: hlsl
// Created by Ogre RT Shader Generator. All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//                         PROGRAM DEPENDENCIES
//-----------------------------------------------------------------------------
#include <OgreUnifiedShader.h>
#include "FFPLib_Common.glsl"
#include "FFPLib_Transform.cg"
#include "SGXLib_DualQuaternion.glsl"
#include "SGXLib_PerPixelLighting.glsl"
#include "FFPLib_Texturing.cg"

//-----------------------------------------------------------------------------
//                         GLOBAL PARAMETERS
//-----------------------------------------------------------------------------

float2x4	world_dualquaternion_array_2x4[24];
float4x4	inverse_world_matrix;
float4x4	viewproj_matrix;
float3x4	world_scale_shear_matrix_array_3x4[24];
float3x3	normal_matrix;

//-----------------------------------------------------------------------------
// Function Name: main
// Function Desc: 
//-----------------------------------------------------------------------------
void main
	(
	 in float4	iPos_0 : POSITION, 
	 in float3	iNormal_0 : NORMAL, 
	 in uint4	iBlendIndices_0 : BLENDINDICES, 
	 in float4	iBlendWeights_0 : BLENDWEIGHT, 
	 out float4	oPos_0 : POSITION, 
	 out float3	oTexcoord_0 : TEXCOORD0
	)
{
	float3	BlendedPosition;
	float3	lTexcoord_1;
	float2x4	worldMatrix;
	float2x4	blendDQ;
	float2x4	initialDQ;
	float3x4	blendS;
	float3x3	TempVal3x3;
	float3x4	TempVal3x4;
	float2x4	TempVal2x4;
	float4	TempVal4;
	float3	TempVal3;
	float4	lColor_11;
	float4	lColor_12;

	TempVal3x4	=	world_scale_shear_matrix_array_3x4[int(iBlendIndices_0.x)];

	TempVal3x4	=	iBlendWeights_0.x*TempVal3x4;

	blendS	=	TempVal3x4;

	TempVal3x4	=	world_scale_shear_matrix_array_3x4[int(iBlendIndices_0.y)];

	TempVal3x4	=	iBlendWeights_0.y*TempVal3x4;

	blendS	=	TempVal3x4+blendS;

	FFP_Transform(blendS, iPos_0, BlendedPosition);

	TempVal2x4	=	world_dualquaternion_array_2x4[int(iBlendIndices_0.x)];

	initialDQ	=	TempVal2x4;

	TempVal2x4	=	iBlendWeights_0.x*TempVal2x4;

	blendDQ	=	TempVal2x4;

	TempVal2x4	=	world_dualquaternion_array_2x4[int(iBlendIndices_0.y)];

	SGX_AntipodalityAdjustment(initialDQ, TempVal2x4, TempVal2x4);

	TempVal2x4	=	iBlendWeights_0.y*TempVal2x4;

	blendDQ	=	TempVal2x4+blendDQ;

	SGX_NormalizeDualQuaternion(blendDQ);

	SGX_CalculateBlendPosition(BlendedPosition, blendDQ, TempVal4);

	FFP_Transform(viewproj_matrix, TempVal4, oPos_0);

	FFP_Transform(inverse_world_matrix, TempVal4, iPos_0);

	SGX_AdjointTransposeMatrix(blendS, TempVal3x3);

	FFP_Transform(TempVal3x3, iNormal_0, iNormal_0);

	FFP_Normalize(iNormal_0);

	SGX_CalculateBlendNormal(iNormal_0, blendDQ, lTexcoord_1);

	FFP_Transform(inverse_world_matrix, lTexcoord_1, iNormal_0);

	lColor_11	=	vec4(1.00000,1.00000,1.00000,1.00000);

	lColor_12	=	vec4(0.00000,0.00000,0.00000,0.00000);

	FFP_Transform(normal_matrix, iNormal_0, oTexcoord_0);
}

