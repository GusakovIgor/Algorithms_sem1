#include <stdio.h>
#include <stdlib.h>

typedef long long int big_int;

int main ()
{
    //printf ("sizeof (big_int) = %d\n", sizeof (big_int));
    //printf ("sizeof (big_int*) = %d", sizeof (big_int*));
    
    int number = 0;
    scanf ("%d", &number);
    
    if (number > 0)
    {
        big_int* array = (big_int*) calloc (number, sizeof(big_int));
        
        for (int i = 0; i < number; i++)
        {
            scanf ("%lld", array + i);
        }
        
        unsigned char* A = (unsigned char*) array;
        
        int count = 0;
        for (int i = 0; i < number*sizeof(big_int); i++)
        {
            if (i % sizeof(big_int) == 0)
                printf ("\nbyte_%d = %d", ++count, A[i]);
            else
                printf (" %d", A[i]);
        }
    }
    
    return 0;
}
