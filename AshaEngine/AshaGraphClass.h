//AshaGraphClass.h
//Define Asha graphic engine class

#pragma once

#ifndef _ASHAGRAPHCLASS_H_
#define _ASHAGRAPHCLASS_H_

//Include customer files
#include "D3D11GraphClass.h"
#include "AshaModelClass.h"
#include "AshaShaderClass.h"

class AshaGraphClass
{
public:
	AshaGraphClass();
	~AshaGraphClass();

	HRESULT Initialize(HWND hWnd);
	void Render();
	void Release();

private:
	void RenderFrame();

private:
	D3D11GraphClass*            m_pd3dGraph;
	AshaModelClass*             m_pModel;
	AshaShaderClass*            m_pShader;

};

#endif