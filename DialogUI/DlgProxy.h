
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CDialogUIDlg;


// CDialogUIDlgAutoProxy ����Ŀ��

class CDialogUIDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CDialogUIDlgAutoProxy)

	CDialogUIDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CDialogUIDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CDialogUIDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CDialogUIDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

