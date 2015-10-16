//Tyler Massicotte 3B A00855150

/*********************************************************************
Comp3770 Assignment#3 (Max 10 marks).

PUT YOUR FULL NAME AND SET AS YOUR WINDOW TITLE! SetWindowText()

When you attempt to click on a radio button the button "runs away" by 20 pixels.
By clicking on the main window using the right mouse button the buttons
will no longer move. Clicking again on the window will allow the buttons to move
again when the mouse is on them.
You will need to get the child window locations using GetWindowRect() but this is
in screen coordinates. You will then need to convert them to positions within the
main window. You will need to use ScreenToClient() for this. However the first
coordinates will need to be adjusted using the parent position (thus you need to
give the ScreenToClient() proc the handle to the parent) but the second coordinate
needs to be adjusted using the client's handle. Once converted you can then use
the function SetWindowPos(). This MUST be performed via windows subclassing!

When you select a menu item, it is checked and the corresponding radio button is
selected. Conversely if you select the a radio button the corresponding menu item
is checked. Background of the window is changed accordingly. DO NOT USE AUTO RADIO
BUTTONS (yes you need to do it the "hard way". Place the buttons neatly as shown in
example.

To get toggling to work - no globals are used but instead a WM_USER msg is sent to the radio
buttons when the user clicks on the main window (thus you need to capture WM_RBUTTONDOWN in
the main window). Note: SetWindowLong() used on the buttons is unreliable and SHOULD NOT BE
USED! [radio buttons need to keep track of their state and do so using the WndExtra]

Marking Guidelines:

Functionality						Max
radio buttons and menus				1
radio buttons checked/unchecked		1
Menu checked/unchecked				1
Menu updates radio buttons			1
radio bnt updates menu				1
Background colour changes			1
Windows Subclassing	- btns move		2
Toggle works via user msg			2

Total 10


Function calls used:

GetMenu(hwnd);
SetWindowText()
CallWindowProc()
SetWindowLongPtr()//to subclass window
SendMessage()
CreateWindow()
GetParent()
GetWindowRect()
ScreenToClient()
SetWindowPos()
//use this command to change the background colour
SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG), CreateSolidBrush(//colour))
InvalidateRect()

Flags:
BM_SETCHECK
MF_CHECKED
MF_UNCHECKED
WS_VISIBLE
WS_CHILD

*********************************************************************/

#include <Windows.h>
#include "wndproc.h"
#include "main.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCMLine, int iCmdShow){
	static TCHAR szAppName[] = TEXT("HelloApplication");
	static HWND	hwnd;
	MSG		msg;
	WNDCLASS wndclass;
	HMENU menu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HelloWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wndclass.lpszClassName = szAppName;


	if (!RegisterClass(&wndclass)){
		MessageBox(NULL, TEXT("This program requires Windows 95/98/NT"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("Tyler Massicotte 3B"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		menu,
		hInstance,
		NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
