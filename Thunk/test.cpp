
/********************************************************

	��ѩ��̳������֮�������Ĵ���֮������Ʒ

	����Thunk������C���Իص�����תΪC++���
	Ա����

	���� : ��³��

	Ϊ���а��ҵ��˺��Ұ�����Ŭ��!

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
		// �ȴ������߳��˳�, Ȼ��������������,
		// ������Ϊ���������ڽ���, ���̻߳��ڷ���nCount, m_bExit

		m_bExit = true;
		WaitForMultipleObjects(2, m_Handles, TRUE, INFINITE);

		printf("destruction\n");

		CloseHandle(m_Handles[0]);
		CloseHandle(m_Handles[1]);
	}

	DWORD /* __thiscall */ ThreadProcA(LPVOID lpParameter)
	{
		// �ڴ��̺߳����п��Է���������ݳ�ԱnCount !
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
		// �ڴ��̺߳����п��Է���������ݳ�ԱnCount !
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
		// ���̺߳�����ַ��ʼ��pProc��, Ȼ����CreateThread
		// ע�����Լ��
		void* pProc = m_PorcA.Thiscall(this, Thunk::GetMemberFxnAddr(&T::ThreadProcA));
		m_Handles[0] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pProc, 0, 0, 0);
	}

	void testB()
	{
		// ���̺߳�����ַ��ʼ��pProc��, Ȼ����CreateThread
		// ע�����Լ��
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
	t.testA();    // ���Ժ���
	Sleep(200);   // ��Ϊû���߳�ͬ������, Ϊʹ�����߳̽������, ����...
	t.testB();    // ���Ժ���
	Sleep(10000); // �������߳��ʷֵ�ִ��ʱ��
}