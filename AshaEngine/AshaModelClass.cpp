//AshaModelClass.cpp

#include "AshaModelClass.h"

AshaModelClass::AshaModelClass():
	m_pahmModel(NULL),
	m_pVertexBuffer(NULL),
	m_pIndexBuffer(NULL)
{
	
}

AshaModelClass::~AshaModelClass()
{

}

 HRESULT AshaModelClass::Initialize(string fileName)
{

	HRESULT hr=S_OK;
	//m_fileName=fileName;
	//Initialize ahm model class
	m_pahmModel=new ahmModelClass;
    hr=m_pahmModel->Initialize(fileName);
	if(FAILED(hr))
		return hr;

	//Get element vertex faceIndex shape number
	//Vertex number
	m_elemNum[0]=m_pahmModel->g_elemIndex[0][0];
	//FaceIndex number
	m_elemNum[1]=m_pahmModel->g_elemIndex[1][0];
	//shape number
	m_elemNum[2]=m_pahmModel->g_elemIndex[2][0];

	return S_OK;
	
}


HRESULT AshaModelClass::LoadModel(ID3D11Device* pDevice)
{
	HRESULT hr=S_OK;

	//Load ahm model data
	vector<modelA::VertexA> vertices(m_pahmModel->g_elemIndex[0][0]);
	vector<modelA::FaceIndexA> faceIndex(m_pahmModel->g_elemIndex[1][0]);
	m_pahmModel->loadModel(vertices,faceIndex);

	//Create vertex buffer
	//Fill vertex buffer description structure
	D3D11_BUFFER_DESC vbd;
	ZeroMemory( &vbd, sizeof(vbd) );
    vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof( modelA::VertexA )*m_pahmModel->g_elemIndex[0][0];
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags=0;

    D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof(InitData) );
	InitData.pSysMem = &vertices;
	InitData.SysMemPitch=0;
	InitData.SysMemSlicePitch=0;
	//MessageBox(NULL,("pDevice:"+var2Str(pDevice)).c_str(),"AshaModelClass::LoadModel",MB_OK);

    hr = pDevice->CreateBuffer( &vbd, &InitData, &m_pVertexBuffer);
    if(FAILED(hr))
	{
		MessageBox(NULL,"Can`t create vertex buffer.","Error",MB_OK);
		return hr;
	}

	
	//Create index buffer
	D3D11_BUFFER_DESC indxbd;
	ZeroMemory(&indxbd,sizeof(indxbd));
	indxbd.Usage=D3D11_USAGE_DEFAULT;
	indxbd.ByteWidth=sizeof(modelA::FaceIndexA)*m_pahmModel->g_elemIndex[1][0];
	indxbd.BindFlags=D3D11_BIND_INDEX_BUFFER;
	indxbd.CPUAccessFlags=0;
	indxbd.MiscFlags=0;

	D3D11_SUBRESOURCE_DATA IndxData;
	ZeroMemory(&IndxData,sizeof(IndxData));
	IndxData.pSysMem= &faceIndex;
	IndxData.SysMemPitch=0;
	IndxData.SysMemSlicePitch=0;

	hr=pDevice->CreateBuffer(&indxbd,&IndxData,&m_pIndexBuffer);
	if(FAILED(hr))
		return hr;
    
	//Release ahm model object
	if( m_pahmModel )
	{
		m_pahmModel->Release();
		delete m_pahmModel;
		m_pahmModel=NULL;
	}


	return S_OK;
}

void AshaModelClass::SetModel(ID3D11DeviceContext* pDeviceContext)
{
	//Bind vertex buffer to IA stage
	UINT vbstride=sizeof(modelA::VertexA);
	UINT vboffset=0;
	pDeviceContext->IASetVertexBuffers(0,1,&m_pVertexBuffer,&vbstride,&vboffset);

	//Bind index buffer to IA stage
	UINT idoffset=0;
	pDeviceContext->IASetIndexBuffer( m_pIndexBuffer,DXGI_FORMAT_R32_UINT,idoffset );

	return;

}

void AshaModelClass::SetPrimTopology(ID3D11DeviceContext* pDeviceContext,D3D_PRIMITIVE_TOPOLOGY primTopology)
{
	//Set primitive topology
	pDeviceContext->IASetPrimitiveTopology(primTopology);
}

void AshaModelClass::ReleaseModel()
{
	if( m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer=NULL;
	}

	if( m_pVertexBuffer ) 
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer=NULL;
	}

	
	return;
}
