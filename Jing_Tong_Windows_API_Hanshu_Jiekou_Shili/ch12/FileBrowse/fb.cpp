/* ************************************
*����ͨWindows API�� 
* ʾ������
* fb.c
* 12.1.4  ����ļ��жԻ���
**************************************/
/* ͷ�ļ���*/
#include <Windows.h>
#include <shlobj.h>
/* ����������*/
DWORD Browse(HWND hwnd) ;

/*************************************
* WinMain
* ����	������ڵ㣬����Browse
*
* ����	δʹ��
**************************************/
int WINAPI WinMain(
				   HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow
				   )
{
	Browse(NULL); 
}

/*************************************
* WinMain
* ����	����������ļ��С��Ի���
����ȡ�û�ѡ����ļ���Ŀ¼
*
* ����	HWND hwnd	�����ھ��
**************************************/
DWORD Browse(HWND hwnd) 
{
	// ���ڱ���·��
	CHAR szRoot[MAX_PATH];
	CHAR szChoose[MAX_PATH];
	CHAR szDisplayName[MAX_PATH];
	// ��ر���
	LPITEMIDLIST pidlRoot = NULL;
	LPITEMIDLIST pidlSelected = NULL;
	BROWSEINFO bi = {0};
	LPMALLOC pMalloc = NULL;

	// ������ļ��С��ĸ�·����������Ա�ɸ������ѡ�񣬱���ֻ������ҵ��ĵ�����
	SHGetFolderLocation(NULL, CSIDL_DESKTOP, NULL, 0, &pidlRoot);
	SHGetPathFromIDList(pidlRoot,szRoot);
	// ��� BROWSEINFO �ṹ
	bi.hwndOwner = hwnd;
	bi.pidlRoot = pidlRoot;
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = "Choose a target";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	// �����Ի���
	pidlSelected = SHBrowseForFolder(&bi);
	// DisplayName
	MessageBox(NULL,szDisplayName,"Display Name:",MB_OK);
	// ѡ����ļ���
	SHGetPathFromIDList( pidlSelected, szChoose );
	MessageBox(NULL,szChoose,"Choose:",MB_OK);
	// �ͷ�
	ILFree(pidlRoot);
	return 0;
}