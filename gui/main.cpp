#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_SAVE 3
#define FILE_MENU_EXIT 4
#define HELP_MENU 5

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInst, LPSTR args, int ncmdshow)
{
	//window class
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;
	
	if (!RegisterClassW(&wc))
		return -1;
	
	CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);
	
	MSG msg = { 0 };

	while (GetMessage(&msg,NULL,NULL,NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		//appends close program to a menu button
		case FILE_MENU_EXIT:
				DestroyWindow(hWnd);
			break;
		//makes file ment new make a sound
		case FILE_MENU_NEW:
				MessageBeep(MB_OK);
			break;
		//makes a messagebox to connect me
		case HELP_MENU:
				MessageBox(hWnd,"     to contact me email \n chatbox8558@gmail.com", "help", MB_OK);
			break;
		}
		break;
	//creates menu
	case WM_CREATE:
		AddMenus(hWnd);
		break;
	//closes program
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	//creates the file menu
	HMENU hFileMenu = CreateMenu();
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "file");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "new file");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, "open file");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING,FILE_MENU_SAVE, "save file");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "exit");
	//creates the help menu
	HMENU hHelpMenu = CreateMenu();
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "help");
	AppendMenu(hHelpMenu, MF_STRING, HELP_MENU, "contact");
	SetMenu(hWnd, hMenu);
}