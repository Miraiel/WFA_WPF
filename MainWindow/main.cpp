#include<Windows.h>

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyWindow"; //���������� ����� ������
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInst, LPSTR lpCmsLine, INT nCmdShow)
{
	//1 ����������� ������ ����

	WNDCLASSEX wc;					//���������
	ZeroMemory(&wc, sizeof(wc));	//��������

	wc.cbSize = sizeof(wc);	//cb - Count Bytes ������ ������ � ������
	wc.cbClsExtra = 0;		//Class ExtraBytes �������������� ����� ������
	wc.cbWndExtra = 0;		//WindowExtraBytes �������������� ����� ����
	wc.style = 0;

	//��������� �������� ���� ����, ������ ������� � �.�.

	wc.hIcon = LoadIcon(hInstanse, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(hInstanse, IDI_APPLICATION);
	wc.hCursor = LoadIcon(hInstanse, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.hInstance = hInstanse;
	wc.lpfnWndProc = (WNDPROC)WndProc;					//��������� ����
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_MY_WINDOW_CLASS; // lpsz - long pointer size zero , ���� �� ������ ����� ����� �� ��������������� 

	//�����������

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "����� �� ���������������", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2 �������� ����

	HWND hwnd = CreateWindowEx
	(
		0,
		g_sz_MY_WINDOW_CLASS,	//��� ������ ����
		g_sz_MY_WINDOW_CLASS,	//��������� ����
		WS_OVERLAPPEDWINDOW,		//����� ��� �������� ���� ��������� ������ ������ ����� - (TPO_LEVEL_WINDOW)	
		CW_USEDEFAULT, CW_USEDEFAULT,	//����������
		CW_USEDEFAULT, CW_USEDEFAULT,	//������, ������
		NULL,	//Perent Window
		NULL,	//��� �������� ���� ��� ����, ��� ��������� ���� ��� ID ��� �������
		hInstanse,
		NULL
	);

	if (hwnd == 0)
	{
		MessageBox(NULL, "���� ����� �������", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//3 ������ ����� ���������

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_COMMAND:
		break;

	case WM_DESTROY: PostQuitMessage(0);
		break;

	case WM_CLOSE: DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}