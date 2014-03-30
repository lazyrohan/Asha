//-------------------------------------------------------------------------------
//CAshaD2D.h
//Version 0.0
//Created at 2013-03-06,by Rohan
//Define Asha D2D class for UI rendering engieen or other 2D drawing 
//--------------------------------------------------------------------------------

#ifndef _CASHAD2D_H_
#define _CASHAD2D_H_

//Inlude windows and D2D headers
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

//Link libs
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"windowscodecs.lib")

//Function to release pointers
template<class Interface>
inline void SafeRelease(
    Interface **ppInterfaceToRelease
    )
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}


//Assert to check vars for debug
#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

//Gloable definations

class CAshaD2D
{
public:
	CAshaD2D(void);
	virtual ~CAshaD2D(void);

private:
	//D2D base members------------------------------
	//Device indepent resource
	ID2D1Factory*                       m_pD2D1Facatory;
	IDWriteFactory*                     m_pDWriteFactory;
	IWICImagingFactory*                 m_pWICImgFactory;

	//Device dependent resourece
	//shape drawing for windows
	ID2D1HwndRenderTarget*              m_pHwndRenderTarget;

	//Text drawing
	IDWriteTextLayout*                  m_pCaptionTxtLayout;
	IDWriteTextLayout*                  m_pContentTxtLayout;

	//Image drawing
	ID2D1BitmapRenderTarget*            m_pImgRenderTarget;                  
	IWICBitmapFrameDecode*              m_pFrame;
	ID2D1Bitmap*                        m_pD2DBitmap;

public:
	HRESULT                             CreateFactory(void);    //Create D2D and dwrite device independent factory
	HRESULT                             BegainDraw(HWND hWnd);  //Create device dependent source and initialize 

	ID2D1HwndRenderTarget*              GetRenderTarget(void);
	void                                ReleaseDevice(void);

	//Function enclosure
	//Drawing 

	//Text
	//caption text
	HRESULT                            CreateCaptionTextLayout(WCHAR* pCaptionStr,FLOAT maxWidth,FLOAT maxHeight);//Create text layout
	void                               DrawCaptionText(float orgx,float orgy,ID2D1Brush* foregroundBrush);        //Draw caption text
	IDWriteTextLayout*                 GetCaptionTextLayout(void);                                                //Get caption text layout pointer
	//Content text
	HRESULT                            CreateContentTextLayout(WCHAR* pContentStr,FLOAT maxWidth,FLOAT maxHeight);//Create text layout
	void                               DrawContentText(float orgx,float orgy,ID2D1Brush* foregroundBrush);        //Draw caption text
	IDWriteTextLayout*                 GetContentTextLayout(void);                                                //Get content text layout pointer

	//Image
	//Open file dialog
	BOOL                               OpenFile(HWND hWnd,LPWSTR lpwFileName,unsigned int fileSize);                                                                 
	HRESULT                            CreateD2DBitmapFromFile(HWND hWnd);
	void                               DrawImg(float destX,float destY,float destWidth,float destHeight);
};

#endif
