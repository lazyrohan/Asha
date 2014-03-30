
// PokerUIDlg.h : ͷ�ļ�
//

#pragma once
#include "PokerPlayer.h"

// CPokerUIDlg �Ի���
class CPokerUIDlg : public CDialogEx
{
// ����
public:
	CPokerUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_POKERAPP_DIALOG };

	Poker::CPokerPlayer m_Players[4];

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	public:
	//Output info container
	string   sOutInfo;
	//Button reaction flag for play buttons.
	bool     bButtonAction[9];

	//Output info function
	void showOutputInfo(string outputInfo,bool bClearOld);
	//Open poker
	afx_msg void OnBnClickedButtonP0open();
	afx_msg void OnBnClickedButtonP1open();
	afx_msg void OnBnClickedButtonP2open();
	//Player operation
	afx_msg void OnBnClickedButtonDrop();
	afx_msg void OnBnClickedButtonBet5();
	afx_msg void OnBnClickedButtonBet10();
	afx_msg void OnBnClickedButtonBet50();
	//Ditribute poker to players
	afx_msg void OnBnClickedButtonDist();
	afx_msg void OnBnClickedButtonP3open();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool createDynmBtn(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
