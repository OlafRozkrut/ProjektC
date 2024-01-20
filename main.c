#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "young.h"

#define FILE_STANDARD 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define FILE_CROSSED 4
#define GENERATE_BUTTON 5
float** tablica;
float rand_float()
{
    return((float)rand())/((double)RAND_MAX);
    // bierzemy przypadkowa liczbe i dzielimy ja przez stala rand_max
}

float **tablica_younga(int n, float liczba)
{
    srand(time(NULL));
    int m = n; // pomocnicza zmienna uzywana do ograniczenia wielkosci tablicy
    float **A = (float **)malloc(n * sizeof(float *)); //dynamiczne alokowanie pamieci
    for (int i = 0; i < n; i++)
    {
        A[i] = (float *)malloc(n * sizeof(float));
        for (int j = 0; j < n; j++)
        {
            if (j >= m)
            {
                A[i][j] = NAN;
            }
            else
            {
                A[i][j] = rand_float();//losowa liczba
            }
        }
        m--;
    }
    A[0][0] = liczba;
    return A;
}

float** jeu_de_taquin(int x, float **tab, int a, int b)
{
    printf("(%d, %d)\n", a, b);
    if (a + b == x - 1)
    {
        return tab;
    }
    else
    {
        if (tab[a][b + 1] < tab[a + 1][b])
        {
            for(int i=a+1;i<x;i++)
            {
                tab[i][b] = NAN;
            }
            return jeu_de_taquin(x, tab, a, b + 1);
        }
        else
        {
            for(int i=b+1;i<x;i++)
            {
                tab[a][i] = NAN;
            }
            return jeu_de_taquin(x, tab, a+1,b);
        }
    }
}
void przypisanie()
{
tablica=tablica_younga(4,20);
}
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);
int pomoc=0;

void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;
HWND hOut;

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args,int ncmdshow)
{
WNDCLASSW wc={0};

wc.hbrBackground= (HBRUSH)COLOR_WINDOW;
wc.hCursor = LoadCursor(NULL,IDC_ARROW);
wc.hInstance= hInst;
wc.lpszClassName=L"myWindowClass";
wc.lpfnWndProc=WindowProcedure;
MessageBox(NULL, "Aby wybraæ rodzaj tablicy u¿yj menu w górnej czêœci aplikacji","PodpowiedŸ",MB_OK);
przypisanie();
if(!RegisterClassW(&wc))
    return -1;
CreateWindowW( L"myWindowClass", L"Aplikacja", WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,700,700,NULL,NULL,NULL,NULL);
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
        {

            if (tablica == NULL)
                {
                    fprintf(stderr, "Nie udalo się zaalokowac pamieci.\n");
                    return 1;
                }

        char tekst[1000];
        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                index += sprintf(tekst + index, "%f ", tablica[i][j]);
            }
        index += sprintf(tekst + index, "\r\n");
        }
        tekst[index - 2] = '\0';
        SetWindowText(hOut, tekst);
        }
            break;
        case FILE_CROSSED:
            MessageBeep(MB_ICONERROR);
            break;
        case GENERATE_BUTTON:
            {
                float **nowa_tablica = jeu_de_taquin(4,tablica,0,0);
                char tekst[1000];
                int index = 0;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        index += sprintf(tekst + index, "%f ", tablica[i][j]);
                    }
                index += sprintf(tekst + index, "\r\n");
                }
                tekst[index - 2] = '\0';

                SetWindowText(hOut, tekst);
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
    CreateWindowW(L"button",L"Generuj Sciezke",WS_VISIBLE | WS_CHILD ,280,20,120,50,hWnd,(HMENU) GENERATE_BUTTON,NULL,NULL);
    hOut = CreateWindowW(L"edit",L"",WS_VISIBLE | WS_CHILD |WS_BORDER| ES_MULTILINE,100,100,500,500,hWnd,NULL,NULL,NULL);
}
