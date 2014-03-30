//-------------------------------------------------------------------------------
//CAshaThunk.h
//Version 0.0
//Created at 2013-03-02,by Rohan
//Define thunk class for call back function use class nonstatic members
//Modified fome internet files,tks fro their help.
//--------------------------------------------------------------------------------

#ifndef _CASHATHUNK_H_
#define _CASHATHUNK_H_

#include <Windows.h>

class CAshaThunk
{
public:
	CAshaThunk(void);
	virtual ~CAshaThunk(void);

	//Get member function poiter
	void* MemberFuncCall(void* pThis, unsigned long MemberFuncAddr,int nCallStyle);  //Automic choose hoose _thiscall(1) or _stdcall(2)

private:
	void* Thiscall(void* pThis, unsigned long MemberFuncAddr);                      //_thiscall 调用约定
	void* Stdcall (void* pThis, unsigned long MemberFuncAddr);                      //_stdcall  调用约定

public:
	//Get fucntion address
	//method1: get pointer through union struct 
	template <typename T> 
	static unsigned long GetMemberFuncAddr(T MemberFuncName)
	{
		union 
		{
			T             From; 
			unsigned long To;
		}	union_cast;
		union_cast.From = MemberFuncName;
		return union_cast.To;
	}

	//method2: through ASM code
	/*To be improve
	unsigned long        GetMemberFuncAddrAsm(unsigned long MemberFuncName)
	{

		DWORD  dwFuncAddr=0;
		_asm
		{

			//MOV EAX, OFFSET MemberFuncName    //Get member funtion address
			//MOV DWORD PTR [dwFuncAddr],eax;   //Set to memory
		}

		return dwFuncAddr;
	}
	*/
private:

	#pragma pack (push, 1)
	
	typedef struct _BYTECODE_THISCALL
	{
		unsigned char Mov;     // 0xB9
		unsigned long This;    // this pointer
		unsigned char Jmp;     // 0xE9
		unsigned long Adrr;    // relative jmp
	}	BYTECODE_THISCALL, *PBYTECODE_THISCALL;

	typedef struct _BYTECODE_STDCALL
	{
		unsigned char Push[3]; // push dword ptr[esp] ;
		unsigned long Move;    // mov dword ptr [esp + 4], ?? ?? ?? ?? ;
		unsigned long This;    // this pointer
		unsigned char Jmp;     // 0xE9
		unsigned long Adrr;    // relative jmp
	}	BYTECODE_STDCALL, *PBYTECODE_STDCALL;

	#pragma pack (pop)

	// u1byte m_BytecodeThiscall[10];
	// u1byte m_BytecodeStdcall [16];

	BYTECODE_THISCALL m_BytecodeThiscall;
	BYTECODE_STDCALL  m_BytecodeStdcall;

	//CAshaThunck class object pointer
	CAshaThunk*       m_pThis;

};

#endif 
