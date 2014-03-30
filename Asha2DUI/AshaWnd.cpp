#include "AshaWnd.h"


CAshaWnd::CAshaWnd(void):
	//m_hWnd(NULL),
	m_pD2D1Facatory(NULL),
	m_pHwndRenderTarget(NULL),
	m_pEdgeBrush(NULL),
	m_pWndBrush(NULL)
{
}


CAshaWnd::~CAshaWnd(void)
{
	//Realese source
	DiscardDeviceDependentSource();
	SafeRelease(&m_pD2D1Facatory);

}
BEGIN_MESSAGE_MAP(CAshaWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
//	ON_WM_MOUSEHOVER()
ON_WM_MOUSEHOVER()
ON_WM_MOUSEACTIVATE()
ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

//D2D drawing functions
HRESULT CAshaWnd::CreateDeviceIndepentedSource(void)
{
	HRESULT hr=S_OK;
	//Create D2D factory
	hr=D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&m_pD2D1Facatory);

	return hr;
}


HRESULT CAshaWnd::CreateDeviceDependentSource(void)
{
	HRESULT hr=S_OK;

	//Check device independent resource creation
	ASSERT(m_pD2D1Facatory!=NULL);
	ASSERT(m_pHwndRenderTarget==NULL);

	//Get window rect
	CRect rc;
	GetClientRect(&rc);

	//Translate to render target size
	D2D_SIZE_U size=D2D1::SizeU(rc.right-rc.left,rc.bottom-rc.top);

	//Create D2D render target
	//Fill render target property struct
	D2D1_RENDER_TARGET_PROPERTIES rtProp;
	rtProp.dpiX=0;                                              //Default DPI
	rtProp.dpiY=0;
	rtProp.minLevel=D2D1_FEATURE_LEVEL_DEFAULT;                 //Feature level
	rtProp.pixelFormat.format=DXGI_FORMAT_UNKNOWN;              //Pixel format
	rtProp.pixelFormat.alphaMode=D2D1_ALPHA_MODE_UNKNOWN;       //Alpha mode 
	rtProp.type=D2D1_RENDER_TARGET_TYPE_DEFAULT;                //Software or hardware render
	rtProp.usage=D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE;       //Compatable with GDI

	hr=m_pD2D1Facatory->CreateHwndRenderTarget(
		rtProp,
		D2D1::HwndRenderTargetProperties(m_hWnd,size),
		&m_pHwndRenderTarget
		);

	//Create brushes
	if(SUCCEEDED(hr))
	{
		//Create wnd edge line brush
		hr=m_pHwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black),&m_pEdgeBrush);
	}

	if(SUCCEEDED(hr))
	{
		//Create wnd fill brush
		ID2D1GradientStopCollection* pGradStopCllection=NULL;
		//Gradient stop struct
		D2D1_GRADIENT_STOP stop[2];
		stop[0].color=D2D1::ColorF(D2D1::ColorF::DarkGray);
		stop[0].position=0.0f;
		stop[1].color=D2D1::ColorF(D2D1::ColorF::Gray);
		stop[1].position=1.0f;
		//Create collection
		hr=m_pHwndRenderTarget->CreateGradientStopCollection(
			stop,                                                  //stops
			2,                                                     //stop count
			D2D1_GAMMA_2_2,                                        //Gama color space
			D2D1_EXTEND_MODE_CLAMP,
			&pGradStopCllection
			);

		//Create brush

		hr=m_pHwndRenderTarget->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(D2D1::Point2F(0.0f,0.0f),D2D1::Point2F(0.0f,40.0f)),
			pGradStopCllection,
			&m_pWndBrush
			);

		//Realese collection
		SafeRelease(&pGradStopCllection);
	}

	return hr;
}


HRESULT CAshaWnd::DiscardDeviceDependentSource(void)
{
	SafeRelease(&m_pWndBrush);
	SafeRelease(&m_pEdgeBrush);
	SafeRelease(&m_pHwndRenderTarget);
}


HRESULT CAshaWnd::OnRender(void)
{
	HRESULT hr=S_OK;
	hr=CreateDeviceDependentSource();

	if(SUCCEEDED(hr))
	{
		//Begain drawing
		m_pHwndRenderTarget->BeginDraw();
		//将呈现器目标的转换设置为单位矩阵，并清除窗口。
		m_pHwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pHwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		//检索绘制区域的大小
		D2D1_SIZE_F rtsize=m_pHwndRenderTarget->GetSize();

		//Drawing process
		//Draw wnd edge
		CRect wndrc;
		GetWindowRect(wndrc);
		D2D1_RECT_F edgerc=D2D1::RectF(wndrc.left,wndrc.top,rtsize.width,rtsize.height);
		m_pHwndRenderTarget->DrawRectangle(&edgerc,m_pEdgeBrush,2.0f);
		m_pHwndRenderTarget->FillRectangle(&edgerc,m_pWndBrush);

		hr=m_pHwndRenderTarget->EndDraw();

		    if (hr == D2DERR_RECREATE_TARGET)
    {
        hr = S_OK;
		DiscardDeviceDependentSource();
    }

	}

	return hr;
}


void    CAshaWnd::OnResize(UINT width,UINT height)
{
	if (m_pHwndRenderTarget)
    {
        // Note: This method can fail, but it's okay to ignore the
        // error here, because the error will be returned again
        // the next time EndDraw is called.
		m_pHwndRenderTarget->Resize(D2D1::SizeU(width, height));
    }

}

void CAshaWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		// TODO: Add your message handler code here
		// Do not call CWnd::OnPaint() for painting messages

	OnRender();

}


BOOL CAshaWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;

	//return CWnd::OnEraseBkgnd(pDC);
}


void CAshaWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	OnResize(cx,cy);
	Invalidate(false);
}


BOOL CAshaWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL hr=CreateDeviceIndepentedSource();

	return hr;
	//return CWnd::PreCreateWindow(cs);
}



void CAshaWnd::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_pEdgeBrush->SetColor(D2D1::ColorF(D2D1::ColorF::WhiteSmoke));
	Invalidate(false);
	CWnd::OnMouseHover(nFlags, point);
}


int CAshaWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CAshaWnd::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMouseLeave();
}
