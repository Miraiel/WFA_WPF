#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<cstdio>

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyWindow"; //объявление имени класса

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInst, LPSTR lpCmsLine, INT nCmdShow)
{
	//1 Регистрация класса окна

	WNDCLASSEX wc;					//объявляем
	ZeroMemory(&wc, sizeof(wc));	//зануляем

	wc.cbSize = sizeof(wc);	//cb - Count Bytes размер класса в байтах
	wc.cbClsExtra = 0;		//Class ExtraBytes дополнительные байты класса
	wc.cbWndExtra = 0;		//WindowExtraBytes дополнительные байты окна
	wc.style = 0;

	//настройка внешнего вида окна, иконки курсоры и т.д.

	//wc.hIcon = LoadIcon(hInstanse, MAKEINTRESOURCE(IDI_ICON_VAMP));		//отображается в панели задач
	//wc.hIconSm = LoadIcon(hInstanse, MAKEINTRESOURCE(IDI_ICON_MOON));	//отображается в заголовке окна
	wc.hIcon = (HICON)LoadImage(hInstanse, "Moon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIcon = (HICON)LoadImage(hInstanse, "Vamp.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	//wc.hCursor = (HCURSOR)LoadImage(hInstanse, "Busy.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	wc.hCursor = LoadIcon(hInstanse, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.hInstance = hInstanse;
	wc.lpfnWndProc = (WNDPROC)WndProc;					//процедура окна
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_MY_WINDOW_CLASS; // lpsz - long pointer size zero , если не задать класс будет не зарегистрирован 

	//регистрация

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Класс не зарегистрирован", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2 Создание окна	

	//int screen_width = GetSystemMetrics(SM_CXSCREEN);	
	//int screen_height = GetSystemMetrics(SM_CYSCREEN);
	//int window_width = screen_width * .75;
	//int window_heigth = screen_height * .75;
	//int start_x = screen_width * .125;
	//int stzrt_y = screen_height * .125;


	HWND hwnd = CreateWindowEx
	(
		0,
		g_sz_MY_WINDOW_CLASS,	//имя класса окна
		g_sz_MY_WINDOW_CLASS,	//заголовок окна
		WS_OVERLAPPEDWINDOW,		//стиль для главного окна программы всегда именно такой - (TPO_LEVEL_WINDOW)	
		CW_USEDEFAULT, CW_USEDEFAULT,	//координаты
		CW_USEDEFAULT, CW_USEDEFAULT,	//ширина, высота
		NULL,	//Perent Window
		NULL,	//Для главного окна это меню, для дочернего окна это ID его ресурса
		hInstanse,
		NULL
	);

	if (hwnd == 0)
	{
		MessageBox(NULL, "Окно небыл создано", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);		//задает режим отображения окна
	UpdateWindow(hwnd);				//выполняет прорисовку окна

	//3 Запуск цикла сообщений

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);		//транслирует сообщения виртуаьных клавиш в символьные сообщения
		DispatchMessage(&msg);		//Отправляет сообщения процедуре окна, сообщение берет от GetMessage();
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

	case WM_SIZE:
	case WM_MOVE:
	{
		CONST INT SIZE = 256;
		CHAR sz_msg[SIZE] = {};

		RECT rect;
		GetWindowRect(hwnd, &rect);

		int window_width = rect.right - rect.left;
		int window_height = rect.bottom - rect.top;
		sprintf(sz_msg, "%s - Size: %i %i, Position: %i %i", g_sz_MY_WINDOW_CLASS, window_width, window_height, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_msg);
	}break;

	case WM_DESTROY: PostQuitMessage(0);
		break;

	case WM_CLOSE:
		if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
			DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}