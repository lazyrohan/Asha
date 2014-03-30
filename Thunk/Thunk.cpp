
/********************************************************************

Copyright 2006-2008 ZHANG Luduo. All Rights Reserved.

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation.

********************************************************************/

/*

代码描述 : 

	Thunk : 将一段机器码对应的字节保存在一个连续内存结构里, 
	然后将其指针强制转换成函数. 即用作函数来执行.
	
	这份代码用于将C语方的回调函数转换为具有this指针的C++成
	员函数.

	在Windows系统编程中, 可以将一些系统回函数封装成C++类成
	员函数, 例如

	// 定时器回调函数
	VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, 
	UINT_PTR idEvent, DWORD dwTime);

	// 线程回调函数
	DWORD WINAPI ThreadProc(LPVOID lpParameter);

	// 窗口过程回调函数
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, 
	WPARAM wParam, LPARAM lParam);

	2008-10-22修正了在Windows XP SP2, Windows server 2003环
	境下开启DEP功能后运行崩溃的BUG

关于作者:

	姓名  - 张鲁夺, ZHANG Luduo
	MSN   - zhangluduo@msn.com
	Email - zhangluduo@163.com
	QQ群  - 34064264, 56918155, 56918241
	网站  - http://www.oopfans.com

	为所有爱我的人和我爱的人努力!

*/

//#include "StdAfx.h"
#include "Thunk.h"
#include <windows.h>

Thunk::Thunk()
{
	m_pThis = (Thunk*)VirtualAlloc(NULL, sizeof (Thunk), 
		MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

Thunk::~Thunk()
{
	if (NULL == m_pThis)
		return;
	VirtualFree(m_pThis, 0, MEM_RELEASE);
}

pvoid Thunk::Thiscall(pvoid pThis, u4byte MemberFxnAddr)
{
	/**
	encoded machine instruction   equivalent assembly languate notation
	---------------------------   -------------------------------------
	B9 ?? ?? ?? ??                mov ecx, pThis  ; load ecx with this pointer
	E9 ?? ?? ?? ??                jmp target addr ; jump to target function
	*/

	/**
	#define GETBYTE(b, n) ((u1byte)(b >> ((n - 1) * 8) & 0x000000FF))

	u4byte dwJmpAdr = MemberFxnAddr - 
		(u4byte)(&(m_pThis->m_BytecodeThiscall)) - 
		sizeof (m_pThis->m_BytecodeThiscall);

	m_pThis->m_BytecodeThiscall[0] = 0xB9;
	m_pThis->m_BytecodeThiscall[1] = GETBYTE((u4byte)pThis, 1);
	m_pThis->m_BytecodeThiscall[2] = GETBYTE((u4byte)pThis, 2);
	m_pThis->m_BytecodeThiscall[3] = GETBYTE((u4byte)pThis, 3);
	m_pThis->m_BytecodeThiscall[4] = GETBYTE((u4byte)pThis, 4);
	m_pThis->m_BytecodeThiscall[5] = 0xE9;
	m_pThis->m_BytecodeThiscall[6] = GETBYTE((u4byte)dwJmpAdr, 1);
	m_pThis->m_BytecodeThiscall[7] = GETBYTE((u4byte)dwJmpAdr, 2);
	m_pThis->m_BytecodeThiscall[8] = GETBYTE((u4byte)dwJmpAdr, 3);
	m_pThis->m_BytecodeThiscall[9] = GETBYTE((u4byte)dwJmpAdr, 4);

	FlushInstructionCache(GetCurrentProcess(), 
		&(m_pThis->m_BytecodeThiscall), 
		sizeof (m_BytecodeThiscall));

	return &(m_pThis->m_BytecodeThiscall);
	*/

	m_pThis->m_BytecodeThiscall.Mov  = 0xB9;
	m_pThis->m_BytecodeThiscall.This = (u4byte)pThis;
	m_pThis->m_BytecodeThiscall.Jmp  = 0xE9;
	m_pThis->m_BytecodeThiscall.Adrr = MemberFxnAddr - 
		(u4byte)(&(m_pThis->m_BytecodeThiscall)) - 
		sizeof (BYTECODE_THISCALL);

	FlushInstructionCache(GetCurrentProcess(), 
		&(m_pThis->m_BytecodeThiscall), 
		sizeof (BYTECODE_THISCALL));

	return &(m_pThis->m_BytecodeThiscall);
}

pvoid Thunk::Stdcall (pvoid pThis, u4byte MemberFxnAddr)
{
	/**
	encoded machine instruction   equivalent assembly languate notation
	---------------------------   -------------------------------------
	FF 34 24                      push dword ptr [esp]          ; save (or duplicate)
																; the return Address into stack
	C7 44 24 04 ?? ?? ?? ??       mov  dword ptr [esp+4], pThis ; overwite the old
																; return address with 'this pointer'
	E9 ?? ?? ?? ??                jmp  target addr              ; jump to target function
	*/

	/**
	#define GETBYTE(b, n) ((u1byte)(b >> ((n - 1) * 8) & 0x000000FF))

	u4byte dwJmpAdr = MemberFxnAddr - 
		(u4byte)(&(m_pThis->m_BytecodeStdcall)) - 
		sizeof (m_pThis->m_BytecodeStdcall);

	m_pThis->m_BytecodeStdcall[ 0] = 0xFF;
	m_pThis->m_BytecodeStdcall[ 1] = 0x34;
	m_pThis->m_BytecodeStdcall[ 2] = 0x24;
	m_pThis->m_BytecodeStdcall[ 3] = 0xC7;
	m_pThis->m_BytecodeStdcall[ 4] = 0x44;
	m_pThis->m_BytecodeStdcall[ 5] = 0x24;
	m_pThis->m_BytecodeStdcall[ 6] = 0x04;
	m_pThis->m_BytecodeStdcall[ 7] = GETBYTE((u4byte)pThis, 1);
	m_pThis->m_BytecodeStdcall[ 8] = GETBYTE((u4byte)pThis, 2);
	m_pThis->m_BytecodeStdcall[ 9] = GETBYTE((u4byte)pThis, 3);
	m_pThis->m_BytecodeStdcall[10] = GETBYTE((u4byte)pThis, 4);
	m_pThis->m_BytecodeStdcall[11] = 0xE9;
	m_pThis->m_BytecodeStdcall[12] = GETBYTE((u4byte)dwJmpAdr, 1);
	m_pThis->m_BytecodeStdcall[13] = GETBYTE((u4byte)dwJmpAdr, 2);
	m_pThis->m_BytecodeStdcall[14] = GETBYTE((u4byte)dwJmpAdr, 3);
	m_pThis->m_BytecodeStdcall[15] = GETBYTE((u4byte)dwJmpAdr, 4);

	FlushInstructionCache(GetCurrentProcess(), 
		&(m_pThis->m_BytecodeStdcall), 
		sizeof (m_BytecodeStdcall));

	return &(m_pThis->m_BytecodeStdcall);
	*/

	m_pThis->m_BytecodeStdcall.Push[0] = 0xFF;
	m_pThis->m_BytecodeStdcall.Push[1] = 0x34;
	m_pThis->m_BytecodeStdcall.Push[2] = 0x24;
	m_pThis->m_BytecodeStdcall.Move    = 0x042444C7;
	m_pThis->m_BytecodeStdcall.This    = (u4byte)pThis;
	m_pThis->m_BytecodeStdcall.Jmp     = 0xE9;
	m_pThis->m_BytecodeStdcall.Adrr    = MemberFxnAddr - 
		(u4byte)(&(m_pThis->m_BytecodeStdcall)) - 
		sizeof (BYTECODE_STDCALL);
	
	FlushInstructionCache(GetCurrentProcess(), 
		&(m_pThis->m_BytecodeStdcall), 
		sizeof (BYTECODE_STDCALL));

	return &(m_pThis->m_BytecodeStdcall);
}
