//-------------------------------------------------------------------------------
//CAshaWnd.h
//Version 0.0
//Created at 2013-02-28,by Rohan
//Define Asha Wnd class for self defined root win32 API windows class
//AshaWnd is the base class for other Asha window items,only creat a blank window.
//--------------------------------------------------------------------------------


#ifndef _ASHAWND_H_
#define _ASHAWND_H_

#define WIN32_LEAN_AND_MEAN
//Include sys headers
#include <windows.h>
#include <windowsx.h>
#include "Resource.h"
#include "CAshaThunk.h"
#include "CAshaD2D.h"

//-----------------------Gloable defines------------------------------------------

//Define golble values
//Ashawnd styles
//Title bar position
#define AS_TITLE_POS_TOP     0;
#define AS_TITLE_POS_BOTTOM  1;
#define AS_TITLE_POS_LEFT    2;
#define AS_TITLE_POS_RIGHT   3;


//------------------------AshaWnd Class--------------------------------------------

class CAshaWnd
{
public:
	CAshaWnd(void);
	virtual ~CAshaWnd(void);

	//Variables 
private:
	CAshaThunk          m_func;                                    //Get object member func address
	CAshaD2D            m_D2DEng;                                  //D2D drawing engieen
	HWND                m_hWnd;                                    //Window handler
	//HINSTANCE           m_hInst;                                   //Window instance
	
	HICON               m_hIcon;                                   //WndIcon
	HICON               m_hIConSm;                                 //Wnd small icon
	HCURSOR             m_hCursor;                                 //Wnd Cursor

	//Basic windows creat functions
public:
	BOOL				InitInstance(HINSTANCE, int);                                          //Initialize window
	BOOL                CreateWnd(HINSTANCE hInstance,UINT wndStyle);                          //Create window
	BOOL                ShowWnd(int nCmdShow);                                                 //Show Window

	//Globle variables operation function
	LPWSTR              GetWndName(void);//Get window name
	BOOL                SetWndName(LPWSTR wndName);//Set window name

private:
	//Store previous wndproc
	LRESULT CALLBACK    WndMsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);     //Self message procedure

//--------------------------Virtual members----------------------------------------------
	virtual BOOL         OnPaint(void);

//--------------------------Static members-----------------------------------------------

private:
	//Message handling static members

	//Window operation
	//TitleBar Drawing
	LPWSTR                m_sWndTxt;                                  //Title name
	unsigned int          m_uTitleBarHeight;                          //For title bar height set
    unsigned int          m_uTitleBarPos;                             //For title bar position:top,left,right,bottom
	bool                  TitleBarDraw(HWND hWnd);                    //Draw title bar

	//Window drawing
	RECT         m_rWndRect;                                          //Widow Rect
	COLORREF     m_cWndEdgeColor;                                     //Window edge color
	BOOL         WndDraw(void);                                       //Draw window
	BOOL         WndMove(void);                                       //Window move
	BOOL         WndMax(void);                                        //Window maximn and restore
	BOOL         WndMin(void);                                        //Window minimn
	BOOL         WndFullScreen(void);                                 //Window fullscreen
	BOOL         WndClose(void);                                      //Close window

	//Mouse actions
	BOOL         m_bMosueHover;                                       //Wheather mouse hover
	POINT        m_pMousePos;                                         //Mouse position
	BOOL         OnMouseHover(void);                                  //Mouse hover actions
	BOOL         OnMouseLeave(void);                                  //Mouse leave actions
	BOOL         OnMosueMove(WPARAM wParam, LPARAM lParam);           //Mouse move actions
	BOOL         OnLBtnDbClk(WPARAM wParam, LPARAM lParam);           //Mouse left button double clicked
	BOOL         OnLBtnDown(WPARAM wParam, LPARAM lParam);            //Mouse left button down
	BOOL         OnLBtnUp(WPARAM wParam, LPARAM lParam);              //Mouse left button up
	BOOL         OnRBtnDbClk(WPARAM wParam, LPARAM lParam);           //Mouse right button click
	BOOL         OnRBtnDow(WPARAM wParam, LPARAM lParam);             //Mouse right button down
	BOOL         OnRBtnUp(WPARAM wParam, LPARAM lParam);              //Mouse right button up(released)

	//Key actions 
	BOOL         OnEscape(WPARAM wParam, LPARAM lParam);              //ESC key

	//Help functions
	POINT        GetCursorPoint(HWND hWnd);                           //Get cursor window client point 

	//Text
	//IDWriteTextFormat* m_pStrFormat;

};



#endif