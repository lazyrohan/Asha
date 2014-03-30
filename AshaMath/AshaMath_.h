//-------------------------------------------------------------------------------------
//AshaMath.h
//Math libary for 3D graphic programe
//Simpfied from Directx math lib
//Version:0.0
//Date:2012/09/29 by Rohan
//-------------------------------------------------------------------------------------

#pragma once

#ifndef _ASHAMATH_H_
#define _ASHAMATH_H_

namespace aMath
{

/****************************************************************************
 *
 * Constant definitions
 *
 ****************************************************************************/

//PI constants
const float aPI           = 3.141592654f; //pi
const float a2PI          = 6.283185307f; //2pi
const float a1_PI         = 0.318309886f; //1/pi
const float a1_2PI        = 0.159154943f; //1/(2*pi)
const float aPI_2         = 1.570796327f; //pi/2
const float aPI_4         = 0.785398163f; //pi/4
const float a2_SqrtPI     =1.1283791670f; //2/sqrt(pi)

//Common constants
const float aE            =2.71828182845f; //e constant
const float aLog2E        =1.44269504088f; //log2(e)
const float aLog10E       =0.43429448190f; //log10(e)
const float aLN2          =0.69314718055f; //loge(2)
const float aLN10         =2.30258509299f; //loge(10)
const float aSqrt2        =1.41421356237f; //sqrt(2)
const float a1_Sqrt2      =0.70710678118f; //1/sqrt(2)
/****************************************************************************
 *
 * Macros
 *
 ****************************************************************************/
// Unit conversion macros

inline float aDeg2Rad(float fDegrees) { return fDegrees * (aPI / 180.0f); } //Degree to radian
inline float aRad2Deg(float fRadians) { return fRadians * (180.0f / aPI); } //Radian to degree

/****************************************************************************
 *
 * Data types
 *
 ****************************************************************************/
//Some optimization need to add here


//------------------------------------------------------------------------------
 struct aVector
{
    union
    {
        float           data_f32[4];
		int             data_i32[4];
        unsigned int    data_u32[4];
    };
};

//------------------------------------------------------------------------------
//some optimization here
//------------------------------------------------------------------------------
// Vector operators
aVector    operator+ (aVector V);
aVector    operator- (aVector V);

aVector&   operator+= (aVector& V1, aVector V2);
aVector&   operator-= (aVector& V1, aVector V2);
aVector&   operator*= (aVector& V1, aVector V2);
aVector&   operator/= (aVector& V1, aVector V2);
aVector&   operator*= (aVector& V, float S);
aVector&   operator/= (aVector& V, float S);

aVector    operator+ (aVector V1, aVector V2);
aVector    operator- (aVector V1, aVector V2);
aVector    operator* (aVector V1, aVector V2);
aVector    operator/ (aVector V1, aVector V2);
aVector    operator* (aVector V, float S);
aVector    operator* (float S, aVector V);
aVector    operator/ (aVector V, float S);

//------------------------------------------------------------------------------
// Matrix type: Sixteen 32 bit floating point components

typedef struct aMat
{
    union
    {
		aVector r[4];
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };

    aMat() {}
    aMat(aVector R0, aVector R1, aVector R2, aVector R3) { r[0] = R0; r[1] = R1; r[2] = R2; r[3] = R3; }
    aMat(    float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);
    explicit aMat( const float *pArray);

	float    operator() (unsigned int Row, unsigned int Column) const { return m[Row][Column]; }
    float&   operator() (unsigned int Row, unsigned int Column) { return m[Row][Column]; }


    aMat&   operator= (const aMat& M) { r[0] = M.r[0]; r[1] = M.r[1]; r[2] = M.r[2]; r[3] = M.r[3]; return *this; }

    aMat    operator+ () const { return *this; }
    aMat    operator- () const;

    aMat&   operator+= (aMat M);
    aMat&   operator-= (aMat M);
    aMat&   operator*= (aMat M);
    aMat&   operator*= (float S);
    aMat&   operator/= (float S);

    aMat    operator+ (aMat M) const;
    aMat    operator- (aMat M) const;
    aMat    operator* (aMat M) const;
    aMat    operator* (float S) const;
    aMat    operator/ (float S) const;

    friend aMat operator* (float S, aMat M);
};

//------------------------------------------------------------------------------
// 2D Vector; 32 bit floating point components
struct aFloat2
{
    float x;
    float y;

    aFloat2() {}
    aFloat2(float _x, float _y) : x(_x), y(_y) {}
    explicit aFloat2(const float *pArray) : x(pArray[0]), y(pArray[1]) {}

    aFloat2& operator= (const aFloat2& Float2) { x = Float2.x; y = Float2.y; return *this; }
};

//------------------------------------------------------------------------------
// 2D Vector; 32 bit signed integer components
struct aInt2
{
    int x;
    int y;

    aInt2() {}
    aInt2(int _x, int _y) : x(_x), y(_y) {}
    explicit aInt2(const int *pArray) : x(pArray[0]), y(pArray[1]) {}

    aInt2& operator= (const aInt2& Int2) { x = Int2.x; y = Int2.y; return *this; }
};

// 2D Vector; 32 bit unsigned integer components
struct aUInt2
{
    unsigned int x;
    unsigned int y;

    aUInt2() {}
    aUInt2(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
    explicit aUInt2(  const unsigned int *pArray) : x(pArray[0]), y(pArray[1]) {}

    aUInt2& operator= (const aUInt2& UInt2) { x = UInt2.x; y = UInt2.y; return *this; }
};

//------------------------------------------------------------------------------
// 3D Vector; 32 bit floating point components
struct aFloat3
{
    float x;
    float y;
    float z;

    aFloat3() {}
    aFloat3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    explicit aFloat3(const float *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}

    aFloat3& operator= (const aFloat3& Float3) { x = Float3.x; y = Float3.y; z = Float3.z; return *this; }
};


//------------------------------------------------------------------------------
// 3D Vector; 32 bit signed integer components
struct aInt3
{
    int x;
    int y;
    int z;

    aInt3() {}
    aInt3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    explicit aInt3(const int *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}

    aInt3& operator= (const aInt3& i3) { x = i3.x; y = i3.y; z = i3.z; return *this; }
};

// 3D Vector; 32 bit unsigned integer components
struct aUInt3
{
    unsigned int x;
    unsigned int y;
    unsigned int z;

    aUInt3() {}
    aUInt3(unsigned int _x, unsigned int _y, unsigned int _z) : x(_x), y(_y), z(_z) {}
    explicit aUInt3(  const unsigned int *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}

    aUInt3& operator= (const aUInt3& u3) { x = u3.x; y = u3.y; z = u3.z; return *this; }
};

//------------------------------------------------------------------------------
// 4D Vector; 32 bit floating point components
struct aFloat4
{
    float x;
    float y;
    float z;
    float w;

    aFloat4() {}
    aFloat4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    explicit aFloat4(const float *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}

    aFloat4& operator= (const aFloat4& Float4) { x = Float4.x; y = Float4.y; z = Float4.z; w = Float4.w; return *this; }
};

//------------------------------------------------------------------------------
// 4D Vector; 32 bit signed integer components
struct aInt4
{
    int x;
    int y;
    int z;
    int w;

    aInt4() {}
    aInt4(int _x, int _y, int _z, int _w) : x(_x), y(_y), z(_z), w(_w) {}
    explicit aInt4(  const int *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}

    aInt4& operator= (const aInt4& Int4) { x = Int4.x; y = Int4.y; z = Int4.z; w = Int4.w; return *this; }
};

// 4D Vector; 32 bit unsigned integer components
struct aUInt4
{
    unsigned int x;
    unsigned int y;
    unsigned int z;
    unsigned int w;

    aUInt4() {}
    aUInt4(unsigned int _x, unsigned int _y, unsigned int _z, unsigned int _w) : x(_x), y(_y), z(_z), w(_w) {}
    explicit aUInt4(const unsigned int *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}

    aUInt4& operator= (const aUInt4& UInt4) { x = UInt4.x; y = UInt4.y; z = UInt4.z; w = UInt4.w; return *this; }
};

//------------------------------------------------------------------------------
// 3x3 Matrix: 32 bit floating point components
struct aFloat3X3
{
    union
    {
        struct
        {
            float _11, _12, _13;
            float _21, _22, _23;
            float _31, _32, _33;
        };
        float m[3][3];
    };

   aFloat3X3() {}
   aFloat3X3(float m00, float m01, float m02,
                float m10, float m11, float m12,
                float m20, float m21, float m22);
    explicit aFloat3X3(const float *pArray);

    float       operator() (unsigned int Row, unsigned int Column) const { return m[Row][Column]; }
    float&      operator() (unsigned int Row, unsigned int Column) { return m[Row][Column]; }

   aFloat3X3& operator= (const aFloat3X3& Float3x3);
};

//------------------------------------------------------------------------------
// 4x3 Matrix: 32 bit floating point components
struct aFloat4X3
{
    union
    {
        struct
        {
            float _11, _12, _13;
            float _21, _22, _23;
            float _31, _32, _33;
            float _41, _42, _43;
        };
        float m[4][3];
    };

    aFloat4X3() {}
    aFloat4X3(float m00, float m01, float m02,
                float m10, float m11, float m12,
                float m20, float m21, float m22,
                float m30, float m31, float m32);
    explicit aFloat4X3(_In_reads_(12) const float *pArray);

    float       operator() (unsigned int Row, unsigned int Column) const { return m[Row][Column]; }
    float&      operator() (unsigned int Row, unsigned int Column) { return m[Row][Column]; }

    aFloat4X3& operator= (const aFloat4X3& Float4x3);

};

//------------------------------------------------------------------------------
// 4x4 Matrix: 32 bit floating point components
struct aFloat4X4
{
    union
    {
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };

    aFloat4X4() {}
    aFloat4X4(float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33);
    explicit aFloat4X4(_In_reads_(16) const float *pArray);

    float       operator() (unsigned int Row, unsigned int Column) const { return m[Row][Column]; }
    float&      operator() (unsigned int Row, unsigned int Column) { return m[Row][Column]; }

    aFloat4X4& operator= (const aFloat4X4& Float4x4);
};

/****************************************************************************
 *
 * Data conversion operations
 *
 ****************************************************************************/

aVector        aConvertVectorIntToFloat(aVector VInt, unsigned int DivExponent);
aVector        aConvertVectorFloatToInt(aVector VFloat, unsigned int MulExponent);
aVector        aConvertVectorUIntToFloat(aVector VUInt, unsigned int DivExponent);
aVector        aConvertVectorFloatToUInt(aVector VFloat, unsigned int MulExponent);

/****************************************************************************
 *
 * Load operations
 *
 ****************************************************************************/

aVector        aLoadUInt(const unsigned int* pSource);
aVector        aLoadInt(const int* pSource);
aVector        aLoadFloat(const float* pSource);

aMat           aLoadFloat3x3(  const aFloat3X3* pSource);
aMat           aLoadFloat4x3(  const aFloat4X3* pSource);
aMat           aLoadFloat4x4(  const aFloat4X4* pSource);

/****************************************************************************
 *
 * Store operations
 *
 ****************************************************************************/

void            aStoreUInt(  unsigned int* pDestination,   aVector V);
void            aStoreInt(  int* pDestination,   aVector V);
void            aStoreFloat(  float* pDestination,   aVector V);

void            aStoreFloat3x3( aFloat3X3* pDestination,   aMat M);
void            aStoreFloat4x3(  aFloat4X3* pDestination,   aMat M);
void            aStoreFloat4x4(  aFloat4X4* pDestination,   aMat M);

/****************************************************************************
 *
 * General vector operations
 *
 ****************************************************************************/

aVector        aVectorZero();
aVector        aVectorSet(float x, float y, float z, float w);
aVector        aVectorSetInt(int x, int y,  int z, int w);
aVector        aVectorSetUInt(unsigned int x, unsigned int y, unsigned int z, unsigned int w);
aVector        aVectorReplicate(float Value);
aVector        aVectorReplicatePtr(  const float *pValue);
aVector        aVectorReplicateUInt(unsigned int Value);
aVector        aVectorReplicateInt(int Value);
aVector        aVectorReplicateIntPtr(  const int *pValue);
aVector        aVectorReplicateUIntPtr(  const unsigned int *pValue);
aVector        aVectorTrueInt();
aVector        aVectorFalseInt();
aVector        aVectorSplatX(aVector V);
aVector        aVectorSplatY(aVector V);
aVector        aVectorSplatZ(aVector V);
aVector        aVectorSplatW(aVector V);
aVector        aVectorSplatOne();
aVector        aVectorSplatInfinity();
aVector        aVectorSplatQNaN();
aVector        aVectorSplatEpsilon();
aVector        aVectorSplatSignMask();

float          aVectorGetByIndex(aVector V, unsigned int i);
float          aVectorGetX(aVector V);
float          aVectorGetY(aVector V);
float          aVectorGetZ(aVector V);
float          aVectorGetW(aVector V);

void           aVectorGetByIndexPtr(  float *f,   aVector V,   unsigned int i);
void           aVectorGetXPtr(  float *x,   aVector V);
void           aVectorGetYPtr(  float *y,   aVector V);
void           aVectorGetZPtr(  float *z,   aVector V);
void           aVectorGetWPtr(  float *w,   aVector V);

unsigned int   aVectorGetIntByIndex(aVector V, unsigned int i);
unsigned int   aVectorGetIntX(aVector V);
unsigned int   aVectorGetIntY(aVector V);
unsigned int   aVectorGetIntZ(aVector V);
unsigned int   aVectorGetIntW(aVector V);

void           aVectorGetIntByIndexPtr(  unsigned int *x,   aVector V,   unsigned int i);
void           aVectorGetIntXPtr(  unsigned int *x,   aVector V);
void           aVectorGetIntYPtr(  unsigned int *y,   aVector V);
void           aVectorGetIntZPtr(  unsigned int *z,   aVector V);
void           aVectorGetIntWPtr(  unsigned int *w,   aVector V);

aVector        aVectorSetByIndex(aVector V,float f, unsigned int i);
aVector        aVectorSetX(aVector V, float x);
aVector        aVectorSetY(aVector V, float y);
aVector        aVectorSetZ(aVector V, float z);
aVector        aVectorSetW(aVector V, float w);

aVector        aVectorSetByIndexPtr(  aVector V,   const float *f,   unsigned int i);
aVector        aVectorSetXPtr(  aVector V,   const float *x);
aVector        aVectorSetYPtr(  aVector V,   const float *y);
aVector        aVectorSetZPtr(  aVector V,   const float *z);
aVector        aVectorSetWPtr(  aVector V,   const float *w);

aVector        aVectorSetIntByIndex(aVector V, unsigned int x, unsigned int i);
aVector        aVectorSetIntX(aVector V, unsigned int x);
aVector        aVectorSetIntY(aVector V, unsigned int y);
aVector        aVectorSetIntZ(aVector V, unsigned int z);
aVector        aVectorSetIntW(aVector V, unsigned int w);

aVector        aVectorSetIntByIndexPtr(  aVector V,   const unsigned int *x,   unsigned int i);
aVector        aVectorSetIntXPtr(  aVector V,   const unsigned int *x);
aVector        aVectorSetIntYPtr(  aVector V,   const unsigned int *y);
aVector        aVectorSetIntZPtr(  aVector V,   const unsigned int *z);
aVector        aVectorSetIntWPtr(  aVector V,   const unsigned int *w);

aVector        aVectorSwizzle(aVector V, unsigned int E0, unsigned int E1, unsigned int E2, unsigned int E3);
aVector        aVectorPermute(aVector V1, aVector V2, unsigned int PermuteX, unsigned int PermuteY, unsigned int PermuteZ, unsigned int PermuteW);
aVector        aVectorSelectControl(unsigned int VectorIndex0, unsigned int VectorIndex1, unsigned int VectorIndex2, unsigned int VectorIndex3);
aVector        aVectorSelect(aVector V1, aVector V2, aVector Control);
aVector        aVectorMergeXY(aVector V1, aVector V2);
aVector        aVectorMergeZW(aVector V1, aVector V2);


aVector        aVectorShiftLeft(aVector V1, aVector V2, unsigned int Elements);
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

/****************************************************************************
 *
 * 3D vector operations
 *
 ****************************************************************************/

bool            aVector3Equal(aVector V1, aVector V2);
unsigned int    aVector3EqualR(aVector V1, aVector V2);
bool            aVector3EqualInt(aVector V1, aVector V2);
unsigned int    aVector3EqualIntR(aVector V1, aVector V2);
bool            aVector3NearEqual(aVector V1, aVector V2, aVector Epsilon);
bool            aVector3NotEqual(aVector V1, aVector V2);
bool            aVector3NotEqualInt(aVector V1, aVector V2);
bool            aVector3Greater(aVector V1, aVector V2);
unsigned int    aVector3GreaterR(aVector V1, aVector V2);
bool            aVector3GreaterOrEqual(aVector V1, aVector V2);
unsigned int    aVector3GreaterOrEqualR(aVector V1, aVector V2);
bool            aVector3Less(aVector V1, aVector V2);
bool            aVector3LessOrEqual(aVector V1, aVector V2);
bool            aVector3InBounds(aVector V, aVector Bounds);

bool            aVector3IsNaN(aVector V);
bool            aVector3IsInfinite(aVector V);

aVector         aVector3Dot(aVector V1, aVector V2);
aVector         aVector3Cross(aVector V1, aVector V2);
aVector         aVector3LengthSq(aVector V);
aVector         aVector3ReciprocalLengthEst(aVector V);
aVector         aVector3ReciprocalLength(aVector V);
aVector         aVector3LengthEst(aVector V);
aVector         aVector3Length(aVector V);
aVector         aVector3NormalizeEst(aVector V);
aVector         aVector3Normalize(aVector V);
aVector         aVector3ClampLength(aVector V, float LengthMin, float LengthMax);
aVector         aVector3ClampLengthV(aVector V, aVector LengthMin, aVector LengthMax);
aVector         aVector3Reflect(aVector Incident, aVector Normal);
aVector         aVector3Refract(aVector Incident, aVector Normal, float RefractionIndex);
aVector         aVector3RefractV(aVector Incident, aVector Normal, aVector RefractionIndex);
aVector         aVector3Orthogonal(aVector V);
aVector         aVector3AngleBetweenNormalsEst(aVector N1, aVector N2);
aVector         aVector3AngleBetweenNormals(aVector N1, aVector N2);
aVector         aVector3AngleBetweenVectors(aVector V1, aVector V2);
aVector         aVector3LinePointDistance(aVector LinePoint1, aVector LinePoint2, aVector Point);
void            aVector3ComponentsFromNormal(  aVector* pParallel,   aVector* pPerpendicular,   aVector V,   aVector Normal);
aVector         aVector3Rotate(aVector V, aVector RotationQuaternion);
aVector         aVector3InverseRotate(aVector V, aVector RotationQuaternion);
aVector         aVector3Transform(aVector V, aMat M);
aVector         aVector3TransformCoord(aVector V, aMat M);
aVector         aVector3TransformNormal(aVector V, aMat M);
aVector         aVector3Project(aVector V, float ViewportX, float ViewportY, float ViewportWidth, float ViewportHeight, float ViewportMinZ, float ViewportMaxZ, 
                                 aMat Projection, aMat View, aMat World);
aVector        aVector3Unproject(aVector V, float ViewportX, float ViewportY, float ViewportWidth, float ViewportHeight, float ViewportMinZ, float ViewportMaxZ, 
                                   aMat Projection, aMat View, aMat World);

/****************************************************************************
 *
 * 4D vector operations
 *
 ****************************************************************************/

bool            aVector4Equal(aVector V1, aVector V2);
unsigned int    aVector4EqualR(aVector V1, aVector V2);
bool            aVector4EqualInt(aVector V1, aVector V2);
unsigned int    aVector4EqualIntR(aVector V1, aVector V2);
bool            aVector4NearEqual(aVector V1, aVector V2, aVector Epsilon);
bool            aVector4NotEqual(aVector V1, aVector V2);
bool            aVector4NotEqualInt(aVector V1, aVector V2);
bool            aVector4Greater(aVector V1, aVector V2);
unsigned int    aVector4GreaterR(aVector V1, aVector V2);
bool            aVector4GreaterOrEqual(aVector V1, aVector V2);
unsigned int    aVector4GreaterOrEqualR(aVector V1, aVector V2);
bool            aVector4Less(aVector V1, aVector V2);
bool            aVector4LessOrEqual(aVector V1, aVector V2);
bool            aVector4InBounds(aVector V, aVector Bounds);

bool            aVector4IsNaN(aVector V);
bool            aVector4IsInfinite(aVector V);

aVector         aVector4Dot(aVector V1, aVector V2);
aVector         aVector4Cross(aVector V1, aVector V2, aVector V3);
aVector         aVector4LengthSq(aVector V);
aVector         aVector4ReciprocalLengthEst(aVector V);
aVector         aVector4ReciprocalLength(aVector V);
aVector         aVector4LengthEst(aVector V);
aVector         aVector4Length(aVector V);
aVector         aVector4NormalizeEst(aVector V);
aVector         aVector4Normalize(aVector V);
aVector         aVector4ClampLength(aVector V, float LengthMin, float LengthMax);
aVector         aVector4ClampLengthV(aVector V, aVector LengthMin, aVector LengthMax);
aVector         aVector4Reflect(aVector Incident, aVector Normal);
aVector         aVector4Refract(aVector Incident, aVector Normal, float RefractionIndex);
aVector         aVector4RefractV(aVector Incident, aVector Normal, aVector RefractionIndex);
aVector         aVector4Orthogonal(aVector V);
aVector         aVector4AngleBetweenNormalsEst(aVector N1, aVector N2);
aVector         aVector4AngleBetweenNormals(aVector N1, aVector N2);
aVector         aVector4AngleBetweenVectors(aVector V1, aVector V2);
aVector         aVector4Transform(aVector V, aMat M);

/****************************************************************************
 *
 * Matrix operations
 *
 ****************************************************************************/

bool            aMatrixIsNaN(aMat M);
bool            aMatrixIsInfinite(aMat M);
bool            aMatrixIsIdentity(aMat M);

aMat            aMatrixMultiply(aMat M1, aMat M2);
aMat            aMatrixMultiplyTranspose(aMat M1, aMat M2);
aMat            aMatrixTranspose(aMat M);
aMat            aMatrixInverse(aVector* pDeterminant,   aMat M);
aVector         aMatrixDeterminant(aMat M);
bool            aMatrixDecompose(  aVector *outScale,   aVector *outRotQuat,   aVector *outTrans,   aMat M);

aMat            aMatrixIdentity();
aMat            aMatrixSet(float m00, float m01, float m02, float m03,
                            float m10, float m11, float m12, float m13,
                            float m20, float m21, float m22, float m23,
                            float m30, float m31, float m32, float m33);
aMat            aMatrixTranslation(float OffsetX, float OffsetY, float OffsetZ);
aMat            aMatrixTranslationFromVector(aVector Offset);
aMat            aMatrixScaling(float ScaleX, float ScaleY, float ScaleZ);
aMat            aMatrixScalingFromVector(aVector Scale);
aMat            aMatrixRotationX(float Angle);
aMat            aMatrixRotationY(float Angle);
aMat            aMatrixRotationZ(float Angle);
aMat            aMatrixRotationRollPitchYaw(float Pitch, float Yaw, float Roll);
aMat            aMatrixRotationRollPitchYawFromVector(aVector Angles);
aMat            aMatrixRotationNormal(aVector NormalAxis, float Angle);
aMat            aMatrixRotationAxis(aVector Axis, float Angle);
aMat            aMatrixRotationQuaternion(aVector Quaternion);
aMat            aMatrixTransformation2D(aVector ScalingOrigin, float ScalingOrientation, aVector Scaling, 
                                         aVector RotationOrigin, float Rotation, aVector Translation);
aMat            aMatrixTransformation(aVector ScalingOrigin, aVector ScalingOrientationQuaternion, aVector Scaling, 
                                       aVector RotationOrigin, aVector RotationQuaternion, aVector Translation);
aMat            aMatrixAffineTransformation2D(aVector Scaling, aVector RotationOrigin, float Rotation, aVector Translation);
aMat            aMatrixAffineTransformation(aVector Scaling, aVector RotationOrigin, aVector RotationQuaternion, aVector Translation);
aMat            aMatrixReflect(aVector ReflectionPlane);
aMat            aMatrixShadow(aVector ShadowPlane, aVector LightPosition);

aMat            aMatrixLookAtLH(aVector EyePosition, aVector FocusPosition, aVector UpDirection);
aMat            aMatrixLookAtRH(aVector EyePosition, aVector FocusPosition, aVector UpDirection);
aMat            aMatrixLookToLH(aVector EyePosition, aVector EyeDirection, aVector UpDirection);
aMat            aMatrixLookToRH(aVector EyePosition, aVector EyeDirection, aVector UpDirection);
aMat            aMatrixPerspectiveLH(float ViewWidth, float ViewHeight, float NearZ, float FarZ);
aMat            aMatrixPerspectiveRH(float ViewWidth, float ViewHeight, float NearZ, float FarZ);
aMat            aMatrixPerspectiveFovLH(float FovAngleY, float AspectHByW, float NearZ, float FarZ);
aMat            aMatrixPerspectiveFovRH(float FovAngleY, float AspectHByW, float NearZ, float FarZ);
aMat            aMatrixPerspectiveOffCenterLH(float ViewLeft, float ViewRight, float ViewBottom, float ViewTop, float NearZ, float FarZ);
aMat            aMatrixPerspectiveOffCenterRH(float ViewLeft, float ViewRight, float ViewBottom, float ViewTop, float NearZ, float FarZ);
aMat            aMatrixOrthographicLH(float ViewWidth, float ViewHeight, float NearZ, float FarZ);
aMat            aMatrixOrthographicRH(float ViewWidth, float ViewHeight, float NearZ, float FarZ);
aMat            aMatrixOrthographicOffCenterLH(float ViewLeft, float ViewRight, float ViewBottom, float ViewTop, float NearZ, float FarZ);
aMat            aMatrixOrthographicOffCenterRH(float ViewLeft, float ViewRight, float ViewBottom, float ViewTop, float NearZ, float FarZ);

/****************************************************************************
 *
 * Plane operations
 *
 ****************************************************************************/

bool            aPlaneEqual(aVector P1, aVector P2);
bool            aPlaneNearEqual(aVector P1, aVector P2, aVector Epsilon);
bool            aPlaneNotEqual(aVector P1, aVector P2);

bool            aPlaneIsNaN(aVector P);
bool            aPlaneIsInfinite(aVector P);

aVector         aPlaneDot(aVector P, aVector V);
aVector         aPlaneDotCoord(aVector P, aVector V);
aVector         aPlaneDotNormal(aVector P, aVector V);
aVector         aPlaneNormalizeEst(aVector P);
aVector         aPlaneNormalize(aVector P);
aVector         aPlaneIntersectLine(aVector P, aVector LinePoint1, aVector LinePoint2);
void            aPlaneIntersectPlane(  aVector* pLinePoint1,   aVector* pLinePoint2,   aVector P1,   aVector P2);
aVector         aPlaneTransform(aVector P, aMat M);

aVector         aPlaneFromPointNormal(aVector Point, aVector Normal);
aVector         aPlaneFromPoints(aVector Point1, aVector Point2, aVector Point3);

/****************************************************************************
 *
 * Color operations
 *
 ****************************************************************************/

bool            aColorEqual(aVector C1, aVector C2);
bool            aColorNotEqual(aVector C1, aVector C2);
bool            aColorGreater(aVector C1, aVector C2);
bool            aColorGreaterOrEqual(aVector C1, aVector C2);
bool            aColorLess(aVector C1, aVector C2);
bool            aColorLessOrEqual(aVector C1, aVector C2);

bool            aColorIsNaN(aVector C);
bool            aColorIsInfinite(aVector C);

aVector        aColorNegative(aVector C);
aVector        aColorModulate(aVector C1, aVector C2);
aVector        aColorAdjustSaturation(aVector C, float Saturation);
aVector        aColorAdjustContrast(aVector C, float Contrast);

aVector        aColorRGBToHSL( aVector rgb );
aVector        aColorHSLToRGB( aVector hsl );

aVector        aColorRGBToHSV( aVector rgb );
aVector        aColorHSVToRGB( aVector hsv );

aVector        aColorRGBToYUV( aVector rgb );
aVector        aColorYUVToRGB( aVector yuv );

aVector        aColorRGBToYUV_HD( aVector rgb );
aVector        aColorYUVToRGB_HD( aVector yuv );

aVector        aColorRGBToXYZ( aVector rgb );
aVector        aColorXYZToRGB( aVector xyz );

aVector        aColorXYZToSRGB( aVector xyz );
aVector        aColorSRGBToXYZ( aVector srgb );

/****************************************************************************
 *
 * Miscellaneous operations
 *
 ****************************************************************************/

bool            aVerifyCPUSupport();

aVector         aFresnelTerm(aVector CosIncidentAngle, aVector RefractionIndex);

bool            aScalarNearEqual(float S1, float S2, float Epsilon);
float           aScalarModAngle(float Value);

float           aScalarSin(float Value);
float           aScalarSinEst(float Value);

float           aScalarCos(float Value);
float           aScalarCosEst(float Value);

void            aScalarSinCos(  float* pSin,   float* pCos, float Value);
void            aScalarSinCosEst(  float* pSin,   float* pCos, float Value);

float           aScalarASin(float Value);
float           aScalarASinEst(float Value);

float           aScalarACos(float Value);
float           aScalarACosEst(float Value);

/****************************************************************************
 *
 * Templates
 *
 ****************************************************************************/
template<class T> inline T aMin(T a, T b) { return (a < b) ? a : b; }
template<class T> inline T aMax(T a, T b) { return (a > b) ? a : b; }

//------------------------------------------------------------------------------


};

#endif

