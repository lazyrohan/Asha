//AshaWnd.h
//Base window class

#pragma once

//include globle header files
#include"GlbHeader.h""
//include CWnd  class files 
#include <afxwin.h>

class CAshaWnd :
	public CWnd
{
public:
	CAshaWnd(void);
	virtual ~CAshaWnd(void);

private:
	//D2D base members------------------------------
	//HWND                      m_hWnd;
	ID2D1Factory*             m_pD2D1Facatory;
	ID2D1HwndRenderTarget*    m_pHwndRenderTarget;

	//Brushes for drawing
	ID2D1SolidColorBrush*               m_pEdgeBrush;      //For  wnd edge line fill
	ID2D1LinearGradientBrush*           m_pWndBrush;       //Wnd fill brush
    //ID2D1SolidColorBrush*               m_pRectFillBrush;      //For wnd rect fill

private:
	//D2D drawing process
	//Initialize device dependent resource
	HRESULT CreateDeviceDependentSource(void);

	//Discard resource as exit
	HRESULT DiscardDeviceDependentSource(void);

	//Create device independent resource for other usage
	HRESULT CreateDeviceIndepentedSource(void);

	//Render content
	HRESULT OnRender(void);

	//Resize render target
	void    OnResize(UINT width,UINT height);

public:
	//Set member vars
	void SetWndEdgeBrush();
	void SetWndFillBrush();
	//void Set

public:
	//OverLoad CWnd class message handler functions
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseLeave();
};

