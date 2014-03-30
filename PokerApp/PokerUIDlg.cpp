
// PokerUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PokerApp.h"
#include "PokerUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPokerUIDlg �Ի���--------------------------------------------------------------



CPokerUIDlg::CPokerUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPokerUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//Initialize players
	for(int i=0;i<4;i++)
	{
		m_Players[i]=Poker::CPokerPlayer();
	}

	//Initialize play button flag.
	for(int i=0;i<9;i++)
	{
		bButtonAction[i]=false;
	}
}

void CPokerUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPokerUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_P0OPEN, &CPokerUIDlg::OnBnClickedButtonP0open)
	ON_BN_CLICKED(IDC_BUTTON_P1OPEN, &CPokerUIDlg::OnBnClickedButtonP1open)
	ON_BN_CLICKED(IDC_BUTTON_P2OPEN, &CPokerUIDlg::OnBnClickedButtonP2open)
	ON_BN_CLICKED(IDC_BUTTON_DROP, &CPokerUIDlg::OnBnClickedButtonDrop)
	ON_BN_CLICKED(IDC_BUTTON_BET5, &CPokerUIDlg::OnBnClickedButtonBet5)
	ON_BN_CLICKED(IDC_BUTTON_BET10, &CPokerUIDlg::OnBnClickedButtonBet10)
	ON_BN_CLICKED(IDC_BUTTON_BET50, &CPokerUIDlg::OnBnClickedButtonBet50)
	ON_BN_CLICKED(IDC_BUTTON_DIST, &CPokerUIDlg::OnBnClickedButtonDist)
	ON_BN_CLICKED(IDC_BUTTON_P3OPEN, &CPokerUIDlg::OnBnClickedButtonP3open)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPokerUIDlg ��Ϣ�������----------------------------------------------------------

BOOL CPokerUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//Initialize players start status
	//Set default poker pics to back.bmp
	///*
	//Set default poker pics to backside.
	Poker::PokerIndx defPoker[3]={Poker::PokerIndx()};
		for(int i=0;i<3;i++)
		{
			defPoker[i]=Poker::PokerIndx(6,14);
		}

	for(int i=0;i<4;i++)
	{
		//Initialize player names.
		m_Players[i]=Poker::CPokerPlayer::CPokerPlayer(("�������"+Poker::var2Str(i)),defPoker,false,500,0,false,false);
		//show player names.
		m_Players[i].showPlayerName(GetSafeHwnd(),IDC_STATIC_P0+i);
		//Show money pocket
        m_Players[i].showUpdatedMoney(GetSafeHwnd(),IDC_EDIT_MONEYPOCKETP0+i);
		
	}
	showOutputInfo("����ÿ����ҵõ�500Ԫ��",false);
	
	//Set poker dist button to active
	bButtonAction[8]=true;
	//*/
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPokerUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPokerUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		/*
		//Change background color
		CPaintDC dc(this);
		CRect crc;
		GetClientRect(crc);
		dc.FillSolidRect(crc,RGB(170,150,180));
		*/

		//Show poker pics
		//Root src file
		 string srcPath="G:\\Visual Studio 2010\\Projects\\Asha\\PokerApp\\res\\";
			            //"C:\\Users\\Administrator\\Documents\\Visual Studio 2012\\Projects\\test\\DialogUI\\res\\";

		for(int i=0;i<4;i++)
		{
			m_Players[i].showPokerPic(srcPath,GetSafeHwnd(),IDC_POKERPIC_P01+i*3);
		}

		//Draw dynamic button 

		//Show or hind button
		for(int i=0;i<9;i++)
		{
			if(bButtonAction[i])
			    GetDlgItem(IDC_BUTTON_P0OPEN+i)->ShowWindow(SW_SHOW);
			else
				GetDlgItem(IDC_BUTTON_P0OPEN+i)->ShowWindow(SW_HIDE);
		}
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPokerUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPokerUIDlg::showOutputInfo(string outputInfo,bool bClearOld=false)
{
	//Show outputInfo
	CString cstrBuff=_T("\0");
	if(!bClearOld)
	{
		string strtemp="\0";
		strtemp=sOutInfo;
		sOutInfo="Info>:"+outputInfo+"\r\n"+strtemp;

	}
	else
		sOutInfo="Info:"+outputInfo+"\r\n";
	cstrBuff+=sOutInfo.data();
	GetDlgItem(IDC_EDIT_OUTPUT)->SetWindowTextW(cstrBuff);
	//GetDlgItem(IDC_EDIT_OUTPUT)->SetFont(CFont(_T("����")),true);
}



void CPokerUIDlg::OnBnClickedButtonP0open()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[0])
	{
		//Hind other player and show self.
	     m_Players[0].bPokerFileShow=true;

		Invalidate(1);
	}
	else
		return;


}


void CPokerUIDlg::OnBnClickedButtonP1open()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[1])
	{
		//Show  player1 poker.
		m_Players[1].bPokerFileShow=true;

		Invalidate(1);
	}
	else
		return;

}


void CPokerUIDlg::OnBnClickedButtonP2open()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[2])
	{
		//Hind other player and show self.
		m_Players[2].bPokerFileShow=true;

		Invalidate(1);
	}
	else
		return;
}



void CPokerUIDlg::OnBnClickedButtonP3open()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[3])
	{
		//Hind other player and show self.
		m_Players[3].bPokerFileShow=true;

		Invalidate(1);
	}
	else
		return;
}

void CPokerUIDlg::OnBnClickedButtonDrop()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[4])
	{
		//Set all play button to imactive
		for(int i=0;i<8;i++)
		{
			bButtonAction[i]=false;
		}

		//Hind other player and show self.
		for(int i=0;i<4;i++)
		{
			m_Players[i].bPokerFileShow=true;
		}

		Invalidate(1);
	}
	else
		return;
}


void CPokerUIDlg::OnBnClickedButtonBet5()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[5])
	{
	//Player money.
		m_Players[0].betNum+=1;
		m_Players[0].money-=5;
		m_Players[0].showUpdatedMoney(GetSafeHwnd(),IDC_EDIT_MONEYPOCKETP0);
	}
	else
		return;
}


void CPokerUIDlg::OnBnClickedButtonBet10()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[5])
	{
	//Player money.
		m_Players[0].betNum+=1;
		m_Players[0].money-=10;
		m_Players[0].showUpdatedMoney(GetSafeHwnd(),IDC_EDIT_MONEYPOCKETP0);
	}
	else
		return;
}


void CPokerUIDlg::OnBnClickedButtonBet50()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[5])
	{
	//Player money.
		m_Players[0].betNum+=1;
		m_Players[0].money-=50;
		m_Players[0].showUpdatedMoney(GetSafeHwnd(),IDC_EDIT_MONEYPOCKETP0);
	}
	else
		return;

}


void CPokerUIDlg::OnBnClickedButtonDist()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[8])
	{
		//Output info buffer 
		string outBuff="��ʼ����.\r\n";
		//Poker distribution process.
		m_Players[0].pokerDist(m_Players,true);
		outBuff+="�������.\r\n";
		//Reset stataus 
		for(int i=0;i<4;i++)
		{
			//Clear showed poker pics to back.
			m_Players[i].bPokerFileShow=false;
			//Everyone lost 5 yuan for ante.
			m_Players[i].money-=5;
			//Clear bet times
			m_Players[i].betNum=0;
			//Show updated money pocket
			m_Players[i].showUpdatedMoney(GetSafeHwnd(),IDC_EDIT_MONEYPOCKETP0+i);
			//Test for poker dist.
			outBuff+=m_Players[i].playerName+"���:";
			for(int j=0;j<3;j++)
			{
				outBuff+=m_Players[i].poker[j].pokerName()+" ";			
			}
			outBuff+="\r\n";
		}
		//Active all operation  buttons
		for(int i=0;i<8;i++)
		{
			bButtonAction[i]=true;
		}
		
		//Update dialog window
		showOutputInfo(outBuff,false);
		Invalidate(1);
	}
	else
		return;
}



BOOL CPokerUIDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//When enter in Eidt control item and Escape key down,ignore them.
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
	{
		LPWSTR itemClassL=new WCHAR[255];
		::GetClassNameW(GetDlgItem(GetFocus()->GetDlgCtrlID())->GetSafeHwnd(),itemClassL,255);//��ȡ��ǰ����ؼ�����������
		LPWSTR classl=_T("Edit");
		if(*itemClassL==*classl)
			return true;
	}
	else
		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
			return true;


	return CDialogEx::PreTranslateMessage(pMsg);
}



bool CPokerUIDlg::createDynmBtn(void)
{
	//New CButton object 
	CButton *dymButton=new CButton;
	CRect dbtnRc=CRect(200,200,100,100);
	dymButton->Create(_T("Dym Button"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|WS_DISABLED,dbtnRc,this,IDC_BUTTON_DYM);
	return false;
}


HBRUSH CPokerUIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	if(nCtlColor==CTLCOLOR_DLG)
	{
		CBrush staticCtlBrush;
		staticCtlBrush.CreateSolidBrush(RGB(100,0,0));
		return staticCtlBrush;
	}
	return hbr;
}
