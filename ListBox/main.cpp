#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* values[] = { "This","is","my","first","List","Box" };


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPAram);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)values[i]);
		}

	}break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDC_BUTTON1_ADD:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
			return 0;
		}break;

		case IDC_BUTTON_DELETE:

			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			SendMessage(hList, LB_GETTEXT, SendMessage(hList, LB_GETTEXT, 0, 0),0);
			break;

		case IDOK:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_massege[SIZE] = {};
			sprintf(sz_massege, "�� ������� ������� � %i, �� ��������� \"%s\"", i, sz_buffer);
			MessageBox(hwnd, sz_massege, "Info", MB_OK | MB_ICONINFORMATION);
		}break;


		case IDCANCEL: EndDialog(hwnd, 0); break;
		}break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPAram)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			const INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_ADD), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			//�������� ������������ ����
			HWND hParent = GetParent(hwnd);
			HWND hList = GetDlgItem(hParent, IDC_LIST1);
			if (SendMessage(hList, LB_FINDSTRING, 0, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			else
				MessageBox(hwnd, "����� ������ ��� ���������","Info", MB_OK|MB_ICONINFORMATION);

		}break;
		case IDCANCEL:
			break;

	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}