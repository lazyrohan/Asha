
// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CDialogUIDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CDialogUIDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDialogUIDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IDialogUI ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {14EEA91E-D7D5-49E0-A0C5-091B24D632D2}
static const IID IID_IDialogUI =
{ 0x14EEA91E, 0xD7D5, 0x49E0, { 0xA0, 0xC5, 0x9, 0x1B, 0x24, 0xD6, 0x32, 0xD2 } };

BEGIN_INTERFACE_MAP(CDialogUIDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CDialogUIDlgAutoProxy, IID_IDialogUI, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {61B53F62-8503-4916-8832-206ED8988F8C}
IMPLEMENT_OLECREATE2(CDialogUIDlgAutoProxy, "DialogUI.Application", 0x61b53f62, 0x8503, 0x4916, 0x88, 0x32, 0x20, 0x6e, 0xd8, 0x98, 0x8f, 0x8c)


// CDialogUIDlgAutoProxy ��Ϣ�������
