//D3DGraphClass.h
//D3D pipeline preparation process

#pragma once

#ifndef _D3DGRAPHCLASS_H_
#define _D3DGRAPHCLASS_H_

//Include d3dut_globle for globle files and functions
#include "d3dut_globle.h"
using namespace utg;

class D3D11GraphClass
{
public:
	D3D11GraphClass();
	~D3D11GraphClass();

	HRESULT Initialize(HWND hWnd,bool vsyn_enable,bool fullScreen);
	void frameBegin(float bgcolor[4]);
	void frameEnd(void);
	ID3D11Device* GetDevice(void);
	ID3D11DeviceContext* GetDeviceContext(void);
	void CleanupDevice();

private:
	HRESULT GetAdapterInfo(int screenHeight,int screenWidth,unsigned int& numerator,unsigned int& denominator,int& videoCardMemory,string& videoCardDesc );
	vector <IDXGIAdapter*> EnumerateAdapters(void);
	HRESULT GetFeatureLevel(D3D_FEATURE_LEVEL& featureLevels);

private:
	D3D_DRIVER_TYPE           m_driverType;
    D3D_FEATURE_LEVEL         m_featureLevel;
    ID3D11Device*             m_pd3dDevice;
    ID3D11DeviceContext*      m_pImmediateContext;
    IDXGISwapChain*           m_pSwapChain;
    ID3D11RenderTargetView*   m_pRenderTargetView;
	ID3D11DepthStencilView*   m_pDepthStencilView;
	ID3D11Texture2D*          m_pDepthBuffer;
	ID3D11DepthStencilState*  m_pdepthStencilState;
	ID3D11RasterizerState*    m_pRasterState;
	bool                      m_vsyn;
};

#endif