//CAshaWnd.cpp

#include "CAshaWnd.h"


CAshaWnd::CAshaWnd(void)
	
{
	//Initialize variables
	m_hWnd=NULL;
	//m_hInst=NULL;
	m_sWndTxt=TEXT("New window");
	m_hIcon=NULL;
	m_hIConSm=NULL;
	m_hCursor=LoadCursorW(NULL,IDC_ARROW); 
	m_cWndEdgeColor=RGB(200,100,255);
	m_bMosueHover=false;
	m_pMousePos.x=0;
	m_pMousePos.y=0;
}


CAshaWnd::~CAshaWnd(void)
{
	//SafeRelease(&m_pCaptionLayout);
}


BOOL CAshaWnd::InitInstance(HINSTANCE, int)
{
	//Initialize D2D

	return true;
}

BOOL CAshaWnd::CreateWnd(HINSTANCE hInstance,UINT wndStyle)
{
	//m_hInst=hInstance;

	//Registe window class
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)m_func.MemberFuncCall(this,CAshaThunk::GetMemberFuncAddr(&CAshaWnd::WndMsgProc),2);
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= HINST_THISCOMPONENT;
	wcex.hIcon			= m_hIcon;
	wcex.hCursor		= m_hCursor;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= TEXT("AshaWindowClass");
	wcex.hIconSm		= m_hIConSm;

	RegisterClassExW(&wcex);

	//Create no caption no border window
	//Set default window accroding to system resolution
	m_hWnd = CreateWindowExW(NULL,TEXT("AshaWindowClass"),NULL, wndStyle|WS_OVERLAPPED,
		(int)GetSystemMetrics(SM_CXFULLSCREEN)/6,13, (int)(GetSystemMetrics(SM_CXFULLSCREEN)/3),
		GetSystemMetrics(SM_CYFULLSCREEN), NULL, NULL, HINST_THISCOMPONENT, NULL);

   if (!m_hWnd)
   {
      return FALSE;
   }

   //Move window title and border style
	LONG dwStyle=GetWindowLongW(m_hWnd,GWL_STYLE);//Store window style	
	dwStyle&=~WS_CAPTION;    //Move caption ,move border
	//Move extra style
	LONG dwExStyle=GetWindowLongW(m_hWnd,GWL_EXSTYLE);
	dwExStyle&=~WS_CAPTION;
	SetWindowLongW(m_hWnd,GWL_STYLE,dwStyle);//Set new window style
	SetWindowLongW(m_hWnd,GWL_EXSTYLE,dwExStyle);//Set new window extra style
	SetWindowPos(NULL,NULL,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);
	//SetLayeredWindowAttributes(m_hWnd,NULL,255,LWA_ALPHA);
	//Transfer default msg process to selfdefined
	//Store def wndproc to userdata
	//SetWindowLongW(m_hWnd,GWL_USERDATA,(LONG)m_hWnd);
	//SetWindowLongW(m_hWnd,GWL_WNDPROC,(LONG)m_func.MemberFuncCall(this,CAshaThunk::GetMemberFuncAddr(&CAshaWnd::WndMsgProc),2));

	//Initialize D2D engieen
	HRESULT hr=S_OK;
	hr=m_D2DEng.CreateFactory();
	IDWriteTextLayout* pTxtLayout=NULL;
	if(SUCCEEDED(hr))
	{
		RECT rc={0,0,0,0};
		GetClientRect(m_hWnd,&rc);
		m_D2DEng.CreateCaptionTextLayout(TEXT("ÐÂ´°¿Ú new window"),(float)rc.right,26.0f);
		m_D2DEng.CreateContentTextLayout(TEXT("ÄÚÈÝ¡£¡£¡£"),(float)rc.right,(float)(rc.bottom-26));
	}

   return hr;
}


BOOL CAshaWnd::ShowWnd(int nCmdShow)
{
	 ShowWindow(m_hWnd, nCmdShow);
     UpdateWindow(m_hWnd);

	 return true;
}


LPWSTR CAshaWnd::GetWndName()
{
	return CAshaWnd::m_sWndTxt;
}


BOOL CAshaWnd::SetWndName(LPWSTR wndName)
{
    CAshaWnd::m_sWndTxt=wndName;
	return true;
}


LRESULT CAshaWnd::WndMsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_COMMAND:
		{
			/*
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		*/
		}
		break;

	case WM_NCPAINT:
		{
			//HDC hdc;
           // hdc = GetDCEx(hWnd, (HRGN)wParam, DCX_WINDOW|DCX_INTERSECTRGN);
           // Paint into this DC 
           //ReleaseDC(hWnd, hdc);

		}
		break;
	case WM_PAINT:
		{
			//Window drawing
			WndDraw();
			//Client area drawing
			OnPaint();

			return true;
		}
		break;
///*
	case WM_ERASEBKGND:
		{
			return false;
		}

		break;
//*/
	case WM_KEYDOWN:
		{
			OnEscape(wParam,lParam);
		}
		break;

	case WM_MOUSEMOVE:
		{
			
			return OnMosueMove(wParam,lParam);
		}
		break;

	case WM_MOUSEHOVER:
		{
			return OnMouseHover();
		}
		break;

	case WM_MOUSELEAVE:
		{
			return OnMouseLeave();
		}
		break;
	case WM_LBUTTONDBLCLK:

		{
			return OnLBtnDbClk(wParam,lParam);
		}

		break;

	case WM_LBUTTONDOWN:
		{
			return OnLBtnDown(wParam,lParam);
		}
		break;

	case WM_LBUTTONUP:
		{
			return OnLBtnUp(wParam,lParam);
		}
		break;

	case WM_RBUTTONDBLCLK:
		{
			return OnRBtnDbClk(wParam,lParam);
		}
		break;

	case WM_RBUTTONDOWN:
		{
			return OnRBtnDow(wParam,lParam);
			
		}
		break;

	case WM_RBUTTONUP:
		{
			return OnRBtnUp(wParam,lParam);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}

	return true;
}


BOOL  CAshaWnd::WndDraw(void)
{
	/*
	   //Get precreate window client area
	    RECT rc={0,0,0,0};
		GetClientRect(m_hWnd,&rc);

		HDC hdc=GetDC(m_hWnd);
       //Draw window edge

		SelectObject(hdc,GetStockObject(DC_PEN));
		SetDCPenColor(hdc,m_cWndEdgeColor);

		LineTo(hdc,rc.right,rc.top);
		MoveToEx(hdc,rc.right-1,rc.top,(LPPOINT)NULL);
		LineTo(hdc,rc.right-1,rc.bottom);
		MoveToEx(hdc,rc.right,rc.bottom-1,(LPPOINT)NULL);
		LineTo(hdc,rc.left,rc.bottom-1);
		LineTo(hdc,rc.left,rc.top);
		
		//Title draw
		TextOutW(hdc,rc.left+16,rc.top+6,m_sWndTxt,lstrlenW(m_sWndTxt));
		ReleaseDC(NULL,hdc);
		*/
	m_D2DEng.BegainDraw(m_hWnd);

	HRESULT hr=S_OK;
	//Create brushes
	//Create wnd edge line brush
	ID2D1SolidColorBrush* wndEdgColor=NULL;
	hr=m_D2DEng.GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::WhiteSmoke),&wndEdgColor);

	//Create wnd fill brush
	ID2D1LinearGradientBrush* wndFillColor=NULL;
	ID2D1GradientStopCollection* pGradStopCllection=NULL;
	//Gradient stop struct
	D2D1_GRADIENT_STOP stop[2];
	stop[0].color=D2D1::ColorF(D2D1::ColorF::DarkBlue);
	stop[0].position=0.0f;
	stop[1].color=D2D1::ColorF(D2D1::ColorF::DeepSkyBlue);
	stop[1].position=1.0f;
	//Create collection
	hr=m_D2DEng.GetRenderTarget()->CreateGradientStopCollection(
		stop,                                                  //stops
		2,                                                     //stop count
		D2D1_GAMMA_2_2,                                        //Gama color space
		D2D1_EXTEND_MODE_CLAMP,
		&pGradStopCllection
		);

	//Create brush

	hr=m_D2DEng.GetRenderTarget()->CreateLinearGradientBrush(
		D2D1::LinearGradientBrushProperties(D2D1::Point2F(0.0f,0.0f),D2D1::Point2F(0.0f,40.0f)),
		pGradStopCllection,
		&wndFillColor
		);

	//Realese collection
	SafeRelease(&pGradStopCllection);


	//Get render target size
	D2D1_SIZE_F rtsize=m_D2DEng.GetRenderTarget()->GetSize();
	    //Drawing process
		//Draw wnd edge
		RECT rc;
		GetClientRect(m_hWnd,&rc);
		D2D1_RECT_F edgerc=D2D1::RectF((FLOAT)rc.left,(FLOAT)rc.top,(FLOAT)rtsize.width,(FLOAT)rtsize.height);
		D2D1_RECT_F capitalRc=D2D1::RectF((FLOAT)rc.left,(FLOAT)rc.top,(FLOAT)rc.right,26.0f);
		//m_D2DEng.GetRenderTarget()->DrawLine(D2D1::Point2F(100.0f,100.0f),D2D1::Point2F(400.0f,400.0f),wndEdgColor,1.0f);
		
		//m_D2DEng.GetRenderTarget()->FillRectangle(&edgerc,wndFillColor);
		m_D2DEng.GetRenderTarget()->DrawRectangle(&edgerc,wndEdgColor,1.0f);
		m_D2DEng.GetRenderTarget()->FillRectangle(&capitalRc,wndFillColor);
		m_D2DEng.DrawCaptionText(20.0f,5.0f,wndEdgColor);
		m_D2DEng.DrawContentText(5.0f,31.0f,wndEdgColor);

		m_D2DEng.DrawImg(5.0f,32.0f,(float)rc.right,(float)rc.bottom);
		m_D2DEng.DrawContentText(5.0f,31.0f,wndEdgColor);

		hr=m_D2DEng.GetRenderTarget()->EndDraw();

		//Release resource
		m_D2DEng.ReleaseDevice();
		SafeRelease(&wndEdgColor);
		SafeRelease(&wndFillColor);

	return hr;

}


BOOL  CAshaWnd::WndMove(void)
{
	//Get mouse window position and client position
			POINT mousePos={0,0};
			RECT wrc={0,0,0,0};
			RECT crc={0,0,0,0};
		    GetWindowRect(m_hWnd,&wrc);
			GetClientRect(m_hWnd,&crc);
			mousePos=GetCursorPoint(m_hWnd);

			if(m_pMousePos.x==0)
				m_pMousePos.x=mousePos.x;
			if(m_pMousePos.y==0)
				m_pMousePos.y=mousePos.y;
			MoveWindow(m_hWnd,wrc.left+mousePos.x-m_pMousePos.x,wrc.top+mousePos.y-m_pMousePos.y,crc.right,crc.bottom,true);

			m_pMousePos=mousePos;

		   return true;
}


BOOL CAshaWnd::WndMax(void)
{
	//Get present window rect
	RECT rc={0,0,0,0};
	GetWindowRect(m_hWnd,&rc);
	//If max restore
	if(rc.left==0&&rc.top==0&&rc.right==(GetSystemMetrics(SM_CXFULLSCREEN))&&(rc.bottom==GetSystemMetrics(SM_CYFULLSCREEN)+26))
	    return MoveWindow(m_hWnd,(int)GetSystemMetrics(SM_CXFULLSCREEN)/6,13, (int)(GetSystemMetrics(SM_CXFULLSCREEN)/3),GetSystemMetrics(SM_CYFULLSCREEN),true);
	else
		return MoveWindow(m_hWnd,0,0,GetSystemMetrics(SM_CXFULLSCREEN),GetSystemMetrics(SM_CYFULLSCREEN)+26,true);
}


BOOL CAshaWnd::WndMin(void)
{
	ShowWindow(m_hWnd,SW_MINIMIZE);
    return UpdateWindow(m_hWnd);
}


BOOL CAshaWnd::WndFullScreen(void)
{
	//Get present window rect
	RECT rc={0,0,0,0};
	GetClientRect(m_hWnd,&rc);
	//If fullscreen restore
	if(rc.left==0&&rc.top==0&&rc.right==(GetSystemMetrics(SM_CXSCREEN))&&(rc.bottom==GetSystemMetrics(SM_CYSCREEN)))
	    return MoveWindow(m_hWnd,(int)GetSystemMetrics(SM_CXFULLSCREEN)/6,13, (int)(GetSystemMetrics(SM_CXFULLSCREEN)/3),GetSystemMetrics(SM_CYFULLSCREEN),true);
	else
		return MoveWindow(m_hWnd,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),true);
}


BOOL CAshaWnd::WndClose(void)
{
	return PostMessageW(m_hWnd,WM_CLOSE,NULL,NULL);
	
}


POINT CAshaWnd::GetCursorPoint(HWND hWnd)
{
	//Get cursor screen position and client rect
	POINT scPos={0,0};
	RECT  rc={0,0,0,0};

	GetCursorPos(&scPos);
	GetClientRect(hWnd,&rc);

	//Get related position and store
	scPos.x-=rc.left;
	scPos.y-=rc.top;

	return scPos;
}


BOOL CAshaWnd::OnPaint(void)
{
	/*
	RECT rc,rcd;
	GetClientRect(m_hWnd,&rc);

	HDC hdc=GetDC(m_hWnd);

	rcd.left=rc.right/4;
	rcd.top=rc.bottom/4;
	rcd.right=rc.right*3/4;
	rcd.bottom=rc.bottom*3/4;


	//LineTo(hdc,200,200);
	HBRUSH hbr=GetSysColorBrush(COLOR_HOTLIGHT);
	SelectBrush(hdc,hbr);
	FillRect(hdc,&rcd,hbr);

	//
	*/
	
	
	return true;
}


BOOL CAshaWnd::OnMouseHover(void)
{
	//Change widow edge color to highlight.
	
	m_cWndEdgeColor=(COLORREF)GetStockObject(COLOR_HOTLIGHT);
	RECT rc={0,0,0,0};
	GetClientRect(m_hWnd,&rc);
	InvalidateRect(m_hWnd,&rc,true);
	
	return true;
}


BOOL CAshaWnd::OnMouseLeave(void)
{
	//Set mouse hover flag to false
	m_bMosueHover=false;
	//Set temperay mouse position to (0,0)
	m_pMousePos.x=0;
	m_pMousePos.y=0;
	//Set window edge color to default
	m_cWndEdgeColor=RGB(200,100,255);
	RECT rc={0,0,0,0};
	GetClientRect(m_hWnd,&rc);
	//InvalidateRect(m_hWnd,&rc,true);

	return true;
}


BOOL CAshaWnd::OnMosueMove(WPARAM wParam, LPARAM lParam)
{
	//Get WM_MOUSEHOVER and MOUSELEAVE message
			if(!m_bMosueHover)
			{
				TRACKMOUSEEVENT tme;
				tme.cbSize=sizeof(tme);
				tme.dwFlags=TME_HOVER|TME_LEAVE;
				tme.hwndTrack=m_hWnd;
				tme.dwHoverTime=HOVER_DEFAULT; //Inspect time in ms.
				TrackMouseEvent(&tme);
				m_bMosueHover=true;
			}
			
			//Window move procedure
			if(wParam&MK_LBUTTON)
			{
				return WndMove();

			}

			return true;
}


BOOL CAshaWnd::OnLBtnDbClk(WPARAM wParam, LPARAM lParam)
{
	//Get desktop info
			RECT rc={0,0,0,0};
			POINT pos=GetCursorPoint(m_hWnd);
			GetClientRect(m_hWnd,&rc);
			if((pos.y<=(rc.top+100)))
			{
				return WndMax();
			}
			else
			{
				if((pos.y>=(rc.bottom-100)))
				    return WndMin();
				else
					return WndFullScreen();
			}
}


BOOL CAshaWnd::OnLBtnDown(WPARAM wParam, LPARAM lParam)
{
	return true;
}


BOOL CAshaWnd::OnLBtnUp(WPARAM wParam, LPARAM lParam)
{
	//Set temperay mouse position to (0,0)
			m_pMousePos.x=0;
			m_pMousePos.y=0;

			//Close window 
			{
				POINT msPos={0,0};
				msPos.x=GET_X_LPARAM(lParam);
				msPos.y=GET_Y_LPARAM(lParam);
				RECT rc={0,0,0,0};
				GetClientRect(m_hWnd,&rc);

				if(msPos.x>=rc.right-50&&msPos.y<=50)
				{
					return WndClose();
				}
			
			}

			return true;
}


BOOL CAshaWnd::OnRBtnDbClk(WPARAM wParam, LPARAM lParam)
{
	return true;
}


BOOL CAshaWnd::OnRBtnDow(WPARAM wParam, LPARAM lParam)
{
	//MessageBox(NULL,TEXT("Test right button menue"),NULL,NULL);
	return true;
}


BOOL CAshaWnd::OnRBtnUp(WPARAM wParam, LPARAM lParam)
{
	HRESULT hr=S_OK;
	RECT rc={0,0,0,0};
	GetClientRect(m_hWnd,&rc);
	hr=m_D2DEng.CreateD2DBitmapFromFile(m_hWnd);
	if(SUCCEEDED(hr))
		InvalidateRect(m_hWnd,&rc,true);
	return hr;
}


BOOL CAshaWnd::OnEscape(WPARAM wParam, LPARAM lParam)
{
	if(wParam&VK_ESCAPE)
			{
				MessageBoxW(m_hWnd,TEXT("Sure to exit?"),TEXT("Exit"),MB_OKCANCEL);
				return WndClose();
			}

	return true;
}