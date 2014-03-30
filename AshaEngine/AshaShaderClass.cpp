//ShaderClass.cpp

#include "AshaShaderClass.h"

AshaShaderClass::AshaShaderClass():
	m_pVertexShader(NULL),
	m_pVertexLayout(NULL),
	m_pPixelShader(NULL),
	m_pCamLightBuff(NULL)
	//m_pCamera(NULL)
{

}

AshaShaderClass::~AshaShaderClass()
{

}


HRESULT AshaShaderClass::Initailize(ID3D11Device* pDevice,HWND hWnd)
{
	HRESULT hr=S_OK;

	//Initialize camera
	m_pCamera.Initailize(hWnd);

	//Create camera light constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamLightBUff);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr =  pDevice->CreateBuffer( &bd, NULL, &m_pCamLightBuff);
	if( FAILED( hr ) )
		return hr;



	//Load and compile shader file

	//Compile vertex shader----------------------------------------
	ID3DBlob* pVSBlob=NULL;
	hr = CompileShaderFromFile( L"shade.fx", "VS", "vs_4_0", &pVSBlob );
	if( FAILED(hr) )
	{
		MessageBox( NULL,
			"The VS FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error:VS Compile", MB_OK );
		return hr;
	}

	// Create the vertex shader

	hr = pDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVertexShader );
	if( FAILED( hr ))
	{	
		pVSBlob->Release();
		pVSBlob=NULL;
		return hr;
	}


	//Create input layout----------------------------------------
	//VertexA input layout
	D3D11_INPUT_ELEMENT_DESC VertexDesc[]=
	{
		{"POSITION",                         //Semantic name
		0,                                  //SemanticIndex
		DXGI_FORMAT_R32G32B32_FLOAT,        //DXGI format
		0,                                  //Input slot
		0,                                  //AlignedByteOffset
		D3D11_INPUT_PER_VERTEX_DATA,        //Input slot class
		0},                                 //InstanceDataStepRate  
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},

	};

	hr=pDevice->CreateInputLayout(VertexDesc,ARRAYSIZE(VertexDesc),pVSBlob->GetBufferPointer(),pVSBlob->GetBufferSize(),&m_pVertexLayout);
	//Release vs blob
	if(pVSBlob)
	{
		pVSBlob->Release();
		pVSBlob=NULL;
	}

	if(FAILED(hr))
		return hr;

	//Compile pixel shader----------------------------------------------------
	ID3DBlob* pPSBlob=NULL;
	hr = CompileShaderFromFile(L"shade.fx", "PS", "ps_4_0", &pPSBlob );
	if(FAILED(hr))
	{
		MessageBox( NULL,
			"The PS FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error:PS Compile",MB_OK );
		return hr;
	}

	//Create Pixel shader	
	hr=pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_pPixelShader );
	//Release psBlob
	if(pPSBlob)
	{
		pPSBlob->Release();
		pPSBlob=NULL;
	}

	if(FAILED(hr))
		return hr;

	return S_OK;
}


void AshaShaderClass::UpdateCamLightBUff(ID3D11DeviceContext* pDeviceContext)
{
	AshaShaderClass::CamLightBUff camlitBuff;
	ZeroMemory(&camlitBuff,sizeof(AshaShaderClass::CamLightBUff));
	camlitBuff.World=DirectX::XMMatrixTranspose(m_pCamera.GetworldMatrix());
	camlitBuff.View=DirectX::XMMatrixTranspose(m_pCamera.GetViewMatrix());
	camlitBuff.Projection=DirectX::XMMatrixTranspose(m_pCamera.GetProjectionMatrix());
	camlitBuff.LightDir=DirectX::XMFLOAT4( -0.577f, 0.577f, -0.577f, 1.0f );
	camlitBuff.LightColor=DirectX::XMFLOAT4( 0.5f, 0.5f, 0.5f, 1.0f );
	pDeviceContext->UpdateSubresource( m_pCamLightBuff, 0, NULL, &camlitBuff, 0, 0 );
}


void AshaShaderClass::renderShader(ID3D11DeviceContext* pDeviceContext)
{
	//Setup input layout
	pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//Setup shader to render pipeline
	pDeviceContext->VSSetShader(m_pVertexShader,NULL,0);
	pDeviceContext->VSSetConstantBuffers(0,1,&m_pCamLightBuff);
	pDeviceContext->PSSetShader(m_pPixelShader,NULL,0);
	pDeviceContext->PSSetConstantBuffers(0,1,&m_pCamLightBuff);

	return;
}


void AshaShaderClass::ReleaseShader()
{
	if(m_pCamLightBuff)
	{
		m_pCamLightBuff->Release();
		m_pCamLightBuff=NULL;
	}
	if( m_pVertexLayout )
	{
		m_pVertexLayout->Release();
		m_pVertexLayout=NULL;
	}

	if( m_pPixelShader )
	{
		m_pPixelShader->Release();
		m_pPixelShader=NULL;
	}

	if( m_pVertexShader )
	{
		m_pVertexShader->Release();
		m_pVertexShader=NULL;
	}
}


HRESULT AshaShaderClass::CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName,NULL,NULL,szEntryPoint,szShaderModel,dwShaderFlags, 0,ppBlobOut, &pErrorBlob );
    if( FAILED(hr))
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}