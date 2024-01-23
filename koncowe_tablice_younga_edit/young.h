#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int dodaj(int a, int b);
float wylosowane[100000];
int uzyte_wylosowane;
float rand_float();
float **tablica_younga(int n, float liczba);
float** jeu_de_taquin(int x, float **tab, int a, int b);
void swap(float* a, float* b);
int partition(float arr[], int low, int high);
void quicksort(float arr[], int low, int high);
void wykres(int ile,int wielkosc_tablic);

