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
// Unit conversion

inline float aDeg2Rad(float fDegrees) { return fDegrees * (a_PI / 180.0f); } //Degree to radian
inline float aRad2Deg(float fRadians) { return fRadians * (180.0f / a_PI); } //Radian to degree

// Condition register evaluation proceeding a recording (R) comparison


/****************************************************************************
 *
 * Data types
 *
 ****************************************************************************/
//Some optimization need to add here


//------------------------------------------------------------------------------
typedef struct __aVector4
{
    union
    {
        float           vector4_f32[4];
		int             vector4_i32[4];
        unsigned int    vector4_u32[4];
    };
};

//------------------------------------------------------------------------------
//some optimization here

//------------------------------------------------------------------------------
// Vector intrinsic: Four 32 bit floating point components aligned on a 16 byte 
// boundary and mapped to hardware vector registers
typedef __aVector4       aVector;
typedef const aVector    faVector;
typedef const aVector&   faVector;
//------------------------------------------------------------------------------
// Conversion types for constants
__declspec(align(16)) struct aVectorF32
{
    union
    {
        float f[4];
		aVector v;
    };

    inline operator aVector() const { return v; }
    inline operator const float*() const { return f; }

};

__declspec(align(16)) struct aVectorI32
{
    union
    {
        int i[4];
        aVector v;
    };

    inline operator aVector() const { return v; }

};

__declspec(align(16)) struct aVectorU8
{
    union
    {
        unsigned char u[16];
        aVector       v;
    };

    inline operator aVector() const { return v; }

};

__declspec(align(16)) struct aVectorU32
{
    union
    {
        unsigned int u[4];
        aVector      v;
    };

    inline operator aVector() const { return v; }

};

//------------------------------------------------------------------------------
// Vector operators
aVector    operator+ (faVector V);
aVector    operator- (faVector V);

aVector&   operator+= (aVector& V1, faVector V2);
aVector&   operator-= (aVector& V1, faVector V2);
aVector&   operator*= (aVector& V1, faVector V2);
aVector&   operator/= (aVector& V1, faVector V2);
aVector&   operator*= (aVector& V, float S);
aVector&   operator/= (aVector& V, float S);

aVector    operator+ (faVector V1, faVector V2);
aVector    operator- (faVector V1, faVector V2);
aVector    operator* (faVector V1, faVector V2);
aVector    operator/ (faVector V1, faVector V2);
aVector    operator* (faVector V, float S);
aVector    operator* (float S, faVector V);
aVector    operator/ (faVector V, float S);

//------------------------------------------------------------------------------
// Matrix type: Sixteen 32 bit floating point components aligned on a
// 16 byte boundary and mapped to four hardware vector registers
struct aMat;
typedef const aMat faMat;
typedef const aMat& faMat;
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
    aMat(faVector R0, faVector R1, faVector R2, faVector R3) { r[0] = R0; r[1] = R1; r[2] = R2; r[3] = R3; }
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

    aMat&   operator+= (faMat M);
    aMat&   operator-= (faMat M);
    aMat&   operator*= (faMat M);
    aMat&   operator*= (float S);
    aMat&   operator/= (float S);

    aMat    operator+ (faMat M) const;
    aMat    operator- (faMat M) const;
    aMat    operator* (faMat M) const;
    aMat    operator* (float S) const;
    aMat    operator/ (float S) const;

    friend aMat operator* (float S, faMat M);
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

// 2D Vector; 32 bit floating point components aligned on a 16 byte boundary
__declspec(align(16)) struct aFloat2A : public aFloat2
{
    aFloat2A() : aFloat2() {}
    aFloat2A(float _x, float _y) : aFloat2(_x, _y) {}
    explicit aFloat2A(  const float *pArray) : aFloat2(pArray) {}

    aFloat2A& operator= (const aFloat2A& Float2) { x = Float2.x; y = Float2.y; return *this; }
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

// 3D Vector; 32 bit floating point components aligned on a 16 byte boundary
__declspec(align(16)) struct aFloat3A : public aFloat3
{
    aFloat3A() : aFloat3() {}
    aFloat3A(float _x, float _y, float _z) : aFloat3(_x, _y, _z) {}
    explicit aFloat3A(const float *pArray) : aFloat3(pArray) {}

    aFloat3A& operator= (const aFloat3A& Float3) { x = Float3.x; y = Float3.y; z = Float3.z; return *this; }
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

// 4D Vector; 32 bit floating point components aligned on a 16 byte boundary
__declspec(align(16)) struct aFloat4A : public aFloat4
{
    aFloat4A() : aFloat4() {}
    aFloat4A(float _x, float _y, float _z, float _w) : aFloat4(_x, _y, _z, _w) {}
    explicit aFloat4A(  const float *pArray) : aFloat4(pArray) {}

    aFloat4A& operator= (const aFloat4A& Float4) { x = Float4.x; y = Float4.y; z = Float4.z; w = Float4.w; return *this; }
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

// 4x3 Matrix: 32 bit floating point components aligned on a 16 byte boundary
__declspec(align(16)) struct aFloatA4X3 : public aFloat4X3
{
    aFloatA4X3() : aFloat4X3() {}
    aFloatA4X3(float m00, float m01, float m02,
                float m10, float m11, float m12,
                float m20, float m21, float m22,
                float m30, float m31, float m32) :
        aFloat4X3(m00,m01,m02,m10,m11,m12,m20,m21,m22,m30,m31,m32) {}
    explicit aFloatA4X3(const float *pArray) : aFloat4X3(pArray) {}

    float       operator() (unsigned int Row, unsigned int Column) const { return m[Row][Column]; }
    float&      operator() (unsigned int Row, unsigned int Column) { return m[Row][Column]; }

    aFloatA4X3& operator= (const aFloatA4X3& Float4x3);
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

// 4x4 Matrix: 32 bit floating point components aligned on a 16 byte boundary
__declspec(align(16)) struct aFloatA4X4 : public aFloat4X4
{
    aFloatA4X4() : aFloat4X4() {}
    aFloatA4X4(float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33)
        : aFloat4X4(m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33) {}
    explicit aFloatA4X4( const float *pArray) : aFloat4X4(pArray) {}

    float       operator() (unsigned int Row, unsigned int Column) const { return m[Row][Column]; }
    float&      operator() (unsigned int Row, unsigned int Column) { return m[Row][Column]; }

    aFloatA4X4& operator= (const aFloatA4X4& Float4x4);
};

////////////////////////////////////////////////////////////////////////////////


/****************************************************************************
 *
 * Data conversion operations
 *
 ****************************************************************************/

aVector        aConvertVectorIntToFloat(faVector VInt, unsigned int DivExponent);
aVector        aConvertVectorFloatToInt(faVector VFloat, unsigned int MulExponent);
aVector        aConvertVectorUIntToFloat(faVector VUInt, unsigned int DivExponent);
aVector        aConvertVectorFloatToUInt(faVector VFloat, unsigned int MulExponent);

/****************************************************************************
 *
 * Load operations
 *
 ****************************************************************************/

aVector        aLoadInt(const unsigned int* pSource);
aVector        aLoadFloat(const float* pSource);

aVector        aLoadInt2(const unsigned int* pSource);
aVector        aLoadInt2A(  const unsigned int* PSource);
aVector        aLoadFloat2(  const aFloat2* pSource);
aVector        aLoadFloat2A(  const aFloat2A* pSource);
aVector        aLoadSInt2(  const aInt2* pSource);
aVector        aLoadUInt2(  const aUInt2* pSource);

aVector        aLoadInt3(  const unsigned int* pSource);
aVector        aLoadInt3A(  const unsigned int* pSource);
aVector        aLoadFloat3(  const aFloat3* pSource);
aVector        aLoadFloat3A(  const aFloat3A* pSource);
aVector        aLoadSInt3(  const aInt3* pSource);
aVector        aLoadUInt3(  const aUInt3* pSource);

aVector        aLoadInt4(  const unsigned int* pSource);
aVector        aLoadInt4A(  const unsigned int* pSource);
aVector        aLoadFloat4(  const aFloat4* pSource);
aVector        aLoadFloat4A(  const aFloat4A* pSource);
aVector        aLoadSInt4(  const aInt4* pSource);
aVector        aLoadUInt4(  const aUInt4* pSource);

aMat           aLoadFloat3x3(  const aFloat3X3* pSource);
aMat           aLoadFloat4x3(  const aFloat4X3* pSource);
aMat           aLoadFloat4x3A(  const aFloatA4X3* pSource);
aMat           aLoadFloat4x4(  const aFloat4X4* pSource);
aMat           aLoadFloat4x4A(  const aFloatA4X4* pSource);

/****************************************************************************
 *
 * Store operations
 *
 ****************************************************************************/

void            aStoreInt(  unsigned int* pDestination,   faVector V);
void            aStoreFloat(  float* pDestination,   faVector V);

void            aStoreInt2(  unsigned int* pDestination,   faVector V);
void            aStoreInt2A(  unsigned int* pDestination,   faVector V);
void            aStoreFloat2(  aFloat2* pDestination,   faVector V);
void            aStoreFloat2A(  aFloat2A* pDestination,   faVector V);
void            aStoreSInt2(  aInt2* pDestination,   faVector V);
void            aStoreUInt2(  aUInt2* pDestination,   faVector V);

void            aStoreInt3(  unsigned int* pDestination,   faVector V);
void            aStoreInt3A(  unsigned int* pDestination,   faVector V);
void            aStoreFloat3(  aFloat3* pDestination,   faVector V);
void            aStoreFloat3A(  aFloat3A* pDestination,   faVector V);
void            aStoreSInt3(  aInt3* pDestination,   faVector V);
void            aStoreUInt3(  aUInt3* pDestination,   faVector V);

void            aStoreInt4(  unsigned int* pDestination,   faVector V);
void            aStoreInt4A(  unsigned int* pDestination,   faVector V);
void            aStoreFloat4(  aFloat4* pDestination,   faVector V);
void            aStoreFloat4A(  aFloat4A* pDestination,   faVector V);
void            aStoreSInt4(  aInt4* pDestination,   faVector V);
void            aStoreUInt4(  aUInt4* pDestination,   faVector V);

void            aStoreFloat3x3( aFloat3X3* pDestination,   faMat M);
void            aStoreFloat4x3(  aFloat4X3* pDestination,   faMat M);
void            aStoreFloat4x3A(  aFloatA4X3* pDestination,   faMat M);
void            aStoreFloat4x4(  aFloat4X4* pDestination,   faMat M);
void            aStoreFloat4x4A(  aFloatA4X4* pDestination,   faMat M);

/****************************************************************************
 *
 * General vector operations
 *
 ****************************************************************************/

aVector        aVectorZero();
aVector        aVectorSet(float x, float y, float z, float w);
aVector        aVectorSetInt(unsigned int x, unsigned int y, unsigned int z, unsigned int w);
aVector        aVectorReplicate(float Value);
aVector        aVectorReplicatePtr(  const float *pValue);
aVector        aVectorReplicateInt(unsigned int Value);
aVector        aVectorReplicateIntPtr(  const unsigned int *pValue);
aVector        aVectorTrueInt();
aVector        aVectorFalseInt();
aVector        aVectorSplatX(faVector V);
aVector        aVectorSplatY(faVector V);
aVector        aVectorSplatZ(faVector V);
aVector        aVectorSplatW(faVector V);
aVector        aVectorSplatOne();
aVector        aVectorSplatInfinity();
aVector        aVectorSplatQNaN();
aVector        aVectorSplatEpsilon();
aVector        aVectorSplatSignMask();

float           aVectorGetByIndex(faVector V, unsigned int i);
float           aVectorGetX(faVector V);
float           aVectorGetY(faVector V);
float           aVectorGetZ(faVector V);
float           aVectorGetW(faVector V);

void            aVectorGetByIndexPtr(  float *f,   faVector V,   unsigned int i);
void            aVectorGetXPtr(  float *x,   faVector V);
void            aVectorGetYPtr(  float *y,   faVector V);
void            aVectorGetZPtr(  float *z,   faVector V);
void            aVectorGetWPtr(  float *w,   faVector V);

unsigned int        aVectorGetIntByIndex(faVector V, unsigned int i);
unsigned int        aVectorGetIntX(faVector V);
unsigned int        aVectorGetIntY(faVector V);
unsigned int        aVectorGetIntZ(faVector V);
unsigned int        aVectorGetIntW(faVector V);

void            aVectorGetIntByIndexPtr(  unsigned int *x,   faVector V,   unsigned int i);
void            aVectorGetIntXPtr(  unsigned int *x,   faVector V);
void            aVectorGetIntYPtr(  unsigned int *y,   faVector V);
void            aVectorGetIntZPtr(  unsigned int *z,   faVector V);
void            aVectorGetIntWPtr(  unsigned int *w,   faVector V);

aVector        aVectorSetByIndex(faVector V,float f, unsigned int i);
aVector        aVectorSetX(faVector V, float x);
aVector        aVectorSetY(faVector V, float y);
aVector        aVectorSetZ(faVector V, float z);
aVector        aVectorSetW(faVector V, float w);

aVector        aVectorSetByIndexPtr(  faVector V,   const float *f,   unsigned int i);
aVector        aVectorSetXPtr(  faVector V,   const float *x);
aVector        aVectorSetYPtr(  faVector V,   const float *y);
aVector        aVectorSetZPtr(  faVector V,   const float *z);
aVector        aVectorSetWPtr(  faVector V,   const float *w);

aVector        aVectorSetIntByIndex(faVector V, unsigned int x, unsigned int i);
aVector        aVectorSetIntX(faVector V, unsigned int x);
aVector        aVectorSetIntY(faVector V, unsigned int y);
aVector        aVectorSetIntZ(faVector V, unsigned int z);
aVector        aVectorSetIntW(faVector V, unsigned int w);

aVector        aVectorSetIntByIndexPtr(  faVector V,   const unsigned int *x,   unsigned int i);
aVector        aVectorSetIntXPtr(  faVector V,   const unsigned int *x);
aVector        aVectorSetIntYPtr(  faVector V,   const unsigned int *y);
aVector        aVectorSetIntZPtr(  faVector V,   const unsigned int *z);
aVector        aVectorSetIntWPtr(  faVector V,   const unsigned int *w);

aVector        aVectorSwizzle(faVector V, unsigned int E0, unsigned int E1, unsigned int E2, unsigned int E3);
aVector        aVectorPermute(faVector V1, faVector V2, unsigned int PermuteX, unsigned int PermuteY, unsigned int PermuteZ, unsigned int PermuteW);
aVector        aVectorSelectControl(unsigned int VectorIndex0, unsigned int VectorIndex1, unsigned int VectorIndex2, unsigned int VectorIndex3);
aVector        aVectorSelect(faVector V1, faVector V2, faVector Control);
aVector        aVectorMergeXY(faVector V1, faVector V2);
aVector        aVectorMergeZW(faVector V1, faVector V2);


aVector aVectorShiftLeft(faVector V1, faVector V2, unsigned int Elements);
aVector aVectorRotateLeft(faVector V, unsigned int Elements);
aVector aVectorRotateRight(faVector V, unsigned int Elements);
aVector aVectorInsert(faVector VD, faVector VS, unsigned int VSLeftRotateElements,
                        unsigned int Select0, unsigned int Select1, unsigned int Select2, unsigned int Select3);

aVector        aVectorEqual(faVector V1, faVector V2);
aVector        aVectorEqualR(  unsigned int* pCR,   faVector V1,   faVector V2);
aVector        aVectorEqualInt(faVector V1, faVector V2);
aVector        aVectorEqualIntR(  unsigned int* pCR,   faVector V,   faVector V2);
aVector        aVectorNearEqual(faVector V1, faVector V2, faVector Epsilon);
aVector        aVectorNotEqual(faVector V1, faVector V2);
aVector        aVectorNotEqualInt(faVector V1, faVector V2);
aVector        aVectorGreater(faVector V1, faVector V2);
aVector        aVectorGreaterR(  unsigned int* pCR,   faVector V1,   faVector V2);
aVector        aVectorGreaterOrEqual(faVector V1, faVector V2);
aVector        aVectorGreaterOrEqualR(  unsigned int* pCR,   faVector V1,   faVector V2);
aVector        aVectorLess(faVector V1, faVector V2);
aVector        aVectorLessOrEqual(faVector V1, faVector V2);
aVector        aVectorInBounds(faVector V, faVector Bounds);
aVector        aVectorInBoundsR(  unsigned int* pCR,   faVector V,   faVector Bounds);

aVector        aVectorIsNaN(faVector V);
aVector        aVectorIsInfinite(faVector V);

aVector        aVectorMin(faVector V1,faVector V2);
aVector        aVectorMax(faVector V1, faVector V2);
aVector        aVectorRound(faVector V);
aVector        aVectorTruncate(faVector V);
aVector        aVectorFloor(faVector V);
aVector        aVectorCeiling(faVector V);
aVector        aVectorClamp(faVector V, faVector Min, faVector Max);
aVector        aVectorSaturate(faVector V);

aVector        aVectorAndInt(faVector V1, faVector V2);
aVector        aVectorAndCInt(faVector V1, faVector V2);
aVector        aVectorOrInt(faVector V1, faVector V2);
aVector        aVectorNorInt(faVector V1, faVector V2);
aVector        aVectorXorInt(faVector V1, faVector V2);

aVector        aVectorNegate(faVector V);
aVector        aVectorAdd(faVector V1, faVector V2);
aVector        aVectorAddAngles(faVector V1, faVector V2);
aVector        aVectorSubtract(faVector V1, faVector V2);
aVector        aVectorSubtractAngles(faVector V1, faVector V2);
aVector        aVectorMultiply(faVector V1, faVector V2);
aVector        aVectorMultiplyAdd(faVector V1, faVector V2, faVector V3);
aVector        aVectorDivide(faVector V1, faVector V2);
aVector        aVectorNegativeMultiplySubtract(faVector V1, faVector V2, faVector V3);
aVector        aVectorScale(faVector V, float ScaleFactor);
aVector        aVectorReciprocalEst(faVector V);
aVector        aVectorReciprocal(faVector V);
aVector        aVectorSqrtEst(faVector V);
aVector        aVectorSqrt(faVector V);
aVector        aVectorReciprocalSqrtEst(faVector V);
aVector        aVectorReciprocalSqrt(faVector V);
aVector        aVectorExp(faVector V);
aVector        aVectorLog(faVector V);
aVector        aVectorPow(faVector V1, faVector V2);
aVector        aVectorAbs(faVector V);
aVector        aVectorMod(faVector V1, faVector V2);
aVector        aVectorModAngles(faVector Angles);
aVector        aVectorSin(faVector V);
aVector        aVectorSinEst(faVector V);
aVector        aVectorCos(faVector V);
aVector        aVectorCosEst(faVector V);
void            aVectorSinCos(  aVector* pSin,   aVector* pCos,   faVector V);
void            aVectorSinCosEst(  aVector* pSin,   aVector* pCos,   faVector V);
aVector        aVectorTan(faVector V);
aVector        aVectorTanEst(faVector V);
aVector        aVectorSinH(faVector V);
aVector        aVectorCosH(faVector V);
aVector        aVectorTanH(faVector V);
aVector        aVectorASin(faVector V);
aVector        aVectorASinEst(faVector V);
aVector        aVectorACos(faVector V);
aVector        aVectorACosEst(faVector V);
aVector        aVectorATan(faVector V);
aVector        aVectorATanEst(faVector V);
aVector        aVectorATan2(faVector Y, faVector X);
aVector        aVectorATan2Est(faVector Y, faVector X);
aVector        aVectorLerp(faVector V0, faVector V1, float t);
aVector        aVectorLerpV(faVector V0, faVector V1, faVector T);
aVector        aVectorHermite(faVector Position0, faVector Tangent0, faVector Position1, faVector Tangent1, float t);
aVector        aVectorHermiteV(faVector Position0, faVector Tangent0, faVector Position1, faVector Tangent1, faVector T);
aVector        aVectorCatmullRom(faVector Position0, faVector Position1, faVector Position2, faVector Position3, float t);
aVector        aVectorCatmullRomV(faVector Position0, faVector Position1, faVector Position2, faVector Position3, faVector T);
aVector        aVectorBaryCentric(faVector Position0, faVector Position1, faVector Position2, float f, float g);
aVector        aVectorBaryCentricV(faVector Position0, faVector Position1, faVector Position2, faVector F, faVector G);

/****************************************************************************
 *
 * 2D vector operations
 *
 ****************************************************************************/

bool             aVector2Equal(faVector V1, faVector V2);
unsigned int        aVector2EqualR(faVector V1, faVector V2);
bool             aVector2EqualInt(faVector V1, faVector V2);
unsigned int         aVector2EqualIntR(faVector V1, faVector V2);
bool             aVector2NearEqual(faVector V1, faVector V2, faVector Epsilon);
bool             aVector2NotEqual(faVector V1, faVector V2);
bool             aVector2NotEqualInt(faVector V1, faVector V2);
bool            aVector2Greater(faVector V1, faVector V2);
unsigned int        aVector2GreaterR(faVector V1, faVector V2);
bool            aVector2GreaterOrEqual(faVector V1, faVector V2);
unsigned int        aVector2GreaterOrEqualR(faVector V1, faVector V2);
bool            aVector2Less(faVector V1, faVector V2);
bool            aVector2LessOrEqual(faVector V1, faVector V2);
bool            aVector2InBounds(faVector V, faVector Bounds);

bool            aVector2IsNaN(faVector V);
bool            aVector2IsInfinite(faVector V);

aVector        aVector2Dot(faVector V1, faVector V2);
aVector        aVector2Cross(faVector V1, faVector V2);
aVector        aVector2LengthSq(faVector V);
aVector        aVector2ReciprocalLengthEst(faVector V);
aVector        aVector2ReciprocalLength(faVector V);
aVector        aVector2LengthEst(faVector V);
aVector        aVector2Length(faVector V);
aVector        aVector2NormalizeEst(faVector V);
aVector        aVector2Normalize(faVector V);
aVector        aVector2ClampLength(faVector V, float LengthMin, float LengthMax);
aVector        aVector2ClampLengthV(faVector V, faVector LengthMin, faVector LengthMax);
aVector        aVector2Reflect(faVector Incident, faVector Normal);
aVector        aVector2Refract(faVector Incident, faVector Normal, float RefractionIndex);
aVector        aVector2RefractV(faVector Incident, faVector Normal, faVector RefractionIndex);
aVector        aVector2Orthogonal(faVector V);
aVector        aVector2AngleBetweenNormalsEst(faVector N1, faVector N2);
aVector        aVector2AngleBetweenNormals(faVector N1, faVector N2);
aVector        aVector2AngleBetweenVectors(faVector V1, faVector V2);
aVector        aVector2LinePointDistance(faVector LinePoint1, faVector LinePoint2, faVector Point);
aVector        aVector2IntersectLine(faVector Line1Point1, faVector Line1Point2, faVector Line2Point1, faVector Line2Point2);
aVector        aVector2Transform(faVector V, faMat M);

/****************************************************************************
 *
 * 3D vector operations
 *
 ****************************************************************************/

bool            aVector3Equal(faVector V1, faVector V2);
unsigned int        aVector3EqualR(faVector V1, faVector V2);
bool            aVector3EqualInt(faVector V1, faVector V2);
unsigned int        aVector3EqualIntR(faVector V1, faVector V2);
bool            aVector3NearEqual(faVector V1, faVector V2, faVector Epsilon);
bool            aVector3NotEqual(faVector V1, faVector V2);
bool            aVector3NotEqualInt(faVector V1, faVector V2);
bool            aVector3Greater(faVector V1, faVector V2);
unsigned int        aVector3GreaterR(faVector V1, faVector V2);
bool            aVector3GreaterOrEqual(faVector V1, faVector V2);
unsigned int        aVector3GreaterOrEqualR(faVector V1, faVector V2);
bool            aVector3Less(faVector V1, faVector V2);
bool            aVector3LessOrEqual(faVector V1, faVector V2);
bool            aVector3InBounds(faVector V, faVector Bounds);

bool            aVector3IsNaN(faVector V);
bool            aVector3IsInfinite(faVector V);

aVector        aVector3Dot(faVector V1, faVector V2);
aVector        aVector3Cross(faVector V1, faVector V2);
aVector        aVector3LengthSq(faVector V);
aVector        aVector3ReciprocalLengthEst(faVector V);
aVector        aVector3ReciprocalLength(faVector V);
aVector        aVector3LengthEst(faVector V);
aVector        aVector3Length(faVector V);
aVector        aVector3NormalizeEst(faVector V);
aVector        aVector3Normalize(faVector V);
aVector        aVector3ClampLength(faVector V, float LengthMin, float LengthMax);
aVector        aVector3ClampLengthV(faVector V, faVector LengthMin, faVector LengthMax);
aVector        aVector3Reflect(faVector Incident, faVector Normal);
aVector        aVector3Refract(faVector Incident, faVector Normal, float RefractionIndex);
aVector        aVector3RefractV(faVector Incident, faVector Normal, faVector RefractionIndex);
aVector        aVector3Orthogonal(faVector V);
aVector        aVector3AngleBetweenNormalsEst(faVector N1, faVector N2);
aVector        aVector3AngleBetweenNormals(faVector N1, faVector N2);
aVector        aVector3AngleBetweenVectors(faVector V1, faVector V2);
aVector        aVector3LinePointDistance(faVector LinePoint1, faVector LinePoint2, faVector Point);
void            aVector3ComponentsFromNormal(  aVector* pParallel,   aVector* pPerpendicular,   faVector V,   faVector Normal);
aVector        aVector3Rotate(faVector V, faVector RotationQuaternion);
aVector        aVector3InverseRotate(faVector V, faVector RotationQuaternion);
aVector        aVector3Transform(faVector V, faMat M);
aVector        aVector3TransformCoord(faVector V, faMat M);
aVector        aVector3TransformNormal(faVector V, faMat M);
aVector        aVector3Project(faVector V, float ViewportX, float ViewportY, float ViewportWidth, float ViewportHeight, float ViewportMinZ, float ViewportMaxZ, 
                                 faMat Projection, faMat View, faMat World);
aVector        aVector3Unproject(faVector V, float ViewportX, float ViewportY, float ViewportWidth, float ViewportHeight, float ViewportMinZ, float ViewportMaxZ, 
                                   faMat Projection, faMat View, faMat World);

/****************************************************************************
 *
 * 4D vector operations
 *
 ****************************************************************************/

bool            aVector4Equal(faVector V1, faVector V2);
unsigned int        aVector4EqualR(faVector V1, faVector V2);
bool            aVector4EqualInt(faVector V1, faVector V2);
unsigned int        aVector4EqualIntR(faVector V1, faVector V2);
bool            aVector4NearEqual(faVector V1, faVector V2, faVector Epsilon);
bool            aVector4NotEqual(faVector V1, faVector V2);
bool            aVector4NotEqualInt(faVector V1, faVector V2);
bool            aVector4Greater(faVector V1, faVector V2);
unsigned int        aVector4GreaterR(faVector V1, faVector V2);
bool            aVector4GreaterOrEqual(faVector V1, faVector V2);
unsigned int        aVector4GreaterOrEqualR(faVector V1, faVector V2);
bool            aVector4Less(faVector V1, faVector V2);
bool            aVector4LessOrEqual(faVector V1, faVector V2);
bool            aVector4InBounds(faVector V, faVector Bounds);

bool            aVector4IsNaN(faVector V);
bool            aVector4IsInfinite(faVector V);

aVector        aVector4Dot(faVector V1, faVector V2);
aVector        aVector4Cross(faVector V1, faVector V2, faVector V3);
aVector        aVector4LengthSq(faVector V);
aVector        aVector4ReciprocalLengthEst(faVector V);
aVector        aVector4ReciprocalLength(faVector V);
aVector        aVector4LengthEst(faVector V);
aVector        aVector4Length(faVector V);
aVector        aVector4NormalizeEst(faVector V);
aVector        aVector4Normalize(faVector V);
aVector        aVector4ClampLength(faVector V, float LengthMin, float LengthMax);
aVector        aVector4ClampLengthV(faVector V, faVector LengthMin, faVector LengthMax);
aVector        aVector4Reflect(faVector Incident, faVector Normal);
aVector        aVector4Refract(faVector Incident, faVector Normal, float RefractionIndex);
aVector        aVector4RefractV(faVector Incident, faVector Normal, faVector RefractionIndex);
aVector        aVector4Orthogonal(faVector V);
aVector        aVector4AngleBetweenNormalsEst(faVector N1, faVector N2);
aVector        aVector4AngleBetweenNormals(faVector N1, faVector N2);
aVector        aVector4AngleBetweenVectors(faVector V1, faVector V2);
aVector        aVector4Transform(faVector V, faMat M);

/****************************************************************************
 *
 * Matrix operations
 *
 ****************************************************************************/

bool            aMatrixIsNaN(faMat M);
bool            aMatrixIsInfinite(faMat M);
bool            aMatrixIsIdentity(faMat M);

aMat            aMatrixMultiply(faMat M1, faMat M2);
aMat            aMatrixMultiplyTranspose(faMat M1, faMat M2);
aMat            aMatrixTranspose(faMat M);
aMat            aMatrixInverse(aVector* pDeterminant,   faMat M);
aVector         aMatrixDeterminant(faMat M);
bool            aMatrixDecompose(  aVector *outScale,   aVector *outRotQuat,   aVector *outTrans,   faMat M);

aMat           aMatrixIdentity();
aMat           aMatrixSet(float m00, float m01, float m02, float m03,
                            float m10, float m11, float m12, float m13,
                            float m20, float m21, float m22, float m23,
                            float m30, float m31, float m32, float m33);
aMat           aMatrixTranslation(float OffsetX, float OffsetY, float OffsetZ);
aMat           aMatrixTranslationFromVector(faVector Offset);
aMat           aMatrixScaling(float ScaleX, float ScaleY, float ScaleZ);
aMat           aMatrixScalingFromVector(faVector Scale);
aMat           aMatrixRotationX(float Angle);
aMat           aMatrixRotationY(float Angle);
aMat           aMatrixRotationZ(float Angle);
aMat           aMatrixRotationRollPitchYaw(float Pitch, float Yaw, float Roll);
aMat           aMatrixRotationRollPitchYawFromVector(faVector Angles);
aMat           aMatrixRotationNormal(faVector NormalAxis, float Angle);
aMat           aMatrixRotationAxis(faVector Axis, float Angle);
aMat           aMatrixRotationQuaternion(faVector Quaternion);
aMat           aMatrixTransformation2D(faVector ScalingOrigin, float ScalingOrientation, faVector Scaling, 
                                         faVector RotationOrigin, float Rotation, faVector Translation);
aMat           aMatrixTransformation(faVector ScalingOrigin, faVector ScalingOrientationQuaternion, faVector Scaling, 
                                       faVector RotationOrigin, faVector RotationQuaternion, faVector Translation);
aMat           aMatrixAffineTransformation2D(faVector Scaling, faVector RotationOrigin, float Rotation, faVector Translation);
aMat           aMatrixAffineTransformation(faVector Scaling, faVector RotationOrigin, faVector RotationQuaternion, faVector Translation);
aMat           aMatrixReflect(faVector ReflectionPlane);
aMat           aMatrixShadow(faVector ShadowPlane, faVector LightPosition);

aMat           aMatrixLookAtLH(faVector EyePosition, faVector FocusPosition, faVector UpDirection);
aMat           aMatrixLookAtRH(faVector EyePosition, faVector FocusPosition, faVector UpDirection);
aMat           aMatrixLookToLH(faVector EyePosition, faVector EyeDirection, faVector UpDirection);
aMat           aMatrixLookToRH(faVector EyePosition, faVector EyeDirection, faVector UpDirection);
aMat           aMatrixPerspectiveLH(float ViewWidth, float ViewHeight, float NearZ, float FarZ);
aMat           aMatrixPerspectiveRH(float ViewWidth, float ViewHeight, float NearZ, float FarZ);
aMat           aMatrixPerspectiveFovLH(float FovAngleY, float AspectHByW, float NearZ, float FarZ);
aMat           aMatrixPerspectiveFovRH(float FovAngleY, float AspectHByW, float NearZ, float FarZ);
aMat           aMatrixPerspectiveOffCenterLH(float ViewLeft, float ViewRight, float ViewBottom, float ViewTop, float NearZ, float FarZ);
aMat           aMatrixPerspectiveOffCenterRH(float ViewLeft, float ViewRight, float ViewBottom, float ViewTop, float NearZ, float FarZ);
aMat           aMatrixOrthographicLH(float ViewWidth, float ViewHeight, float NearZ, float FarZ);
aMat           aMatrixOrthographicRH(float ViewWidth, float ViewHeight, float NearZ, float FarZ);
aMat           aMatrixOrthographicOffCenterLH(float ViewLeft, float ViewRight, float ViewBottom, float ViewTop, float NearZ, float FarZ);
aMat           aMatrixOrthographicOffCenterRH(float ViewLeft, float ViewRight, float ViewBottom, float ViewTop, float NearZ, float FarZ);


/****************************************************************************
 *
 * Quaternion operations
 *
 ****************************************************************************/

bool            aQuaternionEqual(faVector Q1, faVector Q2);
bool            aQuaternionNotEqual(faVector Q1, faVector Q2);

bool            aQuaternionIsNaN(faVector Q);
bool            aQuaternionIsInfinite(faVector Q);
bool            aQuaternionIsIdentity(faVector Q);

aVector        aQuaternionDot(faVector Q1, faVector Q2);
aVector        aQuaternionMultiply(faVector Q1, faVector Q2);
aVector        aQuaternionLengthSq(faVector Q);
aVector        aQuaternionReciprocalLength(faVector Q);
aVector        aQuaternionLength(faVector Q);
aVector        aQuaternionNormalizeEst(faVector Q);
aVector        aQuaternionNormalize(faVector Q);
aVector        aQuaternionConjugate(faVector Q);
aVector        aQuaternionInverse(faVector Q);
aVector        aQuaternionLn(faVector Q);
aVector        aQuaternionExp(faVector Q);
aVector        aQuaternionSlerp(faVector Q0, faVector Q1, float t);
aVector        aQuaternionSlerpV(faVector Q0, faVector Q1, faVector T);
aVector        aQuaternionSquad(faVector Q0, faVector Q1, faVector Q2, faVector Q3, float t);
aVector        aQuaternionSquadV(faVector Q0, faVector Q1, faVector Q2, faVector Q3, faVector T);
void            aQuaternionSquadSetup(  aVector* pA,   aVector* pB,   aVector* pC,   faVector Q0,   faVector Q1,   faVector Q2,   faVector Q3);
aVector        aQuaternionBaryCentric(faVector Q0, faVector Q1, faVector Q2, float f, float g);
aVector        aQuaternionBaryCentricV(faVector Q0, faVector Q1, faVector Q2, faVector F, faVector G);

aVector        aQuaternionIdentity();
aVector        aQuaternionRotationRollPitchYaw(float Pitch, float Yaw, float Roll);
aVector        aQuaternionRotationRollPitchYawFromVector(faVector Angles);
aVector        aQuaternionRotationNormal(faVector NormalAxis, float Angle);
aVector        aQuaternionRotationAxis(faVector Axis, float Angle);
aVector        aQuaternionRotationMatrix(faMat M);

void            aQuaternionToAxisAngle(  aVector* pAxis,   float* pAngle,   faVector Q);

/****************************************************************************
 *
 * Plane operations
 *
 ****************************************************************************/

bool            aPlaneEqual(faVector P1, faVector P2);
bool            aPlaneNearEqual(faVector P1, faVector P2, faVector Epsilon);
bool            aPlaneNotEqual(faVector P1, faVector P2);

bool            aPlaneIsNaN(faVector P);
bool            aPlaneIsInfinite(faVector P);

aVector        aPlaneDot(faVector P, faVector V);
aVector        aPlaneDotCoord(faVector P, faVector V);
aVector        aPlaneDotNormal(faVector P, faVector V);
aVector        aPlaneNormalizeEst(faVector P);
aVector        aPlaneNormalize(faVector P);
aVector        aPlaneIntersectLine(faVector P, faVector LinePoint1, faVector LinePoint2);
void            aPlaneIntersectPlane(  aVector* pLinePoint1,   aVector* pLinePoint2,   faVector P1,   faVector P2);
aVector        aPlaneTransform(faVector P, faMat M);

aVector        aPlaneFromPointNormal(faVector Point, faVector Normal);
aVector        aPlaneFromPoints(faVector Point1, faVector Point2, faVector Point3);

/****************************************************************************
 *
 * Color operations
 *
 ****************************************************************************/

bool            aColorEqual(faVector C1, faVector C2);
bool            aColorNotEqual(faVector C1, faVector C2);
bool            aColorGreater(faVector C1, faVector C2);
bool            aColorGreaterOrEqual(faVector C1, faVector C2);
bool            aColorLess(faVector C1, faVector C2);
bool            aColorLessOrEqual(faVector C1, faVector C2);

bool            aColorIsNaN(faVector C);
bool            aColorIsInfinite(faVector C);

aVector        aColorNegative(faVector C);
aVector        aColorModulate(faVector C1, faVector C2);
aVector        aColorAdjustSaturation(faVector C, float Saturation);
aVector        aColorAdjustContrast(faVector C, float Contrast);

aVector        aColorRGBToHSL( faVector rgb );
aVector        aColorHSLToRGB( faVector hsl );

aVector        aColorRGBToHSV( faVector rgb );
aVector        aColorHSVToRGB( faVector hsv );

aVector        aColorRGBToYUV( faVector rgb );
aVector        aColorYUVToRGB( faVector yuv );

aVector        aColorRGBToYUV_HD( faVector rgb );
aVector        aColorYUVToRGB_HD( faVector yuv );

aVector        aColorRGBToXYZ( faVector rgb );
aVector        aColorXYZToRGB( faVector xyz );

aVector        aColorXYZToSRGB( faVector xyz );
aVector        aColorSRGBToXYZ( faVector srgb );

/****************************************************************************
 *
 * Miscellaneous operations
 *
 ****************************************************************************/

bool            aVerifyCPUSupport();

aVector         aFresnelTerm(faVector CosIncidentAngle, faVector RefractionIndex);

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

