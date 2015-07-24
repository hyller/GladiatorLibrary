/* ************************************
*����ͨWindows API�� 
* ʾ������
* Event.c
* 7.2.1  ��ʾʹ��Eventͬ���߳�
**************************************/

/* ͷ�ļ���*/
#include <windows.h>
#include <stdio.h>
/* �������塡*/
#define NUMTHREADS	3 
#define BUFFER_SIZE	16
#define FOR_TIMES	5
/* ȫ�ֱ�����*/
HANDLE hEvent;					// ����ͬ��
BYTE lpSharedBuffer[16] = {0};	// �����ڴ�
/* ����������*/
void UseEvents(void);
DWORD WINAPI EventFunction(LPVOID lpParam);

/*************************************
* int main(void)
* ����	��ʾ
*
* ����	δʹ��
**************************************/
int main()
{
	UseEvents();
}

/*************************************
* void UseEvents(void) 
* ����	��ʾEvent��ʹ�÷���
*
* ����	δʹ��
**************************************/
void UseEvents(void) 
{
	HANDLE hThread; 

	hEvent = CreateEvent( 
		NULL,			// Ĭ�ϰ�ȫ����
		TRUE,			// �ֹ�����
		FALSE,			// ��ʼΪδ��λ��
		NULL			// δ����
		);
	// �ж��Ƿ񴴽��ɹ�
	if (hEvent == NULL) 
	{ 
		printf("CreateEvent failed (%d)\n", GetLastError());
		return;
	}
	// �����߳�
	hThread = CreateThread(NULL, 0, 
		EventFunction, 
		NULL,
		0, NULL); 
	if (hThread == NULL) 
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return;
	}	
	Sleep(2000); // ������һЩ��������
	// �����ڴ��и�������
	CopyMemory(lpSharedBuffer,"Event",lstrlen("Event"));
	// ���� Event ʹThreadFunction�߳̿��Կ�ʼ��������
	SetEvent(hEvent);
}

/*************************************
* DWORD WINAPI EventFunction(LPVOID lpParam)
* ����	�̺߳������������ڴ�
*
* ����	δʹ��
**************************************/
DWORD WINAPI EventFunction(LPVOID lpParam) 
{
	DWORD dwWaitResult;
	// �ȴ���ֱ���¼�����λ
	dwWaitResult = WaitForSingleObject( 
		hEvent,			// Event ���
		INFINITE);		// ���޵ȴ�
	if (dwWaitResult != WAIT_OBJECT_0) 
	{
		printf("Wait error: %d\n", GetLastError()); 
		return 0;
	}
	// �������ڴ�
	printf(lpSharedBuffer);
	// �����¼�
	if (! ResetEvent(hEvent) ) 
	{ 
		printf("SetEvent failed (%d)\n", GetLastError());
		return 0;
	}
	return 1;
}