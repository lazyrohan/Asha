
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogUI.h"
#include "DlgProxy.h"
#include "DialogUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDialogUIDlgAutoProxy

IMPLEMENT_DYNCREATE(CDialogUIDlgAutoProxy, CCmdTarget)

CDialogUIDlgAutoProxy::CDialogUIDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CDialogUIDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CDialogUIDlg)))
		{
			m_pDialog = reinterpret_cast<CDialogUIDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CDialogUIDlgAutoProxy::~CDialogUIDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CDialogUIDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CDialogUIDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDialogUIDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IDialogUI 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {14EEA91E-D7D5-49E0-A0C5-091B24D632D2}
static const IID IID_IDialogUI =
{ 0x14EEA91E, 0xD7D5, 0x49E0, { 0xA0, 0xC5, 0x9, 0x1B, 0x24, 0xD6, 0x32, 0xD2 } };

BEGIN_INTERFACE_MAP(CDialogUIDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CDialogUIDlgAutoProxy, IID_IDialogUI, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {61B53F62-8503-4916-8832-206ED8988F8C}
IMPLEMENT_OLECREATE2(CDialogUIDlgAutoProxy, "DialogUI.Application", 0x61b53f62, 0x8503, 0x4916, 0x88, 0x32, 0x20, 0x6e, 0xd8, 0x98, 0x8f, 0x8c)


// CDialogUIDlgAutoProxy 消息处理程序
