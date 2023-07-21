#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<cstdio>

CONST CHAR g_sz_MY_WINDOW_CLASS[] = "MyWindow"; //объявление имени класса

CONST INT g_i_BTN_SIZE = 50;		//размер кнопки
CONST INT g_i_DISTANCE = 10;		//размер между кнопками
CONST INT g_i_START_X = 10;			//отступ от начала окна по х
CONST INT g_i_START_Y = 10;			//отступ от начала окна по у
CONST INT g_i_SCREEN_HEIGHT = 25;
CONST INT g_i_DISPLAY_WIDTH = (g_i_BTN_SIZE + g_i_DISTANCE) * 5;
CONST INT g_i_DISPLAY_HEIGHT = 18;

DOUBLE a = 0;
DOUBLE b = 0;
INT z = 0;
BOOL complete = false;
BOOL stored = FALSE;


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
	int screen_width = GetSystemMetrics(SM_CXSCREEN);	
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * .75;
	int window_heigth = screen_height * .75;
	int start_x = screen_width * .125;
	int start_y = screen_height * .125;
	HWND hwnd = CreateWindowEx
	(
		0,
		g_sz_MY_WINDOW_CLASS,			//имя класса окна
		g_sz_MY_WINDOW_CLASS,			//заголовок окна
		WS_OVERLAPPEDWINDOW,			//стиль для главного окна программы всегда именно такой - (TPO_LEVEL_WINDOW)	
		start_x, start_y,				//координаты
		window_width, window_heigth,	//ширина, высота
		NULL,							//Perent Window
		NULL,							//Для главного окна это меню, для дочернего окна это ID его ресурса
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
	while (GetMessage(&msg, NULL, 0, 0) > 0)
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
	{
		HWND hEdit = CreateWindowEx(0, "Edit", "0", WS_CHILD | WS_VISIBLE | ES_RIGHT | WS_BORDER,
									g_i_START_X, g_i_START_Y,
									g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
									hwnd, (HMENU)IDC_EDIT, GetModuleHandle(NULL), NULL);
		INT number = 1;
		CHAR sz_btn_name[] = "0";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_btn_name[0] = number + '0';
				CreateWindowEx(NULL, "Button", sz_btn_name, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * j,
					g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_DISTANCE + (g_i_BTN_SIZE + g_i_DISTANCE) * (2 - i),
					g_i_BTN_SIZE, g_i_BTN_SIZE,
					hwnd,
					(HMENU)(number + 1000),
					GetModuleHandle(NULL), NULL);
				number++;
			}
		}

		CreateWindowEx(NULL, "Button", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE, hwnd, (HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "+/-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + g_i_BTN_SIZE + g_i_DISTANCE,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE, hwnd, (HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL), NULL);
		
		CreateWindowEx(NULL, "Button", ".", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + g_i_BTN_SIZE*2 + g_i_DISTANCE*2, 
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE, hwnd, (HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE)*4,
			g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE * 2 + g_i_DISTANCE, 
			hwnd, (HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE)*4,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 2 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE*2+ g_i_DISTANCE,
			hwnd, (HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE)*3,
			g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE, 
			hwnd, (HMENU)IDC_BUTTON_SLASH,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE)*3,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE * 2),
			g_i_BTN_SIZE, g_i_BTN_SIZE, 
			hwnd, (HMENU)IDC_BUTTON_ASTER,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE)*3,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 2 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_MINUS,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE)*3,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE, 
			hwnd, (HMENU)IDC_BUTTON_PLUS,
			GetModuleHandle(NULL), NULL);

	}break;

	case WM_COMMAND:
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};

		SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
		CHAR sz_digit[2] = {};
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			if (stored == TRUE)
			{
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
				for (int i = 0; i < SIZE; i++)sz_buffer[i] = 0;
				stored = FALSE;
			}
			sz_digit[0] = LOWORD(wParam) - 952;
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}

		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			if (strchr(sz_buffer, '.'))break;
			strcat(sz_buffer, ".");
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}

		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
		}

		if (LOWORD(wParam) == IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(hwnd, WM_COMMAND, LPARAM(IDC_BUTTON_EQUAL), 0);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			a = strtod(sz_buffer, NULL);
			z = LOWORD(wParam);
			stored = TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			b = strtod(sz_buffer, NULL);
			switch (z)
			{
			case IDC_BUTTON_PLUS:a += b; break;
			case IDC_BUTTON_MINUS:a -= b; break;
			case IDC_BUTTON_ASTER:a *= b; break;
			case IDC_BUTTON_SLASH:a /= b; break;
			default:a = b; break;
			}
			sprintf(sz_buffer, "%f", a);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			stored = TRUE;
		}

	}break;

	case WM_KEYDOWN:
	{
		if (LOWORD(wParam) >= '0' && LOWORD(wParam) <= '9')SendMessage(hwnd, WM_COMMAND, LOWORD(wParam) + 1000 - '0', 0);
		switch (LOWORD(wParam)) 
		{
		case VK_OEM_PERIOD:SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_POINT, 0); break;
		case VK_ESCAPE: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLEAR, 0); break;
		}
	}

	case WM_SIZE:
	case WM_MOVE:
	{
		CONST INT SIZE = 256;
		CHAR sz_msg[SIZE] = {};

		RECT rect;
		GetWindowRect(hwnd, &rect);

		INT window_width = rect.right - rect.left;
		INT window_height = rect.bottom - rect.top;
		sprintf(sz_msg, "%s - Size: %i %i, Position: %i %i", g_sz_MY_WINDOW_CLASS, window_width, window_height, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_msg);
	}break;

	case WM_DESTROY:
		PostQuitMessage(NULL); break;
		default: return DefWindowProc(hwnd, uMsg, wParam, lParam);

	case WM_CLOSE:
		if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
			DestroyWindow(hwnd); break;
	}
	return FALSE;
}