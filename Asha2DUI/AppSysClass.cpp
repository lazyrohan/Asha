//AppSysClas.cpp

#include "AppSysClass.h"

AppSysClass::AppSysClass():	
	m_hInstance(NULL),
	m_hWnd(NULL),
	m_msg(NULL)
{
	//Initialize gloable variations
	
	
}

AppSysClass::~AppSysClass()
{

}
bool AppSysClass::Initialize(HINSTANCE hInstance,int nCmdShow,LPCSTR AppName,HCURSOR hCursor,HICON hIcon,RECT rc)
{
	bool hr=true;
	//Initialize windows
	m_AppName=AppName;
	m_hCursor=hCursor;
	m_hIcon=hIcon;
	m_rc=rc;
	hr=InitializeWindows(hInstance,nCmdShow);
	if(!hr)
	{
		return false;
	}

	return hr;
}
bool AppSysClass::InitializeWindows(HINSTANCE hInstance,int nCmdShow)
{
	//Initialize wnd class structure
	WNDCLASSEX wcex;
	wcex.cbSize=sizeof(WNDCLASSEX);
	wcex.style=CS_HREDRAW|CS_VREDRAW;
	wcex.lpfnWndProc=WndProc;
	wcex.cbClsExtra=NULL;
	wcex.cbWndExtra=NULL;
	wcex.hInstance=m_hInstance=hInstance;
	wcex.hIcon=m_hIcon;
	wcex.hCursor=m_hCursor;
	wcex.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName=NULL;
	wcex.lpszClassName=m_AppName;
	wcex.hIconSm=NULL;

	//Regist wnd class
	if(!RegisterClassEx(&wcex))
		return false;

	//Create window
	AdjustWindowRect(&m_rc,WS_OVERLAPPEDWINDOW,false);
	m_hWnd=CreateWindow(m_AppName,m_AppName,WS_TILEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,m_rc.right-m_rc.left,
		              m_rc.bottom-m_rc.top,NULL,NULL,hInstance,NULL);
	if(!m_hWnd)
		return false;

	//show window
	ShowWindow(m_hWnd,nCmdShow);

	return true;
}


void AppSysClass::Run()
{
	bool done=true;
	//Main message loop
	m_msg=new MSG;
	while(done)
	{
	  if(PeekMessageA(m_msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(m_msg);
			DispatchMessage(m_msg);
		}

	  if(m_msg->message==WM_QUIT)
		  done=false;
	  else
	  {
		  done=true;
	  }

	}

	return;
}

int AppSysClass::Exit()
{
	//Destroy window
	DestroyWindow(m_hWnd);
	return ( int )m_msg->wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch(message)
	{
	case WM_PAINT:
		{
			hdc=BeginPaint(hWnd,&ps);
			EndPaint(hWnd,&ps);
			break;
		}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}

	return 0;
}