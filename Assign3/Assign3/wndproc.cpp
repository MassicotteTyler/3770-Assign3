#include <Windows.h>
#include "main.h"
#include "wndproc.h"
#include "resource.h"

LRESULT CALLBACK HelloWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

	static TCHAR* button[] = { TEXT("Red"), TEXT("Blue"), TEXT("Green"), TEXT("Orange"), TEXT("Aqua") };
	static int colour[] = { RGB(255, 0, 0), RGB(0, 0, 255), RGB(0, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255) };
	static int cxChar, cyChar;
	static HWND hwndButton[5];
	int i;
	COLORREF bgcolor = colour[0];
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message){
	case WM_CREATE:

		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		for (i = 0; i < 5; i++){
			hwndButton[i] = CreateWindow(TEXT("button"),
				button[i],
				WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
				cxChar, cyChar * (1 + 2 * i) + 100,
				20 * cxChar, 7 * cyChar / 4,
				hwnd, (HMENU)(i + ID_FILE_RED),
				((LPCREATESTRUCT)lParam)->hInstance, NULL);

		}

		return 0;
	case WM_ERASEBKGND:
		HBRUSH brush;
		HPEN pen;
		RECT rect;

		pen = CreatePen(PS_SOLID, 1, bgcolor);
		brush = CreateSolidBrush(bgcolor);

		SelectObject((HDC)wParam, pen);
		SelectObject((HDC)wParam, brush);
		
		GetClientRect(hwnd, &rect);

		Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, colour[2]);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case ID_FILE_RED:
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_RED);
				return 0;
			case ID_FILE_BLUE:
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_BLUE);
				return 0;
			case ID_FILE_GREEN:
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_GREEN);
				bgcolor = colour[4];
				InvalidateRect(hwnd, NULL, TRUE);
				WM_ERASEBKGND;
				return 0;
			case ID_FILE_ORANGE:
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_ORANGE);
				return 0;
			case ID_FILE_AQUA:
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_AQUA);
				return 0;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

