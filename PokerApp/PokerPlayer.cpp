#include "stdafx.h"
#include "PokerPlayer.h"
using namespace Poker;


CPokerPlayer::CPokerPlayer(void):
	playerName("\0"),
	money(0),
	betNum(0),
	lostFlg(false),
	bankerFlag(false)
{
	//Intialize poker
	for(int i=0;i<3;i++)
	{
		poker[i]=PokerIndx(0,0);
	}

}


CPokerPlayer::~CPokerPlayer(void)
{

}


//Poker distribution
 void CPokerPlayer::pokerDist(CPokerPlayer players[4],bool dropKings)
{
  //Init poker------------------------------------
	int playerNum=4;
	//sizeof(players)/sizeof(CPokerPlayer);
	PokerIndx pokerPool[54]={PokerIndx(0,0)};
	//Initialize poker pool
	for(int i=0;i<52;i++)
	{
		pokerPool[i]=PokerIndx(i/13,i%13);
	}

	//Red Joke and balck Joke
	pokerPool[52]=PokerIndx(4,13);
	pokerPool[53]=PokerIndx(5,13);

	//Distribute poker for player-----------------
   //Rearrange pokers	
	srand(GetTickCount());
	int pokerNum=0;
	if(dropKings)
		pokerNum=52;
	else
		pokerNum=54;

	for(int i=0,j=0;i<pokerNum/2;i++)
	{
		PokerIndx pokertemp=PokerIndx();
		j=rand()%(52-i);
		pokertemp=pokerPool[j];
		pokerPool[j]=pokerPool[pokerNum-1-i];
		pokerPool[pokerNum-1-i]=pokertemp;
	}

	//Give poker to player
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<playerNum;j++)
		{
			players[j].poker[i]=pokerPool[i+j*playerNum];
		}
	}

	//Arrange plays`poker accroding range
	for(int i=0;i<playerNum;i++)
	{
		for(int j=0;j<2;j++)
		{
			if(players[i].poker[j+1].number<=players[i].poker[j].number)
			{
				PokerIndx temp=players[i].poker[j];
				players[i].poker[j]=players[i].poker[j+1];
				players[i].poker[j+1]=temp;
			}
		}
	}


}



//Show poker pics
void CPokerPlayer::showPokerPic(string sPokerPicSrcPath,HWND hDlg,int iPokerDrawCtlStartID)
{
	//Update showed poker pics info.
	string showPokerPicFile[3]={"\0"};   //Poker pics file name buffer.
	for(int i=0;i<3;i++)
	{
		if(bPokerFileShow)
			showPokerPicFile[i]=poker[i].pokerName();
		else
			showPokerPicFile[i]="±³¾°";
		
	}
	//Get pic info.
	CRect rectPokerPic[3]={0,0};
	for(int i=0;i<3;i++)
	{
	  //Get pic item
      //Get pic item rects
		GetClientRect(GetDlgItem(hDlg,iPokerDrawCtlStartID+i),&rectPokerPic[i]);
	 
	}

	//Load pic
	HBITMAP hpokerPic[3];
	BITMAP  bPokerPic[3];
	CBitmap playedPokerPic[3];
	for(int i=0;i<3;i++)
	{
		//Load sourece pics.
		string strtemp="\0";
		strtemp=sPokerPicSrcPath+showPokerPicFile[i]+".bmp";
		USES_CONVERSION;
		hpokerPic[i]=(HBITMAP)::LoadImageW(AfxGetInstanceHandle(),A2CW(strtemp.data()),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		if(hpokerPic[i]==NULL)
		{
			AfxMessageBox(_T("Load file failed."),NULL,NULL);
			return;
		}
		playedPokerPic[i].Attach(hpokerPic[i]);
		playedPokerPic[i].GetBitmap(&bPokerPic[i]);
	}
	//Create compatable pic DC
	HDC memDC[3];
	CBitmap* oldBmp[3];
	for(int i=0;i<3;i++)
	{

		memDC[i]=CreateCompatibleDC(GetDC(GetDlgItem(hDlg,iPokerDrawCtlStartID+i)));
		oldBmp[i]=(CBitmap*)SelectObject(memDC[i],playedPokerPic[i]);
	}
	//Show poker pics.
	UpdateWindow(hDlg);
	for(int i=0;i<3;i++)
	{
	    BitBlt(GetDC(GetDlgItem(hDlg,iPokerDrawCtlStartID+i)),rectPokerPic[i].left,rectPokerPic[i].top,rectPokerPic[i].Width(),rectPokerPic[i].Height(),
			memDC[i],0,0,SRCCOPY);
		SelectObject(memDC[i],&oldBmp[i]);
	}
}



//Show updated money pocket
void CPokerPlayer::showUpdatedMoney(HWND hDlg,int iMoneyPocketDrawCtlID)
{

		//Get money data
		CString moneyShow=_T("£¤");
		moneyShow+=var2Str(money).data();
		//IDC_EDIT_MONEYPOCKETP*
		SetWindowTextW(GetDlgItem(hDlg,iMoneyPocketDrawCtlID),moneyShow);
		//SetBkColor(GetDC(GetDlgItem(hDlg,iMoneyPocketDrawCtlID)),RGB(255,120,180));
		//SetTextColor(GetDC(GetDlgItem(hDlg,iMoneyPocketDrawCtlID)),RGB(255,120,180));
}



//Show player names at group item
void CPokerPlayer::showPlayerName(HWND hDlg,int iPlayerNameDrawCtlID)
{
	
		//Get player names data
		CString playerNameShow=_T("\0");
		playerNameShow+=playerName.data();
		//Show player names
		SetDlgItemTextW(hDlg,iPlayerNameDrawCtlID,playerNameShow);

}
