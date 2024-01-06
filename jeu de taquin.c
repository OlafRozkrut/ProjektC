#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float rand_float()
{
    float wynik = ((float)rand())/((double)RAND_MAX);
    return wynik;
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
                A[i][j] = rand_float();
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

int main()
{
    srand(time(NULL));
    int a = 7; //wielkosc tablicy
    float b = 0.56;//wartosc w (0,0)
    float **tablica = tablica_younga(a,b);//utworzenie tablicy
    for(int i=0;i<a;i++)//wypisanie tablicy
    {
        for(int j=0;j<a;j++)
        {
            printf(" %f",tablica[i][j]);
        }
        printf("\n");
    }

    float **nowa_tablica = jeu_de_taquin(a,tablica,0,0);
    for(int i=0;i<a;i++)//wypisanie tablicy
    {
        for(int j=0;j<a;j++)
        {
            printf(" %f",nowa_tablica[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < a; i++)//zwolnienie tablicy
    {
        free(tablica[i]);
    }

    free(tablica);//zwolnienie tablicy
    for (int i = 0; i < a; i++)//zwolnienie tablicy
    {
        free(nowa_tablica[i]);
    }
    free(nowa_tablica);//zwolnienie tablicy
    return 0;
}
