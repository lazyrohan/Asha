
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
    HWND hwnd_;              //主窗口句柄
    HWND hwndTab_;           //tab控件窗口句柄
    HWND hwndChild_;         //子窗口句柄

public:

    HRESULT Initialize();    //初始化函数
    HWND GetHwnd(){ return hwnd_; }  //获取主窗口句柄

private:

    HWND CreateTabControl();               //创建控件
    HRESULT CreateChildWindows();          //创建子窗口

    HRESULT OnPaint(const PAINTSTRUCT &ps); //绘制函数

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

