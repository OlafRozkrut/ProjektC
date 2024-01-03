#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define FILE_STANDARD 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define FILE_CROSSED 4
#define GENERATE_BUTTON 5
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;
HWND hName,hAge,hOut;

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args,int ncmdshow)
{
WNDCLASSW wc={0};

wc.hbrBackground= (HBRUSH)COLOR_WINDOW;
wc.hCursor = LoadCursor(NULL,IDC_ARROW);
wc.hInstance= hInst;
wc.lpszClassName=L"myWindowClass";
wc.lpfnWndProc=WindowProcedure;
MessageBox(NULL, "Aby wybraæ rodzaj tablicy u¿yj menu w górnej czêœci aplikacji","PodpowiedŸ",MB_OK);

if(!RegisterClassW(&wc))
    return -1;
CreateWindowW( L"myWindowClass", L"Aplikacja", WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,500,500,NULL,NULL,NULL,NULL);
MSG msg ={0};
while(GetMessage(&msg,NULL,NULL,NULL))
{
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
return 0;
}
LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND:

        switch(wp)
        {
        case FILE_MENU_EXIT:
            DestroyWindow(hWnd);
            break;
        case FILE_STANDARD:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case FILE_CROSSED:
            MessageBeep(MB_ICONERROR);
            break;
        case GENERATE_BUTTON: ;

            char name[30],age[10],out[50];
            GetWindowText(hName,name,30);
            GetWindowText(hAge,age,10);
            strcpy(out,name);
            strcat(out," To ");
            strcat(out,age);
            strcat(out,"jeszcze nic nie robi.");

            SetWindowText(hOut,out);
            break;
        }

    break;
    case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
    case WM_DESTROY:
            PostQuitMessage(0);
            break;
    default:
            return DefWindowProc(hWnd,msg,wp,lp);
    }
}
void AddMenus(HWND hWnd)
{
    hMenu=CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu,MF_STRING,FILE_STANDARD,"Standardowa");
    AppendMenu(hSubMenu,MF_STRING,FILE_CROSSED,"Skrzy¿owana");

    AppendMenu(hFileMenu,MF_POPUP,(UINT_PTR)hSubMenu,"Rodzaj Tablicy");
    AppendMenu(hFileMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hFileMenu,MF_STRING,FILE_MENU_EXIT,"WyjdŸ");


    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenu,"Plik");


    SetMenu(hWnd, hMenu);

}

void AddControls(HWND hWnd)
{
    CreateWindowW(L"button",L"Generuj Sciezke",WS_VISIBLE | WS_CHILD ,190,50,120,50,hWnd,(HMENU) GENERATE_BUTTON,NULL,NULL);
    hOut = CreateWindowW(L"edit",L"",WS_VISIBLE | WS_CHILD |WS_BORDER,100,150,300,180,hWnd,NULL,NULL,NULL);
}
