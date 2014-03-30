// AshaWnd.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AshaWnd.h"
#include "CAshaWnd.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	CAshaWnd newWnd;
	newWnd.CreateWnd(hInstance,NULL);
	newWnd.ShowWnd(nCmdShow);

	MSG msg;
	HACCEL hAccelTable;	

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASHAWND));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


