//AshaShaderClass.h
//Management shader

#ifndef _SHADERCLASS_H_
#define _SHADERCLASS_H_

//Include header files
#include <D3D11.h>
#include <D3Dcompiler.h>
#pragma comment(lib,"D3DCompiler.lib")

//Include Camera,light header files
#include "AshaCameraClass.h"


//Shader class
class AshaShaderClass
{
	struct CamLightBUff
	{
		//Camera matrix
		DirectX::XMMATRIX World;
		DirectX::XMMATRIX View;
		DirectX::XMMATRIX Projection;
		//Light specs
		DirectX::XMFLOAT4 LightDir;
		DirectX::XMFLOAT4 LightColor;
	};

public:
	AshaShaderClass();
	~AshaShaderClass();
	HRESULT Initailize(ID3D11Device* pDevice,HWND hWnd);
	void UpdateCamLightBUff(ID3D11DeviceContext* pDeviceContext);
	void renderShader(ID3D11DeviceContext* pDeviceContext);
	void ReleaseShader(void);
private:
	HRESULT CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

private:	
	ID3D11VertexShader*     m_pVertexShader;
	ID3D11InputLayout*      m_pVertexLayout;
	ID3D11PixelShader*      m_pPixelShader;
	ID3D11Buffer*           m_pCamLightBuff;
	AshaCameraClass         m_pCamera;

};

#endif