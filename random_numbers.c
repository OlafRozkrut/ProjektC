#include <stdlib.h>
#include <stdio.h>
#include <time.h>
const N=10;
//od tego zalezy ilosc liczb w tablicy
float rand_float()
{
    return((float)rand())/((double)RAND_MAX);
    // bierzemy przypadkowa liczbe i dzielimy ja przez stala rand_max
}
int compare(const void *x_void, const void *y_void)
{
    int x = *(int *)x_void;
    int y = *(int *)y_void;
    return x-y;
}
// funkcja porównuj¹ca
int main()
{
    float tab[N];
    srand(time(NULL));
    for(int i=0;i<N;i++)
        {
            tab[i]=rand_float();
            printf("%f\n", tab[i]);
        }
        //losujemy liczby
    printf("\n");
    qsort(tab, N, sizeof(float), compare);
        //sortujemy
    for(int j=0;j<N;j++)
        {
            printf("%f\n", tab[j]);
        }

    return 0;
}
