#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void AddMenus(HWND hwnd);
void AddControls(HWND hwnd);


HMENU hMenu;
HWND hEdit;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc))
        return -1;

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Windows Programming",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
       // CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        100, 100, 500, 500,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        switch (wParam)
        {
        case FILE_MENU_EXIT:
            DestroyWindow(hwnd);
            break;

        case FILE_MENU_NEW:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case  CHANGE_TITLE:
            wchar_t text[100];
            GetWindowTextW(hEdit, text, 100);
            SetWindowTextW(hwnd, text);
            break;
        }
    case WM_CREATE:
        AddMenus(hwnd);
        AddControls(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);



        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void AddMenus(HWND hwnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, L"SubMenu Item");


    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open Submenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
    AppendMenu(hMenu, MF_STRING, NULL, L"Help");
    SetMenu(hwnd, hMenu);
}

void AddControls(HWND hwnd)
{
    CreateWindowW(L"Static", L"Enter Text Here:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 175, 100, 125, 50, hwnd, NULL, NULL, NULL);
    hEdit=CreateWindowEx(0,L"Edit", L"...", WS_VISIBLE | WS_CHILD|WS_VSCROLL|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL, 175, 155, 125, 50, hwnd, NULL, NULL, NULL);
    //SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)lpszLatin);
    CreateWindowW(L"Button", L"Change Title", WS_VISIBLE | WS_CHILD, 190, 210, 100, 25, hwnd, (HMENU)CHANGE_TITLE, NULL, NULL);
}
