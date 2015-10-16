//Tyler Massicotte 3B A00855150

#include <Windows.h>
#include "main.h"
#include "wndproc.h"
#include "resource.h"
WNDPROC buttonClass[5];


LRESULT CALLBACK HelloWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

	static TCHAR* button[] = { TEXT("Red"), TEXT("Blue"), TEXT("Green"), TEXT("Orange"), TEXT("Aqua") };
	static int colour[] = { RGB(255, 0, 0), RGB(0, 0, 255), RGB(0, 255, 0), RGB(255, 165, 0), RGB(0, 255, 255) };
	static int cxChar, cyChar;
	static HWND hwndButton[5];
	HMENU menu = GetMenu(hwnd);
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
			buttonClass[i] = (WNDPROC)SetWindowLong(hwndButton[i], GWL_WNDPROC, (long)ButtonWndProc);

		}
		CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_RED);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_RBUTTONUP:
		SendMessage(hwndButton[0], WM_USER, wParam, lParam);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case ID_FILE_RED:
				check_menu(menu, ID_FILE_RED);
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_RED);
				bgcolor = colour[0];
				SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(bgcolor));
				InvalidateRect(hwnd, NULL, TRUE);
				return 0;
			case ID_FILE_BLUE:
				check_menu(menu, ID_FILE_BLUE);
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_BLUE);
				bgcolor = colour[1];
				SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(bgcolor));
				InvalidateRect(hwnd, NULL, TRUE);
				return 0;
			case ID_FILE_GREEN:
				check_menu(menu, ID_FILE_GREEN);
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_GREEN);
				bgcolor = colour[2];
				SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(bgcolor));
				InvalidateRect(hwnd, NULL, TRUE);
				return 0;
			case ID_FILE_ORANGE:
				check_menu(menu, ID_FILE_ORANGE);
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_ORANGE);
				bgcolor = colour[3];
				SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(bgcolor));
				InvalidateRect(hwnd, NULL, TRUE);
				return 0;
			case ID_FILE_AQUA:
				check_menu(menu, ID_FILE_AQUA);
				CheckRadioButton(hwnd, ID_FILE_RED, ID_FILE_AQUA, ID_FILE_AQUA);
				bgcolor = colour[4];
				SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(bgcolor));
				InvalidateRect(hwnd, NULL, TRUE);
				return 0;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void check_menu(HMENU menu, int id)
{
	switch (id)
	{
		case ID_FILE_RED:
			CheckMenuItem(menu, ID_FILE_RED, MF_CHECKED);
			CheckMenuItem(menu, ID_FILE_BLUE, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_GREEN, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_ORANGE, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_AQUA, MF_UNCHECKED);
			break;
		case ID_FILE_BLUE:
			CheckMenuItem(menu, ID_FILE_RED, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_BLUE, MF_CHECKED);
			CheckMenuItem(menu, ID_FILE_GREEN, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_ORANGE, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_AQUA, MF_UNCHECKED);
			break;
		case ID_FILE_GREEN:
			CheckMenuItem(menu, ID_FILE_RED, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_BLUE, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_GREEN, MF_CHECKED);
			CheckMenuItem(menu, ID_FILE_ORANGE, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_AQUA, MF_UNCHECKED);
			break;
		case ID_FILE_ORANGE:
			CheckMenuItem(menu, ID_FILE_RED, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_BLUE, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_GREEN, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_ORANGE, MF_CHECKED);
			CheckMenuItem(menu, ID_FILE_AQUA, MF_UNCHECKED);
			break;
		case ID_FILE_AQUA:
			CheckMenuItem(menu, ID_FILE_RED, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_BLUE, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_GREEN, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_ORANGE, MF_UNCHECKED);
			CheckMenuItem(menu, ID_FILE_AQUA, MF_CHECKED);
			break;
	}
}

LRESULT CALLBACK ButtonWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool mButtons = true;
	int id = GetWindowLong(hwnd, GWL_ID);

	switch (message)
	{
		case WM_MOUSEMOVE:
			if (mButtons)
			{
				POINT p;
				RECT rect;
				GetWindowRect(hwnd, &rect);
				p.x = rect.left;
				p.y = rect.top;
				
				ScreenToClient(GetParent(hwnd), (LPPOINT)&p);

				SetWindowPos(hwnd, HWND_TOP, p.x + 20, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);

			}
			return 0;
		case WM_USER:
			mButtons = !mButtons;
			return 0;
	}
	return CallWindowProc(buttonClass[id - ID_FILE_RED], hwnd, message, wParam, lParam);

}


