//A dynamic button class 
//DymButton.h

#ifndef _DYMBUTTON_H_
#define _DYMBUTTON_H_
#pragma once

#include <string>
using namespace std;


// CDymButton class

class CDymButton : public CButton
{
	DECLARE_DYNAMIC(CDymButton)

public:
	CDymButton();
	virtual ~CDymButton();

	//Variables for button creation
private:
	//Button caption
	string   sBtnCaption;
	int      iExtraStyle;
	CRect    rBtnRect;
	CWnd*    pParentWnd;
	unsigned uCtlID;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void PreSubclassWindow();
	//Function for change button parameters
	void    setBtnCaption(string BtnCaption);
	void    setExtraBtnStyle(int btnStyle);
	void    setBtnRect(CRect BtnRc);

private:
	bool    draw(void);
};

#endif
