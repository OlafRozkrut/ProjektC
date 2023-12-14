#include <stdio.h>
#include <stdlib.h>

float **tablica_younga(int n, float liczba)
{
    int m = n; // pomocnicza zmienna uzywana do ograniczenia wielkosci tablicy
    float **A = (float **)malloc(n * sizeof(float *)); //dynamiczne alokowanie pamieci
    for (int i = 0; i < n; i++)
    {
        A[i] = (float *)malloc(n * sizeof(float));
        for (int j = 0; j < n; j++)
        {
            if (j >= m)
            {
                A[i][j] = -1;
            }
            else
            {
                A[i][j] = losowanie_liczby();//losowa liczba
            }
        }
        m--;
    }
    A[0][0] = liczba;
    return A;
}
int main()
{
    float **tablica = tablica_younga(4,20);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            printf(" %f",tablica[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 4; i++)
    {
        free(tablica[i]);
    }
    free(tablica);
    return 0;
}
