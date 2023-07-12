#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITE[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/*
	HWND - обработчик окта, для того чтобы обратиться к окну можно только через его обработчик(Handler)
	UINT uMasg - сообщение 
	WRAPAM/LPARAM - параметры сообщения, зависят от самого сообщнния (4 параметра)
*/

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hInstans запущенной программы всегда можно получить при помощи функции GetModuleHandle(NULL)
	//MessageBox(NULL, "Привет Мир! Я окно сообщения :-)", "Info", MB_YESNOCANCEL | MB_ICONINFORMATION);

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, NULL);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //Создаем элементы окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);	//иконка

		HWND hdlgItemLogin;
		hdlgItemLogin = GetDlgItem(hwnd, IDC_EDIT1_LOGIN);
		SendMessage(hdlgItemLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITE);

		HWND hdlgItemPass;
		hdlgItemPass = GetDlgItem(hwnd, IDC_EDIT2_PASSWORD);
		SendMessage(hdlgItemPass, WM_SETTEXT, 0, (LPARAM)("Введите пароль"));

	}
	break;
	case WM_COMMAND:	//Обрабатываем команды
		switch (LOWORD(wParam))
		{
			case IDC_EDIT1_LOGIN:
			{
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT1_LOGIN);
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (HIWORD(wParam) == EN_SETFOCUS)
				{
					if (strcmp(sz_buffer, g_sz_LOGIN_INVITE) == 0)
						SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
				}
				if (HIWORD(wParam) == EN_KILLFOCUS)
				{
					if (strlen(sz_buffer) == 0)
						SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITE);
				}
			}
			break;
		case IDC_BUTTON1_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT1_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT2_PASSWORD);
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd, IDC_STATIC_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}