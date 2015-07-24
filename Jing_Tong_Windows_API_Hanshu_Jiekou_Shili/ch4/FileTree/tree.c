/* ************************************
*����ͨWindows API�� 
* ʾ������
* tree.c
* 4.3.6	�ݹ����Ŀ¼��
* 2007��10��
**************************************/

/* ͷ�ļ���*/
#include <windows.h>
#include <stdio.h>

/* Ԥ�������� */
#pragma comment (lib, "User32.lib")

/* ����������*/
DWORD ListAllFileInDrectory(LPSTR szPath);

/* ȫ�ֱ�����*/
//��¼���е��ļ���Ŀ¼��
DWORD dwTotalFileNum = 0;


/* ************************************
* DWORD ListAllFileInDrectory(LPSTR szPath)
* ����	����Ŀ¼��������Ŀ¼����ӡ·��
*
* ����	LPTSTR szPath��Ϊ�������Ŀ¼
*
* ����ֵ	0����ִ����ɣ�1���뷢������
**************************************/
DWORD ListAllFileInDrectory(LPSTR szPath)
{
	CHAR szFilePath[MAX_PATH];

	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	CHAR szFullPath[MAX_PATH];

	//���������Ŀ¼���ļ���·�����ַ�����ʹ��ͨ�����*��
	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, "\\*");
	//���ҵ�һ���ļ�/Ŀ¼����ò��Ҿ��
	hListFile = FindFirstFile(szFilePath,&FindFileData);

	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("����%d",GetLastError());
		return 1;
	}
	else
	{		
		do
		{
			//	���ˡ�.���͡�..��������Ҫ����
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0||
				lstrcmp(FindFileData.cFileName,TEXT(".."))==0)
			{
				continue;
			}
			//�����ȫ·��
			wsprintf(szFullPath,"%s\\%s",
				szPath,FindFileData.cFileName);
			dwTotalFileNum++;
			//��ӡ
			printf("\n%d\t%s\t",dwTotalFileNum,szFullPath);

			//�����Ŀ¼����ݹ���ã��о��¼�Ŀ¼
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			{
				printf("<DIR>");
				ListAllFileInDrectory(szFullPath);
			}			
		}
		while(FindNextFile(hListFile, &FindFileData));
	}
	return 0;
}


/* ************************************
* int main(int argc, PCHAR argv[])
* ����	����ListAllFileInDrectory
*		����Ŀ¼�µ��ļ�����Ŀ¼
*
* ����	argv[1]Ϊ�������·�������Ϊ�����ȡ
*		��ǰ·��
*
* 2007��10��
*
**************************************/
int main(int argc, PCHAR argv[])
{	
	if(argc == 2)
	{
		ListAllFileInDrectory(argv[1]);
	}
	else 
	{
		CHAR szCurrentPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,szCurrentPath);
		ListAllFileInDrectory(szCurrentPath);
	}
	return 0;
}