// OperToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "DialogUI.h"
#include "OperToolBar.h"
#include "afxdialogex.h"


// COperToolBar dialog

IMPLEMENT_DYNAMIC(COperToolBar, CDialogEx)

COperToolBar::COperToolBar(CWnd* pParent /*=NULL*/)
	: CDialogEx(COperToolBar::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

COperToolBar::~COperToolBar()
{
}

void COperToolBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COperToolBar, CDialogEx)
END_MESSAGE_MAP()


// COperToolBar message handlers
