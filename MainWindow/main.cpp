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
CONST INT g_i_DISPLAY_WIDTH = (g_i_BTN_SIZE * 5 + g_i_DISTANCE * 4);
CONST INT g_i_DISPLAY_HEIGHT = 18;

static DOUBLE a = 0;
static DOUBLE b = 0;
static char old_operation = 0;
static char operation_input = false;
static char operation = 0;
static BOOL complete = false;
static BOOL stored = false;


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
	//int window_width = screen_width * .75;
	//int window_heigth = screen_height * .75;
	int window_width = g_i_START_X * 2 + g_i_DISPLAY_WIDTH + 16;
	int window_heigth = g_i_START_Y * 2 + g_i_DISPLAY_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 4 + 47;
	int start_x = screen_width * .125;
	int start_y = screen_height * .125;
	HWND hwnd = CreateWindowEx
	(
		0,
		g_sz_MY_WINDOW_CLASS,			//имя класса окна
		g_sz_MY_WINDOW_CLASS,			//заголовок окна
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		//WS_OVERLAPPEDWINDOW,			//стиль для главного окна программы всегда именно такой - (TPO_LEVEL_WINDOW)	
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
			g_i_START_X + g_i_BTN_SIZE * 2 + g_i_DISTANCE * 2,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE, hwnd, (HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 4,
			g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE * 2 + g_i_DISTANCE,
			hwnd, (HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 4,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 2 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE * 2 + g_i_DISTANCE,
			hwnd, (HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_SLASH,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE * 2),
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_ASTER,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 2 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_MINUS,
			GetModuleHandle(NULL), NULL);

		CreateWindowEx(NULL, "Button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BTN_SIZE + g_i_DISTANCE) * 3,
			g_i_START_Y + g_i_SCREEN_HEIGHT + (g_i_BTN_SIZE + g_i_DISTANCE) * 3 + g_i_DISTANCE,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, (HMENU)IDC_BUTTON_PLUS,
			GetModuleHandle(NULL), NULL);

	}break;

	case WM_COMMAND:
	{
		SetFocus(hwnd);
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);

		CHAR sz_digit[2] = {};
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			complete = true;
			if (stored)
			{
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
				stored = false;
			}

			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			while (sz_buffer[0] == '0')
			{
				for (int i = 0; i < sz_buffer[i]; i++)
					sz_buffer[i] = sz_buffer[i + 1];
			}
			sz_digit[0] = LOWORD(wParam) - 1000 + '0';
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}

		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (strchr(sz_buffer, '.'))break;
			strcat(sz_buffer, ".");
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}

		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"0");
			a = 0;
			stored = false;
		}

		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (complete)b = strtod(sz_buffer, NULL);
			if (a == 0)a = b;
			stored = true;
			complete = false;
			if (/*operation != old_operation && */operation_input)
			{
				SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);
			}
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_PLUS:operation = '+'; break;
			case IDC_BUTTON_MINUS:operation = '-'; break;
			case IDC_BUTTON_SLASH:operation = '/'; break;
			case IDC_BUTTON_ASTER:operation = '*'; break;
			}
			operation_input = true;
		}
		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (complete)b = strtod(sz_buffer, NULL);
			complete = false;
			switch (operation)
			{
			case '+': a += b; break;
			case '-': a -= b; break;
			case '*': a *= b; break;
			case '/': a /= b; break;
			}
			//old_operation = operation;
			operation_input = false;
			sprintf(sz_buffer, "%g", a);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}

	}break;

	case WM_KEYDOWN:
	{
		//char symbol[2]{};
		//symbol[0] = LOWORD(wParam);
		//MessageBox(hwnd, symbol, "Symbol", MB_OK);
		
		if (GetKeyState(VK_LSHIFT) < 0)
		{
			if (wParam == 0x38)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
		}
		else 
		{
			if (LOWORD(wParam) >= '0' && LOWORD(wParam) <= '9')
				SendMessage(hwnd, WM_COMMAND, LOWORD(wParam) - '0' + 1000, 0);
		}

			if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
				SendMessage(hwnd, WM_COMMAND, LOWORD(wParam) - 0x60 + 1000, 0);
			
		switch (LOWORD(wParam))
		{
		case VK_ADD:		case VK_OEM_PLUS:SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0); break;
		case VK_SUBTRACT:	case VK_OEM_MINUS:SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MINUS, 0); break;
		case VK_MULTIPLY:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0); break;
		case VK_OEM_2:		case VK_DIVIDE:SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SLASH, 0); break;
		case VK_RETURN:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0); break;
		case VK_ESCAPE:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLEAR, 0); break;
		}

		if (wParam == VK_OEM_PERIOD|| wParam == VK_DECIMAL)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_POINT, 0);
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
		//if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
		DestroyWindow(hwnd); break;
	}
	return FALSE;
}