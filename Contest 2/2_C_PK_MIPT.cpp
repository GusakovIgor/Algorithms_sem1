#include <stdio.h>
#include <stdlib>

int main ()
{
    int N = 0;
    scanf ("%d", N);
    
    const int max_surname_length = 100;
    const int max_name_length    = 100;
    
    char* surname = (char*) calloc (max_surname_length, sizeof(char));
    char*    name = (char*) calloc (   max_name_length, sizeof(char));
    
    int* sum = (int*) calloc (N, sizeof(int));
    
    int inf = 0, math = 0, rus = 0;
    for (int i = 0; i < N; i++)
    {
        scanf ("%d %d %d", &inf, &math, &rus);
        sum[i] = inf + math + rus;
    }
    
    return 0;
}
