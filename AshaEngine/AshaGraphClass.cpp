//AshaGraphClass.cpp

#include "AshaGraphClass.h"

AshaGraphClass::AshaGraphClass():
	m_pd3dGraph(NULL),
	m_pModel(NULL),
	m_pShader(NULL)
{
  
}

AshaGraphClass::~AshaGraphClass()
{

}

HRESULT AshaGraphClass::Initialize(HWND hWnd)
{
	HRESULT hr=S_OK;

	//Initialize D3D device----------------------------------------------------------------------------
	m_pd3dGraph=new D3D11GraphClass;
	//MessageBox(NULL,("m_pd3dGraph:"+var2Str(m_pd3dGraph)+"\n").c_str(),"AshaGraphClass::Initialize",MB_OK);
	if(!m_pd3dGraph)
	{
		return S_FALSE;
	}
	m_pd3dGraph->Initialize(hWnd,true,false);
	//MessageBox(NULL,("m_pd3dGraph->g_pd3dDevice: "+var2Str(m_pd3dGraph->GetDevice())).c_str(),"AshaGraphClass::Initialize",MB_OK);

	//Initialize shader object
	//Load shader
	m_pShader=new AshaShaderClass;
	if(!m_pShader)
	{
		return S_FALSE;
	}
	hr=m_pShader->Initailize(m_pd3dGraph->GetDevice(),hWnd);
	if(FAILED(hr))
	{
		m_pShader->ReleaseShader();
		delete m_pShader;
		m_pShader=NULL;
		return hr;
	}


	//Initialize model object
	//Load model
	m_pModel=new AshaModelClass;
	if(!m_pModel)
	{
		return S_FALSE;
	}
	hr=m_pModel->Initialize("test.ahm");
	if(FAILED(hr))
	{
		m_pModel->ReleaseModel();
		delete m_pModel;
		m_pModel=NULL;
		return hr;
	}
	hr=m_pModel->LoadModel(m_pd3dGraph->GetDevice());
	if(FAILED(hr))
	{
		m_pModel->ReleaseModel();
		delete m_pModel;
		m_pModel=NULL;
		return hr;
	}
	//Bind model buffer and Set primate topology
	m_pModel->SetModel(m_pd3dGraph->GetDeviceContext());
	m_pModel->SetPrimTopology(m_pd3dGraph->GetDeviceContext(),D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return S_OK;
}


void AshaGraphClass::RenderFrame()
{	
	m_pShader->UpdateCamLightBUff(m_pd3dGraph->GetDeviceContext());
	//Bind shader buffer
	m_pShader->renderShader(m_pd3dGraph->GetDeviceContext());
	//Draw objects
	m_pd3dGraph->GetDeviceContext()->DrawIndexed(m_pModel->m_elemNum[0],0,0);

	return;
}

void AshaGraphClass::Render()
{
	float bgcolor[4]={0.3f,0.2f,0.3f,1.0f};
	m_pd3dGraph->frameBegin(bgcolor);
	RenderFrame();
	m_pd3dGraph->frameEnd();
	
	return;
}

void AshaGraphClass::Release()
{
	if(m_pShader)
	{
		m_pShader->ReleaseShader();
		delete m_pShader;
		m_pShader=NULL;
	}

	if(m_pModel)
	{
		m_pModel->ReleaseModel();
		delete m_pModel;
		m_pModel=NULL;
	}

	if(m_pd3dGraph)
	{
		m_pd3dGraph->CleanupDevice();
		delete m_pd3dGraph;
		m_pd3dGraph=NULL;
	}

	return;
}
