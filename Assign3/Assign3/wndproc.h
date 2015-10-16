#ifndef WNDPROC_H
#define WNDPROC_H

LRESULT CALLBACK HelloWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void check_menu(HMENU menu, int id);
LRESULT CALLBACK ButtonWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


#endif