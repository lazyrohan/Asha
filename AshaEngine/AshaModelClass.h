//AshaModelClass.h
//Define model functions

#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

//Include d3dut_globle for globe files and functions
#include "d3dut_globle.h"
using namespace utg;
//Include ahm model class header
#include "ahmModelClass.h"

// class model
class AshaModelClass
{
public:
	AshaModelClass();
	~AshaModelClass();

public:
	//Load model from file
	HRESULT Initialize(string fileName);
	//Create buffer resource and bind to IA pipeline        
	HRESULT LoadModel(ID3D11Device* pDevice); 
	//Bind model buffer to pipeline
	void SetModel(ID3D11DeviceContext* pDeviceContext);
	void SetPrimTopology(ID3D11DeviceContext* pDeviceContext,D3D_PRIMITIVE_TOPOLOGY primTopology);
	//Release model 
	void ReleaseModel();        

private:
	
public:
	unsigned long           m_elemNum[3];
private:
	ahmModelClass*          m_pahmModel;
	ID3D11Buffer*           m_pVertexBuffer;
	ID3D11Buffer*           m_pIndexBuffer;

};
#endif