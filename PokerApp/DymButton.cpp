// DymButton.cpp : implementation file
//

#include "stdafx.h"
#include "PokerApp.h"
#include "DymButton.h"


// CDymButton

IMPLEMENT_DYNAMIC(CDymButton, CButton)

CDymButton::CDymButton()
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CDymButton::~CDymButton()
{
}


BEGIN_MESSAGE_MAP(CDymButton, CButton)
END_MESSAGE_MAP()



// CDymButton message handlers




void CDymButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{


	// TODO:  Add your code to draw the specified item
}


void CDymButton::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}


bool CDymButton::draw(void)
{
	//Draw button process
	//Turn string to LPCTSR
	CString str=_T("\0");
	str=sBtnCaption.data();

	//Create button
	Create(str,WS_CHILD|WS_CAPTION|BS_PUSHBUTTON|iExtraStyle,rBtnRect,pParentWnd,uCtlID);
}

void CDymButton::setBtnCaption(string BtnCaption)
{
	sBtnCaption=BtnCaption;
}

void CDymButton::setBtnRect(CRect BtnRc)
{
	rBtnRect=BtnRc;
}

void CDymButton::setExtraBtnStyle(int btnStyle)
{
	iExtraStyle=btnStyle;
}

