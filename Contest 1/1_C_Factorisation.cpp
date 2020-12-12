#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void PrimeDevisorsGetter (int number);

int main()
{
    int number = 0;
    
    const int MIN_NUMBER = 2;
    const int MAX_NUMBER = 1000000000;
    
    int N = 0;
    scanf ("%d", &N);
    
    for (int i = 0; i < N; i++)
    {
        scanf ("%d", &number);
        assert (number >= MIN_NUMBER);
        assert (number <= MAX_NUMBER);
        
        PrimeDevisorsGetter (number);
    }
    
    return 0;
}


void PrimeDevisorsGetter (int number)
{
    while (number % 2 == 0)
    {
        printf ("2 ");
        number = number / 2;
    }
    
    for (int dev = 3; dev*dev <= number; dev += 2)
    {
        while (number % dev == 0)
        {
            printf ("%d ", dev);
            number = number / dev;
        }
    }
    
    if (number != 1)
    {
        printf("%d ", number);
    }
}
