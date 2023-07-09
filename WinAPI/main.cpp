#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
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
			//SendMessage(hdlgItemLogin, WM_ENABLE, (WPARAM)(TRUE), 0);
			SendMessage(hdlgItemLogin, WM_SETTEXT, 0, (LPARAM)("Введите имя пользователя"));

			HWND hdlgItemPass;
			hdlgItemPass = GetDlgItem(hwnd, IDC_EDIT2_PASSWORD);
			//SendMessage(hdlgItemPass, EN_CHANGE, (WPARAM)(TRUE), 0);
			SendMessage(hdlgItemPass, WM_SETTEXT, 0, (LPARAM)("Enter Password"));

		}
		break;
		case WM_COMMAND:	//Обрабатываем команды
			switch (LOWORD(wParam))
			{
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