//A poker process.
//PokerClass.h

#ifndef _POKERCLASS_H_
#define _POKERCLASS_H_
#pragma once

//Header files
#include <Windows.h>   //For sys clock function.
#include <math.h>      //For random and mathmatic function.
#include <string>
using namespace std;

//Class PokerClass

class PokerClass
{
public:
	//-------Datas---------------
	//A struct for poker data.
   //2...10,J,Q,K,A

	//Player number
	//unsigned playerNum;
	string pokerPool[54];
	string playedPoker[12];

	PokerClass(void)
	{
		for(int i=0;i<54;i++)
		pokerPool[i]="\0";
		for(int i=0;i<12;i++)
		playedPoker[i]="\0";
	};
	virtual ~PokerClass(void);
	

public:
	void distPoker(void);

	//-------Methods------------
//private:
	//Initialize poker data
	void initPoker();

};

#endif

