//CAshaD2D.cpp

#include "CAshaD2D.h"


CAshaD2D::CAshaD2D(void):
	m_pD2D1Facatory(NULL),
	m_pDWriteFactory(NULL),
	m_pWICImgFactory(NULL),
	m_pHwndRenderTarget(NULL),
	m_pCaptionTxtLayout(NULL),
	m_pContentTxtLayout(NULL),
	m_pFrame(NULL),
	m_pD2DBitmap(NULL)
{

}


CAshaD2D::~CAshaD2D(void)
{
	//Realese source
	SafeRelease(&m_pD2DBitmap);
	SafeRelease(&m_pFrame);
	SafeRelease(&m_pCaptionTxtLayout);
	SafeRelease(&m_pContentTxtLayout);
	SafeRelease(&m_pHwndRenderTarget);
	SafeRelease(&m_pWICImgFactory);
	SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pD2D1Facatory);

}


HRESULT CAshaD2D::CreateFactory(void)
{
	HRESULT hr=S_OK;
	//Initialize com
	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	//Create WIC factory
	hr=CoCreateInstance(CLSID_WICImagingFactory1,NULL,CLSCTX_INPROC_SERVER,IID_PPV_ARGS(&m_pWICImgFactory));
	//Create D2D factory
	if(SUCCEEDED(hr))
		hr=D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,&m_pD2D1Facatory);
	//Create DWrite factory
	if(SUCCEEDED(hr))
		hr=DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&m_pDWriteFactory));

	return hr;
}


HRESULT  CAshaD2D::BegainDraw(HWND hWnd)
{
	HRESULT hr=S_OK;

	//Check device independent resource creation
	Assert(m_pD2D1Facatory!=NULL);

	if(m_pHwndRenderTarget!=NULL)
	{
		SafeRelease(&m_pHwndRenderTarget);
	}
	Assert(m_pHwndRenderTarget==NULL);

	//Create render target------------------------------------------------------
	//Get Render target size
	//Get window rect
	RECT rc;
	GetClientRect(hWnd,&rc);

	//Translate to render target size
	D2D_SIZE_U size=D2D1::SizeU(rc.right-rc.left,rc.bottom-rc.top);

	//Create D2D render target
	//Fill render target property struct
	D2D1_RENDER_TARGET_PROPERTIES rtProp;
	rtProp.dpiX=0;                                              //Default DPI
	rtProp.dpiY=0;
	rtProp.minLevel=D2D1_FEATURE_LEVEL_DEFAULT;                 //Feature level: 
	rtProp.pixelFormat.format=DXGI_FORMAT_UNKNOWN;              //Pixel format
	rtProp.pixelFormat.alphaMode=D2D1_ALPHA_MODE_UNKNOWN;       //Alpha mode 
	rtProp.type=D2D1_RENDER_TARGET_TYPE_DEFAULT;                //Software or hardware render
	rtProp.usage=D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE;       //Compatable with GDI

	hr=m_pD2D1Facatory->CreateHwndRenderTarget(
		rtProp,
		D2D1::HwndRenderTargetProperties(hWnd,size),
		&m_pHwndRenderTarget
		);

	if(SUCCEEDED(hr))
	{
		//Begain drawing
		m_pHwndRenderTarget->BeginDraw();
		//Set transform unit and clear background
		m_pHwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pHwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
	}
	return hr;
}


ID2D1HwndRenderTarget* CAshaD2D::GetRenderTarget(void)
{
	return m_pHwndRenderTarget;
}


void CAshaD2D::ReleaseDevice(void)
{
	SafeRelease(&m_pHwndRenderTarget);
}


HRESULT CAshaD2D::CreateCaptionTextLayout(WCHAR* pCaptionStr,FLOAT maxWidth,FLOAT maxHeight)
{
	HRESULT hr=S_OK;
	//Create default text format
	IDWriteTextFormat* pTxtFormat=NULL;
	hr=m_pDWriteFactory->CreateTextFormat(TEXT("Î¢ÈíÑÅºÚ"),NULL,DWRITE_FONT_WEIGHT_THIN,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,16.0f,TEXT("CN"),&pTxtFormat);
	//Set text aligment
	if(SUCCEEDED(hr))
		hr=pTxtFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	if(SUCCEEDED(hr))
		hr=pTxtFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	//Create text layout
	if(SUCCEEDED(hr))
	{
		if(m_pCaptionTxtLayout!=NULL)
			SafeRelease(&m_pCaptionTxtLayout);
		hr=m_pDWriteFactory->CreateTextLayout(pCaptionStr,lstrlenW(pCaptionStr),pTxtFormat,maxWidth,maxHeight,&m_pCaptionTxtLayout);
	}

	//Set text typography
	IDWriteTypography* txtTypgrah=NULL;

	if(SUCCEEDED(hr))
		hr=m_pDWriteFactory->CreateTypography(&txtTypgrah);

	if(SUCCEEDED(hr))
	{
		DWRITE_FONT_FEATURE fontFeature;
		fontFeature.nameTag=DWRITE_FONT_FEATURE_TAG_DEFAULT;
		fontFeature.parameter=1;
		hr=txtTypgrah->AddFontFeature(fontFeature);
	}

	if(SUCCEEDED(hr))
	{
		DWRITE_TEXT_RANGE txtRange={0,lstrlenW(pCaptionStr)};
		hr=m_pCaptionTxtLayout->SetTypography(txtTypgrah,txtRange);
	}

	if(SUCCEEDED(hr))
	{
		SafeRelease(&txtTypgrah);
		SafeRelease(&pTxtFormat);
	}
	return hr;
}


void CAshaD2D::DrawCaptionText(float orgx,float orgy,ID2D1Brush* foregroundBrush)
{
	m_pHwndRenderTarget->DrawTextLayout(D2D1::Point2F(orgx,orgy),m_pCaptionTxtLayout,foregroundBrush,D2D1_DRAW_TEXT_OPTIONS_NONE);
}


IDWriteTextLayout* CAshaD2D::GetCaptionTextLayout(void)
{
	return m_pCaptionTxtLayout;
}


HRESULT CAshaD2D::CreateContentTextLayout(WCHAR* pContentStr,FLOAT maxWidth,FLOAT maxHeight)
{
	HRESULT hr=S_OK;
	//Create default text format
	IDWriteTextFormat* pTxtFormat=NULL;
	hr=m_pDWriteFactory->CreateTextFormat(TEXT("Î¢ÈíÑÅºÚ"),NULL,DWRITE_FONT_WEIGHT_THIN,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,16.0f,TEXT("CN"),&pTxtFormat);
	//Set text aligment
	if(SUCCEEDED(hr))
		hr=pTxtFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if(SUCCEEDED(hr))
		hr=pTxtFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	//Create text layout
	if(SUCCEEDED(hr))
	{
		if(m_pContentTxtLayout!=NULL)
			SafeRelease(&m_pContentTxtLayout);
		hr=m_pDWriteFactory->CreateTextLayout(pContentStr,lstrlenW(pContentStr),pTxtFormat,maxWidth,maxHeight,&m_pContentTxtLayout);
	}

	//Set text typography
	IDWriteTypography* txtTypgrah=NULL;

	if(SUCCEEDED(hr))
		hr=m_pDWriteFactory->CreateTypography(&txtTypgrah);

	if(SUCCEEDED(hr))
	{
		DWRITE_FONT_FEATURE fontFeature;
		fontFeature.nameTag=DWRITE_FONT_FEATURE_TAG_DEFAULT;
		fontFeature.parameter=1;
		hr=txtTypgrah->AddFontFeature(fontFeature);
	}

	if(SUCCEEDED(hr))
	{
		DWRITE_TEXT_RANGE txtRange={0,lstrlenW(pContentStr)};
		hr=m_pContentTxtLayout->SetTypography(txtTypgrah,txtRange);
	}

	if(SUCCEEDED(hr))
	{
		SafeRelease(&txtTypgrah);
		SafeRelease(&pTxtFormat);
	}
	return hr;
}


void CAshaD2D::DrawContentText(float orgx,float orgy,ID2D1Brush* foregroundBrush)
{
	m_pHwndRenderTarget->DrawTextLayout(D2D1::Point2F(orgx,orgy),m_pContentTxtLayout,foregroundBrush,D2D1_DRAW_TEXT_OPTIONS_NONE);
}


IDWriteTextLayout* CAshaD2D::GetContentTextLayout(void)
{
	return m_pContentTxtLayout;
}


BOOL CAshaD2D::OpenFile(HWND hWnd,LPWSTR lpwFileName,unsigned int fileSize)
{
	//Initialize file name
	lpwFileName[0]=L'\0';

	OPENFILENAME ofn;
	memset(&ofn,0,sizeof(ofn));

	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner=hWnd;
	ofn.lpstrFilter=L"All image files.\0"
		L"*.bmp;*.dib;*.wdp;*.mdp;*.hdp;*.gif;*.png;*.jpg;*.jpeg;*.tif;*.ico\0"
		L"Windows Bitmap\0"               L"*.bmp;*.dib\0"
		L"High Definition Photo\0"        L"*.wdp;*.mdp;*.hdp\0"
		L"Graphics Interchange Format\0"  L"*.gif\0"
		L"Portable Network Graphics\0"    L"*.png\0"
		L"JPEG File Interchange Format\0" L"*.jpg;*.jpeg\0"
		L"Tiff File\0"                    L"*.tif\0"
		L"Icon\0"                         L"*.ico\0"
		L"All Files\0"                    L"*.*\0"
		L"\0";
	ofn.lpstrFile       = lpwFileName;
	ofn.nMaxFile        = fileSize;
	ofn.lpstrTitle      = L"Open File";
	ofn.Flags           = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	//Open file dialog
	return GetOpenFileNameW(&ofn);
}


HRESULT CAshaD2D::CreateD2DBitmapFromFile(HWND hWnd)
{
	HRESULT hr = S_OK;

	WCHAR szFileName[MAX_PATH];

	// Step 1: Create the open dialog box and locate the image file
	if (OpenFile(hWnd, szFileName, ARRAYSIZE(szFileName)))
	{
		// Step 2: Decode the source image

		// Create a decoder
		IWICBitmapDecoder *pDecoder = NULL;

		hr = m_pWICImgFactory->CreateDecoderFromFilename(
			szFileName,                      // Image to be decoded
			NULL,                            // Do not prefer a particular vendor
			GENERIC_READ,                    // Desired read access to the file
			WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
			&pDecoder                        // Pointer to the decoder
			);

		// Retrieve the first frame of the image from the decoder
		//IWICBitmapFrameDecode *pFrame = NULL;

		if (SUCCEEDED(hr))
		{
			SafeRelease(&m_pFrame);
			hr = pDecoder->GetFrame(0, &m_pFrame);
		}

		


		//SafeRelease(&pfmatCoverter);
		SafeRelease(&pDecoder);
		//SafeRelease(&pFrame);
	}

	return hr;
}



void CAshaD2D::DrawImg(float destX,float destY,float destWidth,float destHeight)
{
	HRESULT hr=S_OK;
	//Step 3: Format convert the frame to 32bppPBGRA
		IWICFormatConverter* pfmatCoverter=NULL;
		if (SUCCEEDED(hr))
		{
			SafeRelease(&pfmatCoverter);
			hr = m_pWICImgFactory->CreateFormatConverter(&pfmatCoverter);
		}

		if (SUCCEEDED(hr))
		{
			hr = pfmatCoverter->Initialize(
				m_pFrame,                          // Input bitmap to convert
				GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
				WICBitmapDitherTypeNone,         // Specified dither pattern
				NULL,                            // Specify a particular palette 
				0.f,                             // Alpha threshold
				WICBitmapPaletteTypeCustom       // Palette translation type
				);
		}
	//Step 4: Create render target and D2D bitmap from IWICBitmapSource
	// Need to release the previous D2DBitmap if there is one
	if(m_pD2DBitmap!=NULL)
		SafeRelease(&m_pD2DBitmap);
	hr=m_pHwndRenderTarget->CreateBitmapFromWicBitmap(pfmatCoverter, NULL, &m_pD2DBitmap);
	if(SUCCEEDED(hr))
	{
		SafeRelease(&pfmatCoverter);
		//SafeRelease(&m_pFrame);
		//Get image size and rect
		D2D_SIZE_F imgSize=m_pD2DBitmap->GetSize();
		D2D_RECT_F imgRc=D2D1::RectF(0.0f,0.0f,imgSize.width,imgSize.height);

		//
		D2D_RECT_F destRc=D2D1::RectF(0.0f,0.0f,0.0f,0.0f);
		if(destWidth<=destHeight)
			destRc=D2D1::RectF(destX,destY,destWidth-5.0f,destWidth*imgSize.height/imgSize.width-5.0f);
		else
			destRc=D2D1::RectF((destX+1.0f*(destWidth-destHeight*imgSize.width/imgSize.height)),destY,destHeight*imgSize.width/imgSize.height,destHeight-5.0f);

		m_pHwndRenderTarget->DrawBitmap(m_pD2DBitmap,&destRc,1.0f,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,&imgRc);
	}
}
