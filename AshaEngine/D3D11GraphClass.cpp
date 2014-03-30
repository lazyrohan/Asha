//D3D11GraphClass.cpp

#include "D3D11GraphClass.h"

D3D11GraphClass::D3D11GraphClass():
	m_pd3dDevice(NULL),
	m_pImmediateContext(NULL),
	m_pSwapChain(NULL),
	m_pRenderTargetView(NULL),
	m_pDepthStencilView(NULL),
	m_pDepthBuffer(NULL),
	m_pdepthStencilState(NULL),
	m_pRasterState(NULL),
	m_vsyn(true)
{
	m_driverType = D3D_DRIVER_TYPE_NULL;
    m_featureLevel = D3D_FEATURE_LEVEL_10_0;
}

D3D11GraphClass::~D3D11GraphClass()
{

}

HRESULT D3D11GraphClass::Initialize(HWND hWnd,bool vsyn_enable,bool fullScreen)
{
	HRESULT hr=S_OK;
	m_vsyn=vsyn_enable;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//Get top support hardware feature level
	hr=GetFeatureLevel(m_featureLevel);
	//MessageBox(NULL,("GetFeatureLevel:"+var2Str(m_featureLevel)).c_str(),"D3D11GraphClass::Initialize",MB_OK);
	if(FAILED(hr))
	{
		MessageBox(NULL,"GetFeatureLevel:Can`t find validate video cards!\n","Error:D3D11GraphClass::Initialize",MB_OK);
		return S_FALSE;
	}

	//Get client dimension
	RECT rc;
	GetClientRect(hWnd,&rc);
	int screenHeight=rc.right-rc.left;
	int screenWidth=rc.bottom-rc.top;

	//Check video card info.
    unsigned int numerator=60,denominator=1;
	int videoCardMemory=0;
	string videoCardDesc="\0";

	hr=GetAdapterInfo(screenHeight,screenWidth,numerator,denominator, videoCardMemory,videoCardDesc);	
	if(FAILED(hr))
	{
		MessageBox(NULL,("GetAdapterInfo->hr:"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::Initialize",MB_OK);
		//return S_FALSE;
	}
	string videoCardInfo="Video card: "+videoCardDesc+"\n"+"Video card memory size: "+var2Str(videoCardMemory)+"MB\n";
	//MessageBox(NULL,videoCardInfo.c_str(),"Info:Video Card",MB_OK);

	//Setup swap chain description structure
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd,sizeof(sd));
	sd.BufferCount=1;//Back buffer used
	sd.BufferDesc.Width=screenWidth;
	sd.BufferDesc.Height=screenHeight;
	sd.BufferDesc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;

	//Set refresh rate
	if(vsyn_enable)
	{
		sd.BufferDesc.RefreshRate.Numerator=numerator;
		sd.BufferDesc.RefreshRate.Denominator=denominator;
	}
	else
	{
		sd.BufferDesc.RefreshRate.Numerator=60;
	    sd.BufferDesc.RefreshRate.Denominator=1;
	}

	sd.BufferUsage=DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags=DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//Allow switch between full screen and widowed
	sd.OutputWindow=hWnd;
	sd.SampleDesc.Count=1;//MSAA off
	sd.SampleDesc.Quality=0;

	// Discard the back buffer contents after presenting.
	sd.SwapEffect=DXGI_SWAP_EFFECT_DISCARD;

	//Windowed options
	if(fullScreen)
		sd.Windowed=false;//full screen
	else
	    sd.Windowed=true;//windowed

	
	D3D_DRIVER_TYPE driverTypes[]=
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT numDriverTypes=ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[]=
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT numFeatureLevels=ARRAYSIZE(featureLevels);

	//Creation with adapter support features
	for(UINT i=0;i<numDriverTypes;i++)
	{
		m_driverType=driverTypes[i];
	
		hr= D3D11CreateDeviceAndSwapChain
			(
			NULL,//Adapter to use
			m_driverType,
			NULL,//software module
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_pSwapChain,
			&m_pd3dDevice,
			&m_featureLevel,
			&m_pImmediateContext
			);

		if(SUCCEEDED(hr))
			break;
	}

	if(FAILED(hr))
		return hr;

	//Create Render target view
	ID3D11Texture2D* pBackBuffer=NULL;
	if(FAILED(m_pSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(LPVOID*)&pBackBuffer)))
		return S_FALSE;
	hr=m_pd3dDevice->CreateRenderTargetView(pBackBuffer,NULL,&m_pRenderTargetView);
	if(pBackBuffer)
	{
	  pBackBuffer->Release();
	  pBackBuffer=NULL;
	}
	if(FAILED(hr))
	{
		MessageBox(NULL,("m_pd3dDevice->CreateRenderTargetView failed:hr->"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::Initialize",MB_OK);
		return hr;
	}

	//Create depth buffer 
	D3D11_TEXTURE2D_DESC depthBuffDesc;
	depthBuffDesc.Width=screenWidth;  //Depth stencil view dimension equal to back buffer dimension
	depthBuffDesc.Height=screenHeight;
	depthBuffDesc.MipLevels=1;
	depthBuffDesc.ArraySize=1;
	depthBuffDesc.Format=DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBuffDesc.SampleDesc.Count=1;//Multi sampling
	depthBuffDesc.SampleDesc.Quality=0;
	depthBuffDesc.Usage=D3D11_USAGE_DEFAULT;
	depthBuffDesc.BindFlags=D3D11_BIND_DEPTH_STENCIL;
	depthBuffDesc.CPUAccessFlags=0;//No CPU access to GPU memory
	depthBuffDesc.MiscFlags=0;
	
	
	hr=m_pd3dDevice->CreateTexture2D(&depthBuffDesc,0,&m_pDepthBuffer);
	if(FAILED(hr))
	{
		MessageBox(NULL,("m_pd3dDevice->CreateTexture2D failed:hr->"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::Initialize",MB_OK);
		return hr;
	}

	//Create stencil state
	// Initialize the description of the stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	hr = m_pd3dDevice->CreateDepthStencilState(&depthStencilDesc, &m_pdepthStencilState);
	if(FAILED(hr))
	{
		MessageBox(NULL,("m_pd3dDevice->CreateDepthStencilState failed:hr->"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::Initialize",MB_OK);
		return hr;
	}
	// Set the depth stencil state.
	m_pImmediateContext->OMSetDepthStencilState(m_pdepthStencilState,1);

	//Create depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	hr=m_pd3dDevice->CreateDepthStencilView(m_pDepthBuffer,&depthStencilViewDesc,&m_pDepthStencilView);
	if(FAILED(hr))
	{
		MessageBox(NULL,("m_pd3dDevice->CreateDepthStencilView failed:hr->"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::Initialize",MB_OK);
		return hr;
	}

	//Bind view to render target
	m_pImmediateContext->OMSetRenderTargets(1,&m_pRenderTargetView,m_pDepthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc,sizeof(rasterDesc));

	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	hr = m_pd3dDevice->CreateRasterizerState(&rasterDesc, &m_pRasterState);
	if(FAILED(hr))
	{
		MessageBox(NULL,("m_pd3dDevice->CreateRasterizerState failed:hr->"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::Initialize",MB_OK);
		return hr;
	}

	// Now set the rasterizer state.
	m_pImmediateContext->RSSetState(m_pRasterState);

	//setup viewport
	D3D11_VIEWPORT vp;
	vp.TopLeftX=0;
	vp.TopLeftY=0;
	vp.Height=(float)(screenHeight);
	vp.Width=(float)screenWidth;
	vp.MaxDepth=1.0f;
	vp.MinDepth=0.0f;

	m_pImmediateContext->RSSetViewports(1,&vp);

	//// Setup the projection matrix.
	
	
	return S_OK;

}

void D3D11GraphClass::frameBegin(float bgcolor[4])
{
	//Clear back buffer
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView,bgcolor);
	//Clear depth stencil view
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView,D3D11_CLEAR_DEPTH,1.0f,0);

	return;
}

void D3D11GraphClass::frameEnd()
{
	if(m_vsyn)
		m_pSwapChain->Present(1,0);
	else
	    m_pSwapChain->Present(0,0);

	return;
}
ID3D11Device* D3D11GraphClass::GetDevice()
{
	return m_pd3dDevice;
}

ID3D11DeviceContext* D3D11GraphClass::GetDeviceContext()
{
	return m_pImmediateContext;
}

void D3D11GraphClass::CleanupDevice()
{
	if( m_pSwapChain ) 
	{
		//If full screen set to widowed before exit.
		m_pSwapChain->SetFullscreenState(false,NULL);
	}

	if(m_pRasterState)
	{
		m_pRasterState->Release();
		m_pRasterState=NULL;
	}

	if(m_pdepthStencilState)
	{
		m_pdepthStencilState->Release();
		m_pdepthStencilState=NULL;
	}

	if(m_pDepthBuffer)
	{
		m_pDepthBuffer->Release();
		m_pDepthBuffer=NULL;
	}

	if(m_pDepthStencilView)
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilView=NULL;
	}

    if( m_pRenderTargetView ) 
	{
		m_pRenderTargetView->Release();
		m_pRenderTargetView=NULL;
	}

    if( m_pSwapChain ) 
	{
		m_pSwapChain->Release();
		m_pSwapChain=NULL;
	}

    if( m_pImmediateContext ) 
	{
		m_pImmediateContext->Release();
		m_pImmediateContext->Flush();
		m_pImmediateContext=NULL;
	}

    if( m_pd3dDevice ) 
	{
		m_pd3dDevice->Release();
		m_pd3dDevice=NULL;
	}

	return;
}

HRESULT D3D11GraphClass::GetAdapterInfo(int screenHeight,int screenWidth,unsigned int& numerator,unsigned int& denominator,int& videoCardMemory,string& videoCardDesc  )
{
	HRESULT hr=S_OK;	
	//Get adapter info ----------------------------------------------------------------------
    // Create a DirectX graphics interface factory
	IDXGIFactory* pfactory=NULL;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pfactory);
	if(FAILED(hr))
	{
		MessageBox(NULL,("CreateDXGIFactory:"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::GetAdapterInfo",MB_OK);
		return hr;
	}

	// Step2: Use the factory to create an adapter for the primary graphics interface (video card).
	IDXGIAdapter* padapter=NULL;
	hr = pfactory->EnumAdapters(0, &padapter);
	if(FAILED(hr))
	{
		MessageBox(NULL,("pfactory->EnumAdapters:"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::GetAdapterInfo",MB_OK);
		return hr;
	}

	//step3: Enumerate the primary adapter output (monitor).
	IDXGIOutput* padapterOutput=NULL;
	hr = padapter->EnumOutputs(0, &padapterOutput);
	if(FAILED(hr))
	{
		MessageBox(NULL,("padapter->EnumOutputs:"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::GetAdapterInfo",MB_OK);
		return hr;
	}

	//Get display modles
	UINT numModes=0;//Total display modes
	DXGI_MODE_DESC* pdisplayModes;
	DXGI_FORMAT format=DXGI_FORMAT_R8G8B8A8_UNORM;

	//Get number of elements
	hr=padapterOutput->GetDisplayModeList(format,DXGI_ENUM_MODES_INTERLACED,&numModes,NULL);
	if(FAILED(hr))
	{
		MessageBox(NULL,("padapterOutput->GetDisplayModeList:"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::GetAdapterInfo",MB_OK);
		return hr;
	}
	pdisplayModes=new DXGI_MODE_DESC [numModes];
	if(!pdisplayModes)
	{
		MessageBox(NULL,("pdisplayModes=new DXGI_MODE_DESC:"+var2Str(pdisplayModes)).c_str(),"Error:D3D11GraphClass::GetAdapterInfo",MB_OK);
		return S_FALSE;
	}
	//Get the list
	hr=padapterOutput->GetDisplayModeList(format,0,&numModes,pdisplayModes);
	if(FAILED(hr))
	{
		MessageBox(NULL,("padapterOutput->GetDisplayModeList:"+var2Str(hr)).c_str(),"Erro:D3D11GraphClass::GetAdapterInfo",MB_OK);
		return hr;
	}

	//Get refresh rate which match asigned screen size
	for(unsigned int i=0; i<numModes; i++)
	{
		if(pdisplayModes[i].Width == (unsigned int)screenWidth)
		{
			if(pdisplayModes[i].Height == (unsigned int)screenHeight)
			{
				numerator = pdisplayModes[i].RefreshRate.Numerator;
				denominator = pdisplayModes[i].RefreshRate.Denominator;
			}
		}
	}
	//MessageBox(NULL,("numerator:"+var2Str(numerator)+"\n"+"denominator:"+var2Str(denominator)).c_str(),"D3D11GraphClass::GetAdapterInfo",MB_OK);

	// Get the adapter (video card) info.-------------------------------------------------------
	DXGI_ADAPTER_DESC padapterDesc;
	hr = padapter->GetDesc(&padapterDesc);
	if(FAILED(hr))
	{
		MessageBox(NULL,("padapter->GetDesc:"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::GetAdapterInfo",MB_OK);
		return hr;
	}

	// Store the dedicated(×¨Êô) video card memory in megabytes(MB).
	videoCardMemory = (int)(padapterDesc.DedicatedVideoMemory / (1024*1024));

	//Get video card description.
	unsigned int strLength=0;
	char cvideoCardDesc[200]="\0";
	int error=0;
	error = wcstombs_s(&strLength,cvideoCardDesc, 128, padapterDesc.Description, _TRUNCATE);
	if(error != 0)
	{
		MessageBox(NULL,("wcstombs_s:"+var2Str(error)).c_str(),"Error:D3D11GraphClass::GetAdapterInfo",MB_OK);
		return S_FALSE;
	}
	videoCardDesc=cvideoCardDesc;

	//Release dxgi interface
	// Release the display mode list.
	delete [] pdisplayModes;
	pdisplayModes = NULL;
	// Release the adapter output.
	padapterOutput->Release();
	padapterOutput = NULL;
	// Release the adapter.
	padapter->Release();
	padapter = NULL;
	// Release the factory.
	pfactory->Release();
	pfactory = NULL;

	return S_OK;
}

HRESULT D3D11GraphClass::GetFeatureLevel(D3D_FEATURE_LEVEL& featureLevels)
{
	HRESULT hr=S_OK;
	hr=D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,0,NULL,0,D3D11_SDK_VERSION,NULL,&featureLevels,NULL);
	if(FAILED(hr))
	{
		MessageBox(NULL,("D3D11CreateDevice failed:hr->"+var2Str(hr)).c_str(),"Error:D3D11GraphClass::GetFeatureLevel",MB_OK);
		return hr;
	}

	return S_OK;
}

vector <IDXGIAdapter*> D3D11GraphClass::EnumerateAdapters()
{
  IDXGIAdapter* pAdapter=NULL;
  vector <IDXGIAdapter*> vAdapters;
  IDXGIFactory* pFactory=NULL;

  //Create DXGIFactory object
  if(FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory),(void**) &pFactory)))
	  return vAdapters;

  //Enumerate adapters
  for (int i=0;pFactory->EnumAdapters(i,&pAdapter)!=DXGI_ERROR_NOT_FOUND;++i)
  {
	  vAdapters.push_back(pAdapter);
  }

  if(pFactory)
  {
	  pFactory->Release();
	  pFactory=NULL;
  }

  return vAdapters;
}