/* ************************************
*����ͨWindows API�� 
* ʾ������
* file_map.c
* 4.4.1  ʹ��Mapping File����ļ���д��Ч��
**************************************/

/* ͷ�ļ���*/
#include <windows.h>
#include <stdio.h>
/* Ԥ����������*/
#define BUFFSIZE 1024					// �ڴ��С
#define FILE_MAP_START 0x28804			// �ļ�ӳ�����ʼ��λ��
/* ȫ�ֱ�����*/
LPTSTR lpcTheFile = TEXT("test.dat");	// �ļ���

/* ************************************
* int main(void)
* ����	��ʾʹ���ļ�mapping
*
* ����	��
*
* ����ֵ	0����ִ����ɣ�1������������
**************************************/
int main(void)
{
	HANDLE hMapFile;      // �ļ��ڴ�ӳ������ľ��
	HANDLE hFile;         // �ļ��ľ��
	DWORD dBytesWritten;  // д����ֽ���
	DWORD dwFileSize;     // �ļ���С
	DWORD dwFileMapSize;  // �ļ�ӳ��Ĵ�С
	DWORD dwMapViewSize;  // ��ͼ��View���Ĵ�С
	DWORD dwFileMapStart; // �ļ�ӳ����ͼ����ʼλ��
	DWORD dwSysGran;      // ϵͳ�ڴ���������
	SYSTEM_INFO SysInfo;  // ϵͳ��Ϣ
	LPVOID lpMapAddress;  // ����ӳ���������ʼλ��
	PCHAR pData;			// ����
	INT i;                // ѭ������
	INT iData;
	INT iViewDelta;
	BYTE cMapBuffer[32];  // �洢��mapping�мƳ�������

	// ����һ���ļ�
	hFile = CreateFile(lpcTheFile, 
		GENERIC_READ | GENERIC_WRITE,
		0, 
		NULL,
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	//�ж��ļ��Ƿ񴴽��ɹ�
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile error\n",GetLastError);
		return 1;
	}
	// ����д��������һ��д��65535������
	// ��32λƽ̨�£���СΪ65535*32
	for (i=0; i<65535; i++) 
	{
		WriteFile (hFile, &i, sizeof (i), &dBytesWritten, NULL);
	}
	// �鿴д����ɺ���ļ���С
	dwFileSize = GetFileSize(hFile,  NULL);
	printf("�ļ���С: %d\n", dwFileSize);

	//��ȡϵͳ��Ϣ���ڴ��������
	//��ȡ�������ȣ���������ļ������㣬
	//Ŀ����Ϊ��ӳ���������ϵͳ�ڴ�������ȶ��룬����ڴ����Ч��
	GetSystemInfo(&SysInfo);
	dwSysGran = SysInfo.dwAllocationGranularity;

	//����mapping����ʼλ��
	dwFileMapStart = (FILE_MAP_START / dwSysGran) * dwSysGran;
	// ����mapping view�Ĵ�С
	dwMapViewSize = (FILE_MAP_START % dwSysGran) + BUFFSIZE;
	// ����mapping�Ĵ�С
	dwFileMapSize = FILE_MAP_START + BUFFSIZE;
	// ������Ҫ��ȡ�����ݵ�ƫ��
	iViewDelta = FILE_MAP_START - dwFileMapStart;

	// ����File mapping
	hMapFile = CreateFileMapping( hFile,          // ��Ҫӳ����ļ��ľ��
		NULL,           // ��ȫѡ�Ĭ��
		PAGE_READWRITE, // �ɶ�����д
		0,              // mapping����Ĵ�С����λ
		dwFileMapSize,  // mapping����Ĵ�С����λ
		NULL);          // mapping���������
	if (hMapFile == NULL) 
	{
		printf("CreateFileMapping error: %d\n", GetLastError() );
		return 1;
	}

	// ӳ��view
	lpMapAddress = MapViewOfFile(hMapFile,            // mapping����ľ��
		FILE_MAP_ALL_ACCESS, // �ɶ�����д
		0,                   // ӳ����ļ�ƫ�ƣ���32λ
		dwFileMapStart,      // ӳ����ļ�ƫ�ƣ���32λ
		dwMapViewSize);      // ӳ�䵽View�����ݴ�С
	if (lpMapAddress == NULL) 
	{
		printf("MapViewOfFile error: %d\n", GetLastError());
		return 1;
	}

	printf ("�ļ�map view������ļ�����ʼλ�ã� 0x%x\n",
		dwFileMapStart);
	printf ("�ļ�map view�Ĵ�С��0x%x\n", 	dwMapViewSize);
	printf ("�ļ�mapping����Ĵ�С��0x%x\n", dwFileMapSize);
	printf ("�������map view 0x%x �ֽڵ�λ�ö�ȡ���ݣ�", iViewDelta);

	// ��ָ�����ݵ�ָ��ƫ�ƣ��������ǹ��ĵĵط�
	pData = (PCHAR) lpMapAddress + iViewDelta;
	// ��ȡ���ݣ���ֵ������
	iData = *(PINT)pData;
	// ��ʾ��ȡ������
	printf ("Ϊ��0x%.8x\n", iData);

	// ��mapping�и������ݣ�32���ֽڣ�����ӡ
	CopyMemory(cMapBuffer,lpMapAddress,32);
	printf("lpMapAddress��ʼ��32�ֽ��ǣ�");
	for(i=0; i<32; i++)
	{
		printf("0x%.2x ",cMapBuffer[i]);
	}
	// ��mapping��ǰ32���ֽ���0xff���
	FillMemory(lpMapAddress,32,(BYTE)0xff);
	// ��ӳ�������д�ص�Ӳ����
	FlushViewOfFile(lpMapAddress,dwMapViewSize);
	printf("\n�Ѿ���lpMapAddress��ʼ��32�ֽ�ʹ��0xff��䡣\n");

	// �ر�mapping����
	if(!CloseHandle(hMapFile)) 
	{
		printf("\nclosing the mapping object error %d!",
			GetLastError());
	}
	//�ر��ļ�
	if(!CloseHandle(hFile)) 
	{
		printf("\nError %ld occurred closing the file!",
			GetLastError());
	}

	return 0;
}