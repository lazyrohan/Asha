
// PokerApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPokerAppApp:
// �йش����ʵ�֣������ PokerApp.cpp
//

class CPokerAppApp : public CWinApp
{
public:
	CPokerAppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPokerAppApp theApp;