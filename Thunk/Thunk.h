
/********************************************************************

Copyright 2006-2008 ZHANG Luduo. All Rights Reserved.

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation.

********************************************************************/

/*

�������� : 

	Thunk : ��һ�λ������Ӧ���ֽڱ�����һ�������ڴ�ṹ��, 
	Ȼ����ָ��ǿ��ת���ɺ���. ������������ִ��.
	
	��ݴ������ڽ�C�﷽�Ļص�����ת��Ϊ����thisָ���C++��
	Ա����.

	��Windowsϵͳ�����, ���Խ�һЩϵͳ�غ�����װ��C++���
	Ա����, ����

	// ��ʱ���ص�����
	VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, 
	UINT_PTR idEvent, DWORD dwTime);

	// �̻߳ص�����
	DWORD WINAPI ThreadProc(LPVOID lpParameter);

	// ���ڹ��̻ص�����
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, 
	WPARAM wParam, LPARAM lParam);

	2008-10-22��������Windows XP SP2, Windows server 2003��
	���¿���DEP���ܺ����б�����BUG

��������:

	����  - ��³��, ZHANG Luduo
	MSN   - zhangluduo@msn.com
	Email - zhangluduo@163.com
	QQȺ  - 34064264, 56918155, 56918241
	��վ  - http://www.oopfans.com

	Ϊ���а��ҵ��˺��Ұ�����Ŭ��!

*/

#ifndef _THUNK_H
#define _THUNK_H

// type redefinition
typedef unsigned char  u1byte; // an 8 bit unsigned character type
typedef unsigned short u2byte; // a 16 bit unsigned integer type
typedef unsigned long  u4byte; // a 32 bit unsigned integer type
typedef void*          pvoid;  // a 32 bit undefined type pointer

class Thunk
{
public:

	Thunk();
	/*virtual*/ ~Thunk();

	pvoid Thiscall(pvoid pThis, u4byte MemberFxnAddr);
	pvoid Stdcall (pvoid pThis, u4byte MemberFxnAddr);

	template <typename T> 
	static u4byte GetMemberFxnAddr(T MemberFxnName)
	{
		union 
		{
			T From; 
			u4byte To;
		}	union_cast;
		union_cast.From = MemberFxnName;
		return union_cast.To;
	}

private:

	#pragma pack (push, 1)
	
	typedef struct _BYTECODE_THISCALL
	{
		u1byte Mov;     // 0xB9
		u4byte This;    // this pointer
		u1byte Jmp;     // 0xE9
		u4byte Adrr;    // relative jmp
	}	BYTECODE_THISCALL, *PBYTECODE_THISCALL;

	typedef struct _BYTECODE_STDCALL
	{
		u1byte Push[3]; // push dword ptr[esp] ;
		u4byte Move;    // mov dword ptr [esp + 4], ?? ?? ?? ?? ;
		u4byte This;    // this pointer
		u1byte Jmp;     // 0xE9
		u4byte Adrr;    // relative jmp
	}	BYTECODE_STDCALL, *PBYTECODE_STDCALL;

	#pragma pack (pop)

	// u1byte m_BytecodeThiscall[10];
	// u1byte m_BytecodeStdcall [16];

	BYTECODE_THISCALL m_BytecodeThiscall;
	BYTECODE_STDCALL  m_BytecodeStdcall;

	Thunk* m_pThis;
};

#endif // #define _THUNK_H
