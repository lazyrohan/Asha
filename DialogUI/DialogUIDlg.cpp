
// DialogUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogUI.h"
#include "DialogUIDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDialogUIDlg �Ի���


IMPLEMENT_DYNAMIC(CDialogUIDlg, CDialogEx);

CDialogUIDlg::CDialogUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogUIDlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
	//m_pLoginDlg=NULL;
	//Initialize poker show flag to false.
	for(int i=0;i<12;i++)
	{
		bPokerFileShow[i]=false;
	}
	//Initialize play button flag.
	for(int i=0;i<9;i++)
	{
		bButtonAction[i]=false;
	}
	//Initialize players money pocket and bet times.
	for(int i=0;i<4;i++)
	{
		dMoneyPocket[i]=0;
		dBetNum[i]=0;
	}
	//Initialize player names
	playerName[0]="���";
	for(int i=1;i<4;i++)
	{
		playerName[i]="�������"+var2Str(i);
	
	}
}

CDialogUIDlg::~CDialogUIDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
	//if(m_pLoginDlg!=NULL)
		//m_pLoginDlg=NULL;
}

void CDialogUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDialogUIDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON10, &CDialogUIDlg::OnBnClickedButtonDistrib)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialogUIDlg::OnBnClickedButtonShowPoker)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogUIDlg::OnBnClickedButtonShowPokerP1)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialogUIDlg::OnBnClickedButtonPokerDrop)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogUIDlg::OnBnClickedButtonPokerShowP2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialogUIDlg::OnBnClickedButtonPokerShowP3)
	ON_BN_CLICKED(IDC_BUTTON6, &CDialogUIDlg::OnBnClickedButtonBet5)
	ON_BN_CLICKED(IDC_BUTTON7, &CDialogUIDlg::OnBnClickedButtonBet10)
	ON_BN_CLICKED(IDC_BUTTON8, &CDialogUIDlg::OnBnClickedButtonBet50)
END_MESSAGE_MAP()


// CDialogUIDlg ��Ϣ�������

BOOL CDialogUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//Check the saved user profiles and show login dialog
	m_pLoginDlg.Create(IDD_DIALOG_LOGIN,this);
	m_pLoginDlg.ShowWindow(SW_SHOW);

	
	
	//Initialize vars.

	//Set poker distribution button reactable.
	bButtonAction[8]=true;
	//Give everyone 500 yuan at start
	for(int i=0;i<4;i++)
	{
		dMoneyPocket[i]=500;
	}

	//Initialize ouput info.
	showOutputInfo("���֣�ÿ���˵õ�500Ԫ.\r\n",false);
	showUpdatedMoney();
	showPlayerName();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDialogUIDlg::OnPaint()
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
		//Paint poker.
		showPokerPic();
		//Load poker tool bar
	//m_pokerTool.Create(IDD_DIALOGBAR_OPRBUTTON,this);
	//Set tool bar position
	//CRect outputrc,toolrc;
	//GetDlgItem(IDC_EDIT_OUTPUT)->GetWindowRect(&outputrc);
	//ScreenToClient(&outputrc);
	//GetDlgItem(IDD_DIALOGBAR_OPRBUTTON)->GetWindowRect(&toolrc);
	//ScreenToClient(&toolrc);
	//m_pokerTool.MoveWindow(outputrc.CenterPoint().x,outputrc.CenterPoint().y,181,14,1);
	//m_pokerTool.SetForegroundWindow();
	//m_pokerTool.ShowWindow(SW_SHOW);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDialogUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CDialogUIDlg::OnClose()
{
	if (CanExit())
	{
		AfxMessageBox(_T("Sure to exit?"));
		CDialogEx::OnClose();
	}
}

void CDialogUIDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CDialogUIDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CDialogUIDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


//Distribute the poker to players.
void CDialogUIDlg::OnBnClickedButtonDistrib()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[8])
	{
		//Output info buffer 
		string outBuff="��ʼ����.\r\n";
		//Poker distribution process.
		pokerIndx player[4][3]={{0,0}};
		pokerDist(player);

		for(int i=0;i<4;i++)
		{
			for(int j=0;j<3;j++)
			{			
				pokerPicFile[i*3+j]=pokerColor[player[i][j].color]+pokerRang[player[i][j].number]+".bmp";
			}

			outBuff+="���"+var2Str(i+1)+"�����ơ�\r\n";
		}

		//Clear showed poker pics to back.
		for(int i=0;i<12;i++)
		{
			bPokerFileShow[i]=true;
		}
		//Active all buttons
		for(int i=0;i<8;i++)
		{
			bButtonAction[i]=true;
		}
		//Everyone lost 5 yuan for ante.
		//Clear bet times
		for(int i=0;i<4;i++)
		{
			dMoneyPocket[i]-=5;
			dBetNum[i]=0;
		}
		//Update dialog window
		showOutputInfo(outBuff,false);
		//Update money pocket
		showUpdatedMoney();
		Invalidate(1);
	}
	else
		return;

}

//Poker init
void CDialogUIDlg::pokerInit(CDialogUIDlg::pokerIndx pokerPool[54])
{
	//Initialize poker pool
	for(int i=0;i<52;i++)
	{
		pokerPool[i].color=i/13;
		pokerPool[i].number=i%13;
	}

	//Red Joke and balck Joke
	pokerPool[52].color=4;
	pokerPool[52].number=13;
	pokerPool[53].color=5;
	pokerPool[53].number=13;
}


//Poker distribution
void CDialogUIDlg::pokerDist(pokerIndx player[4][3])
{
  //Init poker
	pokerIndx pokerPool[54]={{0,0}};
	pokerInit(pokerPool);
	//Poker buffer
	pokerIndx pokerPlayed[12]={{0,0}};
	//Distribute poker for player
   //Get 12 pokers	
	srand(GetTickCount());
	for(int i=0,j=0;i<12;i++)
	{
		j=rand()%(52-i);
		pokerPlayed[i]=pokerPool[j];
		pokerPool[j]=pokerPool[51-i];
	}

	//Give poker to player
	//Four players.
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<4;j++)
		{
			player[j][i]=pokerPlayed[i*4+j];
		}
	}

	//Arrange plays`poker accroding range
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<2;j++)
		{
			if(player[i][j+1].number<=player[i][j].number)
			{
				int temp=0;
			    temp=player[i][j].number;
				player[i][j].number=player[i][j+1].number;
				player[i][j+1].number=temp;
			}
		}
	}


}

//Show poker pics
void CDialogUIDlg::showPokerPic(void)
{
	//Update showed poker pics info.
	string showPokerPicFile[12]={"\0"};
	for(int i=0;i<12;i++)
	{
		if(bPokerFileShow[i])
			showPokerPicFile[i]=pokerPicFile[i];
		else
			showPokerPicFile[i]="����.bmp";
		
	}
	//Get pic info.
	CStatic* stacPokerPic[12];
	CRect rectPokerPic[12]={0,0};
	for(int i=0;i<12;i++)
	{
	  //Get pic item 
	  stacPokerPic[i]=(CStatic*)GetDlgItem(1040+i);//IDC_POKERPIC_P**
	  //Get pic item rects
	  stacPokerPic[i]->GetClientRect(&rectPokerPic[i]);
	}

	//Load pic
	HBITMAP hpokerPic[12];
	BITMAP  bPokerPic[12];
	CBitmap playedPokerPic[12];
	for(int i=0;i<12;i++)
	{
		//Root src file
		string strb="E:\\Visual Studio 2010\\Projects\\Asha\\DialogUI\\res\\";
	    //C:\\Users\\Administrator\\Documents\\Visual Studio 2012\\Projects\\test\\DialogUI\\res\\
		
		strb+=showPokerPicFile[i];
		USES_CONVERSION;
		hpokerPic[i]=(HBITMAP)::LoadImageW(AfxGetInstanceHandle(),A2CW(strb.data()),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
		if(hpokerPic[i]==NULL)
		{
			AfxMessageBox(_T("Load file failed."),NULL,NULL);
			return;
		}
		playedPokerPic[i].Attach(hpokerPic[i]);
		playedPokerPic[i].GetBitmap(&bPokerPic[i]);
	}
	//Create compatable pic DC
	CDC memDC[12];
	CBitmap* oldBmp[12];
	for(int i=0;i<12;i++)
	{
		memDC[i].CreateCompatibleDC(stacPokerPic[i]->GetDC());
		oldBmp[i]=(CBitmap*)memDC[i].SelectObject(playedPokerPic[i]);
	}

	//Show poker pics.
	UpdateWindow();
	for(int i=0;i<12;i++)
	{
		stacPokerPic[i]->GetDC()->BitBlt(rectPokerPic[i].left,rectPokerPic[i].top,rectPokerPic[i].Width(),rectPokerPic[i].Height(),
			&memDC[i],0,0,SRCCOPY);
		memDC[i].SelectObject(&oldBmp[i]);
	}
}

//Show updated money pocket
void CDialogUIDlg::showUpdatedMoney(void)
{
	for(int i=0;i<4;i++)
	{
		//Get money data
		CString moneyShow=_T("��:");
	    moneyShow+=var2Str(dMoneyPocket[i]).data();
		//IDC_EDIT_MONEYPOCKETP*
		GetDlgItem(1030+i)->SetWindowTextW(moneyShow);
	}
}

//Show player names at group item
void CDialogUIDlg::showPlayerName()
{
	
	for(int i=0;i<4;i++)
	{
		//Get player names data
		CString playerNameShow=_T("\0");
		playerNameShow=playerName[i].data();
		//Show player names
		SetDlgItemTextW(1010+i,playerNameShow);
	}
}
//player require to show self pokers
void CDialogUIDlg::OnBnClickedButtonShowPoker()
{
	// TODO: Add your control notification handler code here
	
	if(bButtonAction[3])
	{
		//Hind other player and show self.
		for(int i=0;i<3;i++)
		{
			bPokerFileShow[i]=true;
		}

		Invalidate(1);
	}
	else
		return;
}


void CDialogUIDlg::OnBnClickedButtonShowPokerP1()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[0])
	{
		//Show  player1 poker.
		for(int i=3;i<6;i++)
		{
			bPokerFileShow[i]=true;
		}

		Invalidate(1);
	}
	else
		return;
}

void CDialogUIDlg::showOutputInfo(string outputInfo,bool bClearOld=false)
{
	//Show outputInfo
	CString cstrBuff=_T("\0");
	if(bClearOld)
	{
		string strtemp="\0";
		strtemp=outInfo;
		outInfo="Info:"+outputInfo+"\r\n"+strtemp;

	}
	else
		outInfo="Info:"+outputInfo+"\r\n";
	cstrBuff+=outInfo.data();
	GetDlgItem(IDC_EDIT_OUTPUT)->SetWindowTextW(cstrBuff);
}


void CDialogUIDlg::OnBnClickedButtonPokerDrop()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[4])
	{
		//Set all play button to imactive
		for(int i=0;i<8;i++)
		{
			bButtonAction[i]=false;
		}

		//Show all poker pics
		for(int i=0;i<12;i++)
		{
			bPokerFileShow[i]=true;
		}
		Invalidate(1);
	}
	else
		return;
}


void CDialogUIDlg::OnBnClickedButtonPokerShowP2()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[1])
	{
		//Show player2 pokers.
		for(int i=6;i<9;i++)
		{
			bPokerFileShow[i]=true;
		}
		Invalidate(1);
	}
	else
		return;
}


void CDialogUIDlg::OnBnClickedButtonPokerShowP3()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[2])
	{
		//Show player3 pokers.
		for(int i=9;i<12;i++)
		{
			bPokerFileShow[i]=true;
		}
		Invalidate(1);
	}
	else
		return;
}


BOOL CDialogUIDlg::PreTranslateMessage(MSG* pMsg)
{
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

//Bet process
void CDialogUIDlg::OnBnClickedButtonBet5()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[5])
	{
	//Player money.
		dBetNum[0]=1;
		dMoneyPocket[0]-=5*dBetNum[0];
		showUpdatedMoney();
	}
	else
		return;
}


void CDialogUIDlg::OnBnClickedButtonBet10()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[6])
	{
	//Player money.
	dMoneyPocket[0]-=10;
	showUpdatedMoney();
	}
	else
		return;
}


void CDialogUIDlg::OnBnClickedButtonBet50()
{
	// TODO: Add your control notification handler code here
	if(bButtonAction[7])
	{
	//Player money.
	dMoneyPocket[0]-=50;
	showUpdatedMoney();
	}
	else
		return;
}
