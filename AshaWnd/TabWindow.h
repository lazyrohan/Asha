
/************************************************************************
 *
 * File: TabWindow.h
 ************************************************************************/

#pragma once


#include <Windows.h>
#include <commctrl.h>

#ifndef HINST_THISCOMPONENT 
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

/*
#include "SimpleText.h"
#include "MultiformattedText.h"
#include "CustomText.h"
*/

/******************************************************************
*                                                                 *
*  TabWindow                                                      *
*                                                                 *
******************************************************************/

class TabWindow
{
public:
    TabWindow();
    ~TabWindow();

private:
    HWND hwnd_;              //�����ھ��
    HWND hwndTab_;           //tab�ؼ����ھ��
    HWND hwndChild_;         //�Ӵ��ھ��

public:

    HRESULT Initialize();    //��ʼ������
    HWND GetHwnd(){ return hwnd_; }  //��ȡ�����ھ��

private:

    HWND CreateTabControl();               //�����ؼ�
    HRESULT CreateChildWindows();          //�����Ӵ���

    HRESULT OnPaint(const PAINTSTRUCT &ps); //���ƺ���

    void OnResize(
                   UINT width,
                   UINT height
                 );

    static LRESULT CALLBACK WndProc(
                                     HWND hWnd,
                                     UINT message,
                                     WPARAM wParam,
                                     LPARAM lParam
                                    );

	/*
    SimpleText simpleText_;
    MultiformattedText multiformattedText_;
    CustomText customText_;
	*/
};

