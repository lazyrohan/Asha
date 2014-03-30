//AppSysClass.h
//Define windows initialize class
#pragma once

#ifndef _APPCLASS_H_
#define _APPCLASS_H_

//Pre-processing instruction
#define WIN32_LEAN_AND_MEAN

//Include header files
#include <Windows.h>


class AppSysClass
{
public:
	AppSysClass();
	~AppSysClass();

	//Initialize windows parameters
	bool Initialize(HINSTANCE hInstance,int nCmdShow,LPCSTR AppName,HCURSOR hCursor,HICON hIcon,RECT rc);
	void Run();
	int Exit();

private:
	bool InitializeWindows(HINSTANCE hInstance,int nCmdShow);

private:
	LPCSTR             m_AppName;
	HCURSOR            m_hCursor;
	HICON              m_hIcon;
	RECT               m_rc;//Set start screen		
	HINSTANCE          m_hInstance;
	HWND               m_hWnd;
	MSG*               m_msg;
};

static LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

#endif