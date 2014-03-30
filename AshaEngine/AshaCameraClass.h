//AshaCameraClass.h
//Define camera class

#ifndef _ASHACAMERA_H_
#define _ASHACAMERA_H_

//Including header files
#include <d3d11.h>
//DirectX math library
#include <directxmath.h>
//using namespace DirectX;


//AshaCamera class
class AshaCameraClass
{
public:
	AshaCameraClass(void);
	virtual ~AshaCameraClass(void);

public:
	void                Initailize(HWND hWnd);
	//World transform functions
	void                   SetRotation(float x,float y,float z,float w,float angle);
	void                   SetTranslation(float x,float y,float z);
	void                   SetScaling(float x,float y,float z);
	void                   SetWorld(void);
	DirectX::XMMATRIX      GetworldMatrix(void) const;

	//View function 
	void                   SetEyePos(float x,float y,float z,float w);
	DirectX::XMVECTOR      GetEyePos(void) const;
	void                   SetFocusPos(float x,float y,float z,float w);
	DirectX::XMVECTOR      GetFocusPos(void) const;
	void                   SetUpAxis(float x,float y,float z,float w);
	DirectX::XMVECTOR      GetUpAxis(void) const;
	void                   SetView(void);
	DirectX::XMMATRIX      GetViewMatrix(void) const;

	//Projection frustum function
	DirectX::XMMATRIX      GetProjectionMatrix(void) const;
	float                  GetFovAngleY(void) const;
	float                  GetFovAngleX(void) const;
	float                  GetAspect(void) const;
	float                  GetNearZ(void) const;
	float                  GetFarZ(void) const;
	// Get near and far plane dimensions in view space coordinates.
	float                  GetNearWndHeight(void) const;
	float                  GetNearWndWidth(void) const;
	float                  GetFarWndHeight(void) const;
	float                  GetFarWndWidth(void) const;
	// Set frustum.
	void SetLens(float fovY, float aspect, float nz, float fz);
private:
	//World matrix
	DirectX::XMMATRIX      m_xWorld;
	//Rotation matrix
	DirectX::XMMATRIX      m_xRotation;
	//Translation matrix
	DirectX::XMMATRIX      m_xTranslation;
	//Scaling matrix
	DirectX::XMMATRIX      m_xScale;

	//View matrix
	DirectX::XMMATRIX      m_xView;
	//Eye position
	DirectX::XMVECTOR      m_xEyePos;
	//Focus position
	DirectX::XMVECTOR      m_xFocusPos;
	//Up axis
	DirectX::XMVECTOR      m_xUpAix;

	//Projection matrix
	DirectX::XMMATRIX      m_xProjection;
	float                  m_fFovAngleY;
	float                  m_fAspect;
	float                  m_fNearZ;
	float                  m_fFarZ;
	float                  m_fNearWndHeight;
	float                  m_fFarWndHeight;

};

#endif
