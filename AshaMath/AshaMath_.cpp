//AshaMath.cpp
#include "AshaMath_.h"
using namespace aMath;

/****************************************************************************
 *
 * Data conversion operations
 *
 ****************************************************************************/

aVector aConvertVectorIntToFloat(aVector VInt, unsigned int DivExponent)
{

}
aVector aConvertVectorFloatToInt(aVector VFloat, unsigned int MulExponent)
{

}
aVector aConvertVectorUIntToFloat(aVector VUInt, unsigned int DivExponent)
{

}
aVector aConvertVectorFloatToUInt(aVector VFloat, unsigned int MulExponent)
{

}

///////////////////////////////////////////////////////////////////////////////////

/****************************************************************************
 *
 * Load operations
 *
 ****************************************************************************/
//Usigned int vector load
aVector aMath::aLoadUInt(const unsigned int* pSource)
{
	aVector vecbuff;
	for(int i=0;i<4;i++)
	{
		if(pSource!=nullptr)
			vecbuff.data_u32[i]=pSource[i];
		else
			vecbuff.data_u32[i]=0;
	}

	return vecbuff;
}
//Int vector load
aVector aMath::aLoadInt(const int* pSource)
{
	aVector vecbuff;
	for(int i=0;i<4;i++)
	{
		if(pSource!=nullptr)
			vecbuff.data_i32[i]=pSource[i];
		else
			vecbuff.data_i32[i]=0;
	}

	return vecbuff;
}
//Float vector load
aVector aMath::aLoadFloat(const float* pSource)
{
	aVector vecbuff;
	for(int i=0;i<4;i++)
	{
		if(pSource!=nullptr)
			vecbuff.data_f32[i]=pSource[i];
		else
			vecbuff.data_f32[i]=0.0f;
	}
	
	return vecbuff;
}

//Matrix load
aMat aMath::aLoadFloat3x3(  const aFloat3X3* pSource)
{
	aMat matbuff;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i<3)
			    matbuff.m[i][j]=pSource->m[i][j];
			else
				matbuff.m[i][j]=0.0f;
		}

		matbuff.m[i][3]=0.0f;
	}

	return matbuff;
}
aMat aMath::aLoadFloat4x3(  const aFloat4X3* pSource)
{
	aMat matbuff;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(j<3)
			    matbuff.m[i][j]=pSource->m[i][j];
			else
				matbuff.m[i][j]=0.0f;
		}
	}

	return matbuff;
}
aMat aMath::aLoadFloat4x4(  const aFloat4X4* pSource)
{
	aMat matbuff;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			    matbuff.m[i][j]=pSource->m[i][j];
		}
	}

	return matbuff;
}
/****************************************************************************
 *
 * Store operations
 *
 ****************************************************************************/
//Store vector to array
void  aMath::aStoreUInt(  unsigned int* pDestination,   aVector V)
{
	for(int i=0;i<4;i++)
	{
			pDestination[i]=V.data_u32[i];
	}
}
void  aMath::aStoreInt(int* pDestination,   aVector V)
{
	for(int i=0;i<4;i++)
	{
			pDestination[i]=V.data_i32[i];
	}
}
void  aMath::aStoreFloat(  float* pDestination,   aVector V)
{
	for(int i=0;i<4;i++)
	{
			pDestination[i]=V.data_f32[i];
	}
}

//Store matrix to 4x4 matrix
void aMath::aStoreFloat3x3( aFloat3X3* pDestination, aMat M)
{
	for(int i=0;i<3;i++)
	{
		  for(int j=0;j<3;j++)
		   {
				pDestination->m[i][j]=M.m[i][j];
		   }
	}
}
void aMath::aStoreFloat4x3( aFloat4X3* pDestination, aMat M)
{
	for(int i=0;i<4;i++)
	{
		  for(int j=0;j<3;j++)
		   {
				pDestination->m[i][j]=M.m[i][j];
		   }
	}
}
void aMath::aStoreFloat4x4( aFloat4X4* pDestination,  aMat M)
{
	for(int i=0;i<4;i++)
	{
		  for(int j=0;j<4;j++)
		   {
				pDestination->m[i][j]=M.m[i][j];
		   }
	}
}
/****************************************************************************
 *
 * General vector operations
 *
 ****************************************************************************/

aVector aMath::aVectorZero()
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_f32[i]=0.0f;
	}

	return vec;
}
aVector aMath::aVectorSet(float x, float y, float z, float w)
{
	aVector vec;
	vec.data_f32[0]=x;
	vec.data_f32[1]=y;
	vec.data_f32[2]=z;
	vec.data_f32[3]=w;

	return vec;
}
aVector aMath::aVectorSetUInt(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
	aVector vec;
	vec.data_u32[0]=x;
	vec.data_u32[1]=y;
	vec.data_u32[2]=z;
	vec.data_u32[3]=w;

	return vec;
}
aVector aMath::aVectorSetInt(int x, int y,  int z, int w)
{
	aVector vec;
	vec.data_i32[0]=x;
	vec.data_i32[1]=y;
	vec.data_i32[2]=z;
	vec.data_i32[3]=w;

	return vec;
}
aVector aMath::aVectorReplicate(float Value)
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_f32[i]=Value;
	}

	return vec;
}
aVector aMath::aVectorReplicatePtr(  const float *pValue)
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_f32[i]=pValue[i];
	}

	return vec;

}
aVector aMath::aVectorReplicateUInt(unsigned int Value)
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_u32[i]=Value;
	}

	return vec;
}
aVector aMath::aVectorReplicateInt(int Value)
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_i32[i]=Value;
	}

	return vec;
}
aVector aMath::aVectorReplicateIntPtr( const int *pValue)
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_i32[i]=pValue[i];
	}

	return vec;
}
aVector aMath::aVectorReplicateUIntPtr( const unsigned int *pValue)
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_u32[i]=pValue[i];
	}

	return vec;
}
aVector aMath::aVectorTrueInt()
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_i32[i]=true;
	}

	return vec;
}
aVector aMath::aVectorFalseInt()
{
	aVector vec;
	for(int i=0;i<4;i++)
	{
		vec.data_i32[i]=false;
	}

	return vec;
}
aVector aMath::aVectorSplatX(aVector V);
aVector aMath::aVectorSplatY(aVector V);
aVector aMath::aVectorSplatZ(aVector V);
aVector aMath::aVectorSplatW(aVector V);
aVector aMath::aVectorSplatOne();
aVector aMath::aVectorSplatInfinity();
aVector aMath::aVectorSplatQNaN();
aVector aMath::aVectorSplatEpsilon();
aVector aMath::aVectorSplatSignMask();

float aMath::aVectorGetByIndex(aVector V, unsigned int i)
{
	if(i>3)
		return -0.0f;
	else
	    return V.data_f32[i];
}
float aMath::aVectorGetX(aVector V)
{
	return V.data_f32[0];
}
float aMath::aVectorGetY(aVector V)
{
	return V.data_f32[1];
}
float aMath::aVectorGetZ(aVector V)
{
	return V.data_f32[2];
}
float aMath::aVectorGetW(aVector V)
{
	return V.data_f32[3];
}

void aMath::aVectorGetByIndexPtr(  float *f,   aVector V,   unsigned int i)
{
	f=V.data_f32+i;
}
void aMath::aVectorGetXPtr(  float *x,   aVector V)
{
	x=V.data_f32;
}
void aMath::aVectorGetYPtr(  float *y,   aVector V)
{
	y=V.data_f32+1;
}
void aMath::aVectorGetZPtr(  float *z,   aVector V)
{
	z=V.data_f32+2;
}
void aMath::aVectorGetWPtr(  float *w,   aVector V)
{
	w=V.data_f32+3;
}

unsigned int aMath::aVectorGetIntByIndex(aVector V, unsigned int i)
{
	return V.data_u32[i];
}
unsigned int aMath::aVectorGetIntX(aVector V)
{
	return V.data_u32[0];
}
unsigned int aMath::aVectorGetIntY(aVector V)
{
    return V.data_u32[1];
}
unsigned int aMath::aVectorGetIntZ(aVector V)
{
    return V.data_u32[2];
}
unsigned int aMath::aVectorGetIntW(aVector V)
{
    return V.data_u32[3];

}

void aMath::aVectorGetIntByIndexPtr(  unsigned int *x,   aVector V,   unsigned int i)
{
	x=V.data_u32+i;
}
void aMath::aVectorGetIntXPtr(  unsigned int *x,   aVector V)
{
	x=V.data_u32;
}
void aMath::aVectorGetIntYPtr(  unsigned int *y,   aVector V)
{
	y=V.data_u32+1;
}
void aMath::aVectorGetIntZPtr(  unsigned int *z,   aVector V)
{
	z=V.data_u32+2;
}
void aMath::aVectorGetIntWPtr(  unsigned int *w,   aVector V)
{
	w=V.data_u32+3;
}

aVector aMath::aVectorSetByIndex(aVector V,float f, unsigned int i)
{
	//Assume V has been initialized once empty vector or filled vector.
	V.data_f32[i]=f;
	return V;
}
aVector aMath::aVectorSetX(aVector V, float x)
{
	V.data_f32[0]=x;
	return V;
}
aVector aMath::aVectorSetY(aVector V, float y)
{
	V.data_f32[1]=y;
	return V;
}
aVector aMath::aVectorSetZ(aVector V, float z)
{
	V.data_f32[2]=z;
	return V;
}
aVector aMath::aVectorSetW(aVector V, float w)
{
	V.data_f32[3]=w;
		return V;
}

aVector aMath::aVectorSetByIndexPtr(  aVector V,   const float *f,   unsigned int i)
{
	V.data_f32[i]=*f;
	return V;
}
aVector aMath::aVectorSetXPtr(  aVector V,   const float *x)
{
	V.data_f32[0]=*x;
	return V;
}
aVector aMath::aVectorSetYPtr(  aVector V,   const float *y)
{
	V.data_f32[1]=*y;
	return V;
}
aVector aMath::aVectorSetZPtr(  aVector V,   const float *z)
{
	V.data_f32[2]=*z;
	return V;
}
aVector  aMath::aVectorSetWPtr(  aVector V,   const float *w)
{
	V.data_f32[3]=*w;
	return V;
}

aVector aMath::aVectorSetIntByIndex(aVector V, unsigned int x, unsigned int i)
{
	V.data_u32[i]=x;
	return V;
}
aVector aMath::aVectorSetIntX(aVector V, unsigned int x)
{
	V.data_u32[0]=x;
	return V;
}
aVector aMath::aVectorSetIntY(aVector V, unsigned int y)
{
	V.data_u32[1]=y;
	return V;
}
aVector aMath::aVectorSetIntZ(aVector V, unsigned int z)
{
	V.data_u32[2]=z;
	return V;
}
aVector aMath::aVectorSetIntW(aVector V, unsigned int w)
{
	V.data_u32[3]=w;
	return V;
}

aVector aMath::aVectorSetIntByIndexPtr(  aVector V,   const unsigned int *x,   unsigned int i)
{
	V.data_u32[i]=*x;
	return V;
}
aVector aMath::aVectorSetIntXPtr(  aVector V,   const unsigned int *x)
{
	V.data_u32[0]=*x;
	return V;
}
aVector aMath::aVectorSetIntYPtr(  aVector V,   const unsigned int *y)
{
	V.data_u32[1]=*y;
	return V;
}
aVector aMath::aVectorSetIntZPtr(  aVector V,   const unsigned int *z)
{
	V.data_u32[2]=*z;
	return V;
}
aVector aMath::aVectorSetIntWPtr(  aVector V,   const unsigned int *w)
{
	V.data_u32[3]=*w;
	return V;
}

aVector        aVectorSwizzle(aVector V, unsigned int E0, unsigned int E1, unsigned int E2, unsigned int E3);
aVector        aVectorPermute(aVector V1, aVector V2, unsigned int PermuteX, unsigned int PermuteY, unsigned int PermuteZ, unsigned int PermuteW);
aVector        aVectorSelectControl(unsigned int VectorIndex0, unsigned int VectorIndex1, unsigned int VectorIndex2, unsigned int VectorIndex3);
aVector        aVectorSelect(aVector V1, aVector V2, aVector Control);
aVector        aVectorMergeXY(aVector V1, aVector V2);
aVector        aVectorMergeZW(aVector V1, aVector V2);


aVector  aMath::aVectorShiftLeft(aVector V1, aVector V2, unsigned int Elements)
{
	for (int i=0;i<Elements;i++)
	{
		if(Elements<4)
		{
		V2.data_f32[i]=V1.data_f32[i+Elements];
		V2.data_f32[3-i]=V1.data_f32[i];
		}
		if(Elements>=2)
		{
			V2.data_f32[i]=V1.data_f32[];
		}



	}
}
aVector        aVectorRotateLeft(aVector V, unsigned int Elements);
aVector        aVectorRotateRight(aVector V, unsigned int Elements);
aVector        aVectorInsert(aVector VD, aVector VS, unsigned int VSLeftRotateElements,
                        unsigned int Select0, unsigned int Select1, unsigned int Select2, unsigned int Select3);

aVector        aVectorEqual(aVector V1, aVector V2);
aVector        aVectorEqualR(  unsigned int* pCR,   aVector V1,   aVector V2);
aVector        aVectorEqualInt(aVector V1, aVector V2);
aVector        aVectorEqualIntR(  unsigned int* pCR,   aVector V,   aVector V2);
aVector        aVectorNearEqual(aVector V1, aVector V2, aVector Epsilon);
aVector        aVectorNotEqual(aVector V1, aVector V2);
aVector        aVectorNotEqualInt(aVector V1, aVector V2);
aVector        aVectorGreater(aVector V1, aVector V2);
aVector        aVectorGreaterR(  unsigned int* pCR,   aVector V1,   aVector V2);
aVector        aVectorGreaterOrEqual(aVector V1, aVector V2);
aVector        aVectorGreaterOrEqualR(  unsigned int* pCR,   aVector V1,   aVector V2);
aVector        aVectorLess(aVector V1, aVector V2);
aVector        aVectorLessOrEqual(aVector V1, aVector V2);
aVector        aVectorInBounds(aVector V, aVector Bounds);
aVector        aVectorInBoundsR(  unsigned int* pCR,   aVector V,   aVector Bounds);

aVector        aVectorIsNaN(aVector V);
aVector        aVectorIsInfinite(aVector V);

aVector        aVectorMin(aVector V1,aVector V2);
aVector        aVectorMax(aVector V1, aVector V2);
aVector        aVectorRound(aVector V);
aVector        aVectorTruncate(aVector V);
aVector        aVectorFloor(aVector V);
aVector        aVectorCeiling(aVector V);
aVector        aVectorClamp(aVector V, aVector Min, aVector Max);
aVector        aVectorSaturate(aVector V);

aVector        aVectorAndInt(aVector V1, aVector V2);
aVector        aVectorAndCInt(aVector V1, aVector V2);
aVector        aVectorOrInt(aVector V1, aVector V2);
aVector        aVectorNorInt(aVector V1, aVector V2);
aVector        aVectorXorInt(aVector V1, aVector V2);

aVector        aVectorNegate(aVector V);
aVector        aVectorAdd(aVector V1, aVector V2);
aVector        aVectorAddAngles(aVector V1, aVector V2);
aVector        aVectorSubtract(aVector V1, aVector V2);
aVector        aVectorSubtractAngles(aVector V1, aVector V2);
aVector        aVectorMultiply(aVector V1, aVector V2);
aVector        aVectorMultiplyAdd(aVector V1, aVector V2, aVector V3);
aVector        aVectorDivide(aVector V1, aVector V2);
aVector        aVectorNegativeMultiplySubtract(aVector V1, aVector V2, aVector V3);
aVector        aVectorScale(aVector V, float ScaleFactor);
aVector        aVectorReciprocalEst(aVector V);
aVector        aVectorReciprocal(aVector V);
aVector        aVectorSqrtEst(aVector V);
aVector        aVectorSqrt(aVector V);
aVector        aVectorReciprocalSqrtEst(aVector V);
aVector        aVectorReciprocalSqrt(aVector V);
aVector        aVectorExp(aVector V);
aVector        aVectorLog(aVector V);
aVector        aVectorPow(aVector V1, aVector V2);
aVector        aVectorAbs(aVector V);
aVector        aVectorMod(aVector V1, aVector V2);
aVector        aVectorModAngles(aVector Angles);
aVector        aVectorSin(aVector V);
aVector        aVectorSinEst(aVector V);
aVector        aVectorCos(aVector V);
aVector        aVectorCosEst(aVector V);
void           aVectorSinCos(  aVector* pSin,   aVector* pCos,   aVector V);
void           aVectorSinCosEst(  aVector* pSin,   aVector* pCos,   aVector V);
aVector        aVectorTan(aVector V);
aVector        aVectorTanEst(aVector V);
aVector        aVectorSinH(aVector V);
aVector        aVectorCosH(aVector V);
aVector        aVectorTanH(aVector V);
aVector        aVectorASin(aVector V);
aVector        aVectorASinEst(aVector V);
aVector        aVectorACos(aVector V);
aVector        aVectorACosEst(aVector V);
aVector        aVectorATan(aVector V);
aVector        aVectorATanEst(aVector V);
aVector        aVectorATan2(aVector Y, aVector X);
aVector        aVectorATan2Est(aVector Y, aVector X);
aVector        aVectorLerp(aVector V0, aVector V1, float t);
aVector        aVectorLerpV(aVector V0, aVector V1, aVector T);
aVector        aVectorHermite(aVector Position0, aVector Tangent0, aVector Position1, aVector Tangent1, float t);
aVector        aVectorHermiteV(aVector Position0, aVector Tangent0, aVector Position1, aVector Tangent1, aVector T);
aVector        aVectorCatmullRom(aVector Position0, aVector Position1, aVector Position2, aVector Position3, float t);
aVector        aVectorCatmullRomV(aVector Position0, aVector Position1, aVector Position2, aVector Position3, aVector T);
aVector        aVectorBaryCentric(aVector Position0, aVector Position1, aVector Position2, float f, float g);
aVector        aVectorBaryCentricV(aVector Position0, aVector Position1, aVector Position2, aVector F, aVector G);
