#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* values[] = { "This","is","my","First","List","Box" };


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, NULL);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);

			for (int i = 0; i < ARRAYSIZE(values); i++)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)values[i]);
			}
			//SetFocus(hList);

		}break;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDOK:
				{
					
				}break;
			}
		case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}