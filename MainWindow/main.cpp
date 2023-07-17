#include<Windows.h>

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

	wc.hIcon = LoadIcon(hInstanse, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(hInstanse, IDI_APPLICATION);
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

	//3 Запуск цикла сообщений

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