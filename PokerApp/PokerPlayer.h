//Poker player class
//PokerPlayer.h
#pragma once

#ifndef _POKERPLAYER_H_
#define _POKERPLAYER_H_

//Include sys headers
#include <Windows.h>
#include <math.h>
#include <string>
#include <sstream>
using namespace std;

namespace Poker
{
	//Two constants for poker names.
    //Array to store poker data from:2...10,J,Q,K,A
	const string pokerRang[15]={"2","3","4","5","6","7","8","9","10","J","Q","K","A","王","背景"};
	//Poker color：Red,black,club,diamond
	const string pokerColor[7]={"方块","梅花","黑桃","红桃","小","大","\0"};

	//Poker info struct
	struct PokerIndx
	{
		//Color index
		int color;
		//Range index
		int number;
		//Initialize function
		PokerIndx(void)
		{
			color=0;
			number=0;
		}
		PokerIndx(int acolor,int bnum)
		{
			color=acolor;
			number=bnum;
		};
		//Get poker name function
		string pokerName(void)
		{
			return Poker::pokerColor[color]+Poker::pokerRang[number];
		};
	};

	//Common debug functions--------------------------------
	//Var to string function
	template<class T> string var2Str(T var)
	{
		stringstream ss;
		ss<<var;
		return ss.str();
	}

	/*
	//Erro test function
	void errotest(void)
	{
		CString ecstr=_T("Error number: ");
		ecstr+=var2Str(GetLastError()).data();
		AfxMessageBox(ecstr,NULL,NULL);
	}
	//Test variable value
	void vartest(string val)
	{
		CString vcs=_T("变量值为： ");
		vcs+=val.data();
		AfxMessageBox(vcs,NULL,NULL);
	}
	//*/

//CPokerPlay class

class CPokerPlayer
{

public:
	CPokerPlayer(void);
	//Construct function
	CPokerPlayer(string name,PokerIndx pok[3],bool pokerFileShow,int mony,int bet,bool lost,bool banker)
		{
		    playerName=name;
			for(int i=0;i<3;i++)
			{
			  poker[i]=pok[i];
			}
			bPokerFileShow=pokerFileShow;
			money=mony;
			betNum=0;
			lostFlg=lost;
			bankerFlag=banker;

		};

	virtual ~CPokerPlayer(void);

	//Variables member for process----------------------------------	
public:
	//Player info.
	//player name
	string     playerName;
public:
	//Player owened poker
	PokerIndx  poker[3];
	//Showed poker pic flag:0/1
	bool       bPokerFileShow;
	//Money ownd
	int        money;
	//Bet number
	int        betNum;
	//Wheather lost
	bool       lostFlg;
	//Banker flag(是否为庄家)
	bool       bankerFlag;
		
public:
	//Poker play functions----------------------------------
	 //Poker initialize function
	void pokerDist(CPokerPlayer players[4],bool dropKings);
	//Poker pics drawing function
	void showPokerPic(string sPokerPicSrcPath,HWND hDlg,int iPokerDrawCtlStartID);
	//Show update money pocket
	void showUpdatedMoney(HWND hDlg,int iMoneyPocketDrawCtlID);	
	//Player name function.
	void showPlayerName(HWND hDlg,int iPlayerNameDrawCtlID);
};


	

}

#endif

