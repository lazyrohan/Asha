//PokerClass.cpp
#include "PokerClass.h"


//PokerClass::PokerClass(string a)
//{
//}


PokerClass::~PokerClass(void)
{

}

void PokerClass::distPoker(void)
{
  //Initialize poker
	initPoker();

  //Distribute poker for player
  //Get 12 pokers
	srand(GetTickCount());
	for(int i=12,j=0;i>0;i--)
	{
		j=rand()%i;
		playedPoker[12-i]=pokerPool[j];
		pokerPool[j-1]=pokerPool[51-(12-i)];

	}

}

void PokerClass::initPoker(void)
{
	//Array to store poker data from:2...10,J,Q,K,A
	const string pokerRang[13]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
	//Poker color：Red,black,club,diamond
	const string pokerColor[4]={"红桃","黑桃","梅花","方块"};
	//Initialize poker pool
	for(int i=0;i<52;i++)
	{
		pokerPool[i]=pokerRang[i%13]+pokerColor[i/13];
	}

	//Red Joke and balck Joke
	pokerPool[52]="小王";
	pokerPool[53]="大王";
}