//AshaMath.h
//Asha math utinity lib

#pragma once

#ifndef _ASHAMATH_H_
#define _ASHAMATH_H_

//Tempary wrap directx math libs
#include <DirectXMath.h>
using namespace DirectX;
namespace aMath
{
	//Wrap d3dxmatrix type
	typedef XMMATRIX aMat;

    //Define common math constants
	#define aE        2.71828182845904523536
    #define aLOG2E    1.44269504088896340736
    #define aLOG10E   0.434294481903251827651
    #define aLN2      0.693147180559945309417
    #define aLN10     2.30258509299404568402
    #define aPI       3.14159265358979323846
    #define aPI_2     1.57079632679489661923
    #define aPI_4     0.785398163397448309616
    #define a1_PI     0.318309886183790671538
    #define a2_PI     0.636619772367581343076
    #define a2_SQRTPI 1.12837916709551257390
    #define aSQRT2    1.41421356237309504880
    #define aSQRT1_2  0.707106781186547524401

	//Left hand projection matrix get
	aMat getProjMat(float fovyrad,float aspect,float znear,float zfar);
	//Get unit matrix
	aMat getWorldMat(void);
	//Get orthogeography projection matrix left hand
	aMat getOrthMat(float wide,float height,float znear,float zfar);
	//Get aixes rotation matrix
	aMat getAixRotaMat(float roateAix[4],float angleRad);
	//Get camera matrix
	aMat getCameraMat(float eyePos[4],float objPos[4],float upPos[4]);
	XMVECTOR arry2xmvec(float srcArray[4]);
};

#endif