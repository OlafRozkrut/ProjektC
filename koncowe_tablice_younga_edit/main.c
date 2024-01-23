#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "young.h"

#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 5
struct Wypisanie{
    char hello[20];
};
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);
int pomoc=0;

void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;
HWND hOut1;
HWND hOut2;

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args,int ncmdshow)
{
WNDCLASSW wc={0};

wc.hbrBackground= (HBRUSH)COLOR_WINDOW;
wc.hCursor = LoadCursor(NULL,IDC_ARROW);
wc.hInstance= hInst;
wc.lpszClassName=L"myWindowClass";
wc.lpfnWndProc=WindowProcedure;
MessageBox(NULL, "Wpisz rozmiar oraz ilosc tablic do wygenerowania","Podpowiedz",MB_OK);
if(!RegisterClassW(&wc))
    return -1;
CreateWindowW( L"myWindowClass", L"Aplikacja", WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,700,700,NULL,NULL,NULL,NULL);
MSG msg ={0};
while(GetMessage(&msg,NULL,0,0))
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
        case GENERATE_BUTTON:
            {
                int (*wsk_do_funkcji)(int, int);
                wsk_do_funkcji = &dodaj;
                int wynik = wsk_do_funkcji(3, 4);
                printf("Wynik dodawania: %d\n", wynik);
                struct Wypisanie wypisanie;
                strcpy(wypisanie.hello, "Hello");
                printf("%s", wypisanie.hello);
                char buffer1[256];
                char buffer2[256];
                GetWindowText(hOut1, buffer1, sizeof(buffer1));
                GetWindowText(hOut2, buffer2, sizeof(buffer2));

                int value1 = atoi(buffer1);
                int value2 = atoi(buffer2);

                wykres(value1, value2);
            }
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

    AppendMenu(hFileMenu,MF_STRING,FILE_MENU_EXIT,"Wyjdz");


    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenu,"Plik");


    SetMenu(hWnd, hMenu);

}

void AddControls(HWND hWnd)
{
    CreateWindowW(L"button",L"Wykonaj program",WS_VISIBLE | WS_CHILD ,500,100,130,100,hWnd,(HMENU) GENERATE_BUTTON,NULL,NULL);
    CreateWindowW(L"Static",L"Ile",WS_VISIBLE | WS_CHILD ,300,100,100,100,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Wielkosc",WS_VISIBLE | WS_CHILD ,300,300,100,100,hWnd,NULL,NULL,NULL);
    hOut1 = CreateWindowW(L"edit",L"",WS_VISIBLE | WS_CHILD |WS_BORDER| ES_MULTILINE,100,100,100,100,hWnd,NULL,NULL,NULL);
    hOut2 = CreateWindowW(L"edit",L"",WS_VISIBLE | WS_CHILD |WS_BORDER| ES_MULTILINE,100,300,100,100,hWnd,NULL,NULL,NULL);
}
