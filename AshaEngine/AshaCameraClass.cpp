//AshaCameraClass.cpp

#include "AshaCameraClass.h"


AshaCameraClass::AshaCameraClass(void)
{
	// Initialize the world matrix
	m_xWorld =DirectX::XMMatrixIdentity();
	m_xRotation=DirectX::XMMatrixIdentity();
	m_xTranslation=DirectX::XMMatrixIdentity();
	m_xScale=DirectX::XMMatrixIdentity();
	// Initialize the view matrix
	m_xView= DirectX::XMMatrixIdentity();
	// Initialize the projection matrix
	m_xProjection=DirectX::XMMatrixIdentity();
}


AshaCameraClass::~AshaCameraClass(void)
{
}


void AshaCameraClass::Initailize(HWND hWnd)
{
	// Initialize the world matrix
	SetRotation(0.0f,1.0f,0.0f,0.0f,0.0f);
	SetTranslation(0.0f,0.0f,0.0f);
	SetScaling(1.0f,1.0f,1.0f);
	SetWorld();

	// Initialize the view matrix
	SetEyePos(0.0f, 4.0f, -10.0f, 0.0f);
	SetFocusPos(0.0f, 1.0f, 0.0f, 0.0f);
	SetUpAxis(0.0f, 1.0f, 0.0f, 0.0f  );
	SetView();

	// Initialize the projection matrix
	//Get client dimension
	RECT rc;
	GetClientRect(hWnd,&rc);
	int screenHeight=rc.right-rc.left;
	int screenWidth=rc.bottom-rc.top;
	SetLens(DirectX::XM_PIDIV4, screenWidth / (FLOAT)screenHeight, 0.01f, 100.0f);

}


void AshaCameraClass::SetRotation(float x,float y,float z,float w,float angle)
{
	m_xRotation=DirectX::XMMatrixRotationAxis(DirectX::XMVectorSet(x,y,z,w),angle);
}


void AshaCameraClass::SetTranslation(float x,float y,float z)
{
	m_xTranslation= DirectX::XMMatrixTranslation(x,y,z);
}


void AshaCameraClass::SetScaling(float x,float y,float z)
{
	m_xScale=DirectX::XMMatrixScaling(x,y,z);
}


void AshaCameraClass::SetWorld(void)
{
	m_xWorld= m_xRotation*m_xTranslation*m_xScale;
}


DirectX::XMMATRIX AshaCameraClass::GetworldMatrix(void) const
{
	return m_xWorld;
}


void AshaCameraClass::SetEyePos(float x,float y,float z,float w)
{
	m_xEyePos=DirectX::XMVectorSet( x, y, z, w );
}


DirectX::XMVECTOR AshaCameraClass::GetEyePos(void) const
{
	return m_xEyePos;
}


void AshaCameraClass::SetFocusPos(float x,float y,float z,float w)
{
	m_xFocusPos=DirectX::XMVectorSet( x, y, z, w );
}


DirectX::XMVECTOR AshaCameraClass::GetFocusPos(void) const
{
	return m_xFocusPos;
}


void AshaCameraClass::SetUpAxis(float x,float y,float z,float w)
{
	m_xUpAix=DirectX::XMVectorSet( x, y, z, w );
}


DirectX::XMVECTOR AshaCameraClass::GetUpAxis(void) const
{
	return m_xUpAix;
}


void AshaCameraClass::SetView(void)
{
	m_xView= DirectX::XMMatrixLookAtLH( m_xEyePos, m_xFocusPos, m_xUpAix );
}


DirectX::XMMATRIX AshaCameraClass::GetViewMatrix(void) const
{
	return m_xView;
}


DirectX::XMMATRIX AshaCameraClass::GetProjectionMatrix(void) const
{
	return m_xProjection;
}


float AshaCameraClass::GetFovAngleY(void) const
{
	return m_fFovAngleY;
}


float AshaCameraClass::GetFovAngleX(void) const
{
	return 2.0f*atan((0.5f*GetNearWndWidth())/m_fNearZ);
}


float AshaCameraClass::GetAspect(void) const
{
	return m_fAspect;
}


float AshaCameraClass::GetNearZ(void) const
{
	return m_fNearZ;
}


float AshaCameraClass::GetFarZ(void) const
{
	return m_fFarZ;
}


float AshaCameraClass::GetFarWndHeight(void) const
{
	return m_fFarWndHeight;
}


float AshaCameraClass::GetFarWndWidth(void) const
{
	return m_fFarWndHeight*m_fAspect;
}


float AshaCameraClass::GetNearWndHeight(void) const
{
	return m_fNearWndHeight;
}


float AshaCameraClass::GetNearWndWidth(void) const
{
	return m_fNearWndHeight*m_fAspect;
}


void AshaCameraClass::SetLens(float fovY, float aspect, float nz, float fz)
{
	//Set  frustum parameter
	m_fFovAngleY=fovY;
	m_fAspect=aspect;
	m_fNearZ=nz;
	m_fFarZ=fz;

	m_fNearWndHeight=2.0f * m_fNearZ * tanf( 0.5f*m_fFovAngleY);
	m_fFarWndHeight=2.0f*m_fNearZ*tanf(0.5f*m_fFovAngleY);

	//Set projection matrix
	m_xProjection=DirectX::XMMatrixPerspectiveFovLH(m_fFovAngleY,m_fAspect,m_fNearZ,m_fFarZ);
}