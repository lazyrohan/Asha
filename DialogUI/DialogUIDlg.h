
// DialogUIDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <Windows.h>
#include <math.h>
#include <string>
#include <sstream>
//Include defined headers
#include "CLoginDlg.h"

using namespace std;

class CDialogUIDlgAutoProxy;

// CDialogUIDlg 对话框
class CDialogUIDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogUIDlg);
	friend class CDialogUIDlgAutoProxy;

// 构造
public:
	CDialogUIDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CDialogUIDlg();

// 对话框数据
	enum { IDD = IDD_DIALOGUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CDialogUIDlgAutoProxy* m_pAutoProxy;
	//Login dialog
	CLoginDlg              m_pLoginDlg;
	//Poker operation tool bar
	
protected:
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDistrib();

private:
	struct pokerIndx
	{
		int color;
		int number;
	};
	

private:
	//Var to string function
	template<class T> string var2Str(T var)
	{
		stringstream ss;
		ss<<var;
		return ss.str();
	}

	//Erro test function
	void errotest(void)
	{
		CString ecstr=_T("Error number: ");
		ecstr+=var2Str(GetLastError()).data();
		AfxMessageBox(ecstr,NULL,NULL);
	}
	void vartest(string val)
	{
		CString vcs=_T("变量值为： ");
		vcs+=val.data();
		AfxMessageBox(vcs,NULL,NULL);
	}

	//Poker initialize function
	void pokerInit(pokerIndx pokerPool[54]);
	void pokerDist(pokerIndx player[4][3]);
	//Poker pics drawing function
	void showPokerPic(void);
	//Show update money pocket
	void showUpdatedMoney(void);
	//Output info function
	string outInfo;
	void showOutputInfo(string outputInfo,bool bClearOld);
	//Player name function.
	string playerName[4];
	void showPlayerName(void);

public:
	//Picture variables for distributed poker.
	string pokerPicFile[12];
	//Showed poker pic flag:0/1
	bool     bPokerFileShow[12];
	//Button reaction flag for play buttons.
	bool     bButtonAction[9];
	//Players money pocket
	int      dMoneyPocket[4];
	//Players bet times
	int      dBetNum[4];

	afx_msg void OnBnClickedButtonShowPoker();
	afx_msg void OnBnClickedButtonShowPokerP1();
	afx_msg void OnBnClickedButtonPokerDrop();
	afx_msg void OnBnClickedButtonPokerShowP2();
	afx_msg void OnBnClickedButtonPokerShowP3();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonBet5();
	afx_msg void OnBnClickedButtonBet10();
	afx_msg void OnBnClickedButtonBet50();
};


    //Two constants for poker names.
    //Array to store poker data from:2...10,J,Q,K,A
	const string pokerRang[14]={"2","3","4","5","6","7","8","9","10","J","Q","K","A","王"};
	//Poker color：Red,black,club,diamond
	const string pokerColor[6]={"方块","梅花","黑桃","红桃","小","大"};
