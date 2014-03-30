
// PokerUIDlg.h : 头文件
//

#pragma once
#include "PokerPlayer.h"

// CPokerUIDlg 对话框
class CPokerUIDlg : public CDialogEx
{
// 构造
public:
	CPokerUIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_POKERAPP_DIALOG };

	Poker::CPokerPlayer m_Players[4];

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	

	// 生成的消息映射函数
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
