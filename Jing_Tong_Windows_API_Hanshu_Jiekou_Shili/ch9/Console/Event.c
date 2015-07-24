/* ************************************
*����ͨWindows API�� 
* ʾ������
* Event.c
* 9.2  �ַ��������
**************************************/
/* ͷ�ļ� */
#include <windows.h>
/* �������� */
VOID KeyEventProc(KEY_EVENT_RECORD); 
VOID MouseEventProc(MOUSE_EVENT_RECORD); 
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD); 

/* ************************************
* DWORD UseEvent(VOID) 
* ����	ʹ���¼����п���̨����
**************************************/
DWORD UseEvent(VOID) 
{ 
	CHAR chBuffer[256]; 
	DWORD cRead;
	HANDLE hStdin; 
	DWORD cNumRead, fdwMode, fdwSaveOldMode, i; 
	INPUT_RECORD irInBuf[128]; 

	// ��ȡ��׼������
	hStdin = GetStdHandle(STD_INPUT_HANDLE); 
	if (hStdin == INVALID_HANDLE_VALUE) 
		MyErrorExit("GetStdHandle"); 

	// ���浱ǰ�Ŀ���̨ģʽ
	if (! GetConsoleMode(hStdin, &fdwSaveOldMode) ) 
		MyErrorExit("GetConsoleMode"); 

	// ʹ�ܴ�����������¼�
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; 
	if (! SetConsoleMode(hStdin, fdwMode) ) 
		MyErrorExit("SetConsoleMode"); 

	// ѭ����ȡ����
	while (1) 
	{ 

		// �ȴ��¼�
		if (! ReadConsoleInput( 
			hStdin,      // ������
			irInBuf,     // ��������Ļ����� 
			128,         // ��������С 
			&cNumRead) ) // ʵ�ʶ�ȡ�Ĵ�С 
			MyErrorExit("ReadConsoleInput"); 

		// ��ʾ�¼�
		for (i = 0; i < cNumRead; i++) 
		{
			switch(irInBuf[i].EventType) 
			{ 
			case KEY_EVENT: // ��������
				KeyEventProc(irInBuf[i].Event.KeyEvent); 
				break; 

			case MOUSE_EVENT: // �������
				MouseEventProc(irInBuf[i].Event.MouseEvent); 
				break; 

			case WINDOW_BUFFER_SIZE_EVENT: // Resize
				ResizeEventProc( 
					irInBuf[i].Event.WindowBufferSizeEvent); 
				break; 

			case FOCUS_EVENT:  // focus �¼� 

			case MENU_EVENT:   // menu �¼� 
				break; 

			default: 
				MyErrorExit("unknown event type"); 
				break; 
			} 
		}
	} 
	return 0; 
}

/* ************************************
* VOID KeyEventProc(KEY_EVENT_RECORD ker)
* ����	ʹ�öԻ�����ʾ���������¼�
* ����	KEY_EVENT_RECORD ker  �����¼�
**************************************/
VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	CHAR szMsg[256];
	wsprintf(szMsg,"KEY_EVENT_RECORD\n Char = %c",
		ker.uChar);
	MessageBox(NULL,szMsg,"EVENT",MB_OK);
}

/* ************************************
* VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
* ����	ʹ�öԻ�����ʾ����¼�
* ����	MOUSE_EVENT_RECORD mer ����¼�
**************************************/
VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
	CHAR szMsg[256];
	wsprintf(szMsg,"MOUSE_EVENT_RECORD\n button state: %d\nmouse position X=%u,Y=%u",
		mer.dwButtonState,mer.dwMousePosition.X,mer.dwMousePosition.Y);
	MessageBox(NULL,szMsg,"EVENT",MB_OK);
	if(IDOK == MessageBox(NULL,"Exit?","EVENT",MB_OKCANCEL))
	{
		ExitProcess(0);
	}
} 

/* ************************************
* VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
* ����	���ô�С�¼�
* ����	WINDOW_BUFFER_SIZE_RECORD wbsr) �¼�
**************************************/
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	CHAR szMsg[256];
	wsprintf(szMsg,"WINDOW_BUFFER_SIZE_RECORD\nX=%u,Y=%u",
		wbsr.dwSize.X,wbsr.dwSize.Y);
	MessageBox(NULL,szMsg,"EVENT",MB_OK);
} 