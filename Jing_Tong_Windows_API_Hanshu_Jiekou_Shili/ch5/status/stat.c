/* ************************************
*����ͨWindows API�� 
* ʾ������
* stat.c
* 5.5.2  ��õ�ǰϵͳ�ڴ�ʹ�����
**************************************/

/* ͷ�ļ���*/
#include <windows.h>
#include <stdio.h>

/*************************************
* int main(void)
* ����	��ȡ�ڴ�ʹ�����
*
* ����	δʹ��
**************************************/
int main(void)
{	
	//���ڱ�����Ϣ
	MEMORYSTATUSEX memstatusex;
	//���ýṹ��С
	memstatusex.dwLength = sizeof(memstatusex);
	//��ȡϵͳ�ڴ�ʹ�����
	GlobalMemoryStatusEx(&memstatusex);
	//��ӡ������
	printf("TotalPhys\tAvailPhys\tTotalVirtual\tAvailVirtual\t"
		"TotalPageFile\tuAvailPageFile\tMemoryLoad\n"
		"%I64u\t%I64u\t%I64u\t%I64u\t%I64u\t%I64u\t%u%%",
		memstatusex.ullTotalPhys,memstatusex.ullAvailPhys,
		memstatusex.ullTotalVirtual,memstatusex.ullAvailVirtual,
		memstatusex.ullTotalPageFile,memstatusex.ullAvailPageFile,
		memstatusex.dwMemoryLoad);
	return 0;
}