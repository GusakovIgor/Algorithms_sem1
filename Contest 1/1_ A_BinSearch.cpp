#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

bool BinSearch (int* ar_begin, int* ar_end, int target);

int main()
{
    int N = 0;
    scanf("%d", &N);
    
    int* Arr = (int*) calloc(N, sizeof(int));
    assert (Arr != NULL);
    
    for (int i = 0; i < N; i++)
    {
        scanf("%d", Arr + i);
    }
    
    int Q = 0;
    scanf("%d", &Q);
    
    int ar_begin = 0;
    int ar_end = 0;
    int target = 0;
    
    for (int i = 0; i < Q; i++)
    {
        scanf("%d", &ar_begin);
        scanf("%d", &ar_end);
        scanf("%d", &target);
        if (BinSearch((Arr + ar_begin), (Arr + ar_end), target) == true)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    
    return 0;
}



bool BinSearch (int* ar_begin, int* ar_end, int target)
{
    int* mid = ar_begin + (ar_end - ar_begin)/2;
    
    if (*(ar_end - 1) < target)
    {
        return false;
    }
    
    if (ar_end - ar_begin == 1)
    {
        return (*ar_begin == target);
    }
    
    if (*mid == target)
    {
        return true;    
    }
    
    if (*mid > target)
    {
        if (BinSearch (ar_begin, mid, target) == true)
        {
            return true;
        }
    }
    
    if (*mid < target)
    {
        if (BinSearch (mid, ar_end, target) == true)
        {
            return true;
        }
    }
    
}
