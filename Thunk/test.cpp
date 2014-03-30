
/********************************************************

	看雪论坛【代码之美】征文大赛之参赛作品

	利用Thunk技术将C语言回调函数转为C++类成
	员函数

	作者 : 张鲁夺

	为所有爱我的人和我爱的人努力!

********************************************************/

#include <windows.h>
#include <stdio.h>
#include "Thunk.h"

class T
{
public:

	T() : nCount(10), m_bExit(false) { }

	~T()
	{
		// 等待所有线程退出, 然后再做析构操作,
		// 以免因为类生命周期结束, 而线程还在访问nCount, m_bExit

		m_bExit = true;
		WaitForMultipleObjects(2, m_Handles, TRUE, INFINITE);

		printf("destruction\n");

		CloseHandle(m_Handles[0]);
		CloseHandle(m_Handles[1]);
	}

	DWORD /* __thiscall */ ThreadProcA(LPVOID lpParameter)
	{
		// 在此线程函数中可以访问类的数据成员nCount !
		while(nCount >= 0)
		{
			if(m_bExit)
				break;
			printf("thiscall\t%d\n", nCount);
			nCount--;
			Sleep(1000);
		}
		printf("ThreadA exit\n");
		return 0;
	}

	DWORD __stdcall ThreadProcB(LPVOID lpParameter)
	{
		// 在此线程函数中可以访问类的数据成员nCount !
		while(nCount >= 0)
		{
			if(m_bExit)
				break;
			printf("stdcall\t\t%d\n", nCount);
			nCount--;
			Sleep(1000);
		}
		printf("ThreadB exit\n");
		return 0;
	}

	void testA()
	{
		// 将线程函数地址初始到pProc中, 然后赋与CreateThread
		// 注意调用约定
		void* pProc = m_PorcA.Thiscall(this, Thunk::GetMemberFxnAddr(&T::ThreadProcA));
		m_Handles[0] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pProc, 0, 0, 0);
	}

	void testB()
	{
		// 将线程函数地址初始到pProc中, 然后赋与CreateThread
		// 注意调用约定
		void* pProc = m_PorcB.Stdcall(this, Thunk::GetMemberFxnAddr(&T::ThreadProcB));
		m_Handles[1] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pProc, 0, 0, 0);
	}

private:

	int nCount;
	bool m_bExit;
	HANDLE m_Handles[2];
	Thunk m_PorcA;
	Thunk m_PorcB;
};

void main()
{
	T t;
	t.testA();    // 测试函数
	Sleep(200);   // 因为没有线程同步操作, 为使两个线程交替输出, 所以...
	t.testB();    // 测试函数
	Sleep(10000); // 给给予线程允分的执行时间
}