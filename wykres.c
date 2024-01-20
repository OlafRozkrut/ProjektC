#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
float wylosowane[100000];
int uzyte_wylosowane = 0;
float rand_float()
{
    float wynik = ((float)rand())/((double)RAND_MAX);
    return wynik;
}
float **tablica_younga(int n, float liczba)
{
    srand(time(0));
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
                A[i][j] = wylosowane[uzyte_wylosowane];//rand_float();
                uzyte_wylosowane++;

            }
        }
        m--;
    }
    A[0][0] = liczba;
    return A;
}
float** jeu_de_taquin(int x, float **tab, int a, int b)
{
    if (a + b == x - 1)
    {
        FILE *punkty_do_odczytu;
        punkty_do_odczytu = fopen("punkty_do_odczytu.txt", "a");
        fprintf(punkty_do_odczytu,"(%d,%d)\n",a,b);
        fclose(punkty_do_odczytu);
        FILE *punkty_do_wykresu;
        punkty_do_wykresu = fopen("punkty_do_wykresu.txt", "a");
        fprintf(punkty_do_wykresu,"%d\n",a*b);
        fclose(punkty_do_wykresu);
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
void swap(float* a, float* b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

int partition(float arr[], int low, int high)
{
    float pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(float arr[], int low, int high)
{
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}
void wykres()
{
    FILE *punkty_do_odczytu;
    punkty_do_odczytu = fopen("punkty_do_odczytu.txt", "w");
    fclose(punkty_do_odczytu);
    FILE *punkty_do_wykresu;
    punkty_do_wykresu = fopen("punkty_do_wykresu.txt", "w");
    fclose(punkty_do_wykresu);
    for(int i=0;i<100000;i++)
    {
        wylosowane[i]=rand_float();
    }
    int ile,wielkosc_tablic;
    printf("Ile?:\n");
    scanf("%d",&ile);
    printf("Wielkosc tablic?:\n");
    scanf("%d",&wielkosc_tablic);
    float liczby[ile];
    for(int i=0;i<ile;i++)
    {
        liczby[i]=rand_float();
    }
    quicksort(liczby,0,ile-1);
    FILE *liczby_plik;
    liczby_plik = fopen("liczby.txt", "w");
    if (liczby_plik == NULL)
    {
        printf("Nie mo¿na otworzyæ pliku.\n");
        return 1;
    }
    for(int i=0;i<ile;i++)
    {
        fprintf(liczby_plik,"%f\n",liczby[i]);
    }
    fclose(liczby_plik);
    FILE *tablice_younga;
    FILE *jeu_de_taquin_plik;
    tablice_younga = fopen("tablice_younga.txt", "w");
    jeu_de_taquin_plik = fopen("jeu_de_taquin.txt", "w");
    for(int i=0;i<ile;i++)
    {

        float **pomocnicza_tabela = tablica_younga(wielkosc_tablic,liczby[i]);
        for(int j=0;j<wielkosc_tablic;j++)
        {
            for(int k=0;k<wielkosc_tablic;k++)
            {
                if(isnan(pomocnicza_tabela[j][k]))
                {
                    fprintf(tablice_younga,"         ");
                }
                else
                {
                    fprintf(tablice_younga,"%f ",pomocnicza_tabela[j][k]);
                }
            }
            fprintf(tablice_younga,"\n");
        }
        fprintf(tablice_younga,"\n");
        float **pomocnicza_tabela2 = jeu_de_taquin(wielkosc_tablic,pomocnicza_tabela,0,0);
        for(int j=0;j<wielkosc_tablic;j++)
        {
            for(int k=0;k<wielkosc_tablic;k++)
            {
                if(isnan(pomocnicza_tabela2[j][k]))
                {
                    fprintf(jeu_de_taquin_plik,"         ");
                }
                else
                {
                    fprintf(jeu_de_taquin_plik,"%f ",pomocnicza_tabela2[j][k]);
                }
            }
            fprintf(jeu_de_taquin_plik,"\n");
        }

    }
    fclose(tablice_younga);
    fclose(jeu_de_taquin_plik);
    /////////////////////////////////////
    FILE *punkty_do_wykresu_plik;
    int wykres_y[ile];
    // Otwieranie pliku do odczytu (w trybie tekstowym)
    punkty_do_wykresu_plik = fopen("punkty_do_wykresu.txt", "r");
    if (punkty_do_wykresu_plik == NULL)
    {
        fprintf(stderr, "Nie udało się otworzyć pliku.\n");
        return 1;  // zwraca 1, aby oznaczyć błąd
    }
    // Odczytywanie danych z pliku i zapisywanie ich do tablicy
    for (int i = 0; i < ile; ++i)
    {
        fscanf(punkty_do_wykresu_plik, "%d", &wykres_y[i]);
    }
    // Zamykanie pliku
    fclose(punkty_do_wykresu_plik);
    // Teraz tablica zawiera wczytane wartości
    ////////////////////////////////////
    FILE *dane = fopen("dane.txt", "w");

    if (dane == NULL)
    {
        fprintf(stderr, "Nie można otworzyć pliku.\n");
        return 1;
    }

    for (int i = 0; i < ile; i++)
    {
        fprintf(dane, "%f %d\n", liczby[i], wykres_y[i]);
    }
    fclose(dane);
    // Wywołaj Gnuplot w terminalu
    #ifdef _WIN32
        system("start gnuplot -persist -e \"plot 'dane.txt' with linespoints\"");
    #else
        system("gnuplot -persist -e \"plot 'dane.txt' with linespoints\"");
    #endif
}
int main()
{
    wykres();
    return 0;
}
