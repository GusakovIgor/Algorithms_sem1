#include <stdio.h>
#include <stdlib.h>

typedef long long int big_int;

int Max_Num_Digits (big_int array[], int number);

int digit (big_int element, int i);

void LSD_Sort (big_int array[], int number, int max_num);

int main()
{
    int number = 0;
    scanf ("%d", &number);
    
    if (number > 0)
    {
        big_int* array = (big_int*) calloc (number, sizeof(big_int));
        
        for (int i = 0; i < number; i++)
        {
            scanf ("%lld", array + i);
        }
        
        int max_num = Max_Num_Digits (array, number);
        
        LSD_Sort (array, number, max_num);
        
        for (int i = 0; i < number; i++)
        {
            printf ("%lld\n", array[i]);
        }
        
        free (array);
    }
    else
    {
        printf ("Incorrect number, please enter something >= 1");
    }
    
    return 0;
}

int Max_Num_Digits (big_int array[], int number)
{
    big_int temp = 0;
    size_t count = 0;
    size_t max_num = 0;
    
    for (int i = 0; i < number; i++)
    {
        count = 0;
        temp = array[i];
        while (temp > 0)
        {
            temp /= 10;
            count++;
        }
        if (count > max_num)
        {
            max_num = count;
        }
    }
    
    return max_num;
}

int digit (big_int element, int i)
{
    for (i; i > 1; i--)
    {
        element /= 10;
    }
    
    return (element % 10);
}

void LSD_Sort (big_int array[], int number, int max_num)
{
    const int max_num_category = 10;
    int count = 0;
    int temp = 0;
    int current_digit = 0;
    
    big_int* dist_array = (big_int*) calloc (number, sizeof(big_int));      // B
    int* num_digits = (int*) calloc (max_num_category, sizeof(int));        // C
    
    
    for (int i = 1; i <= max_num; i++)
    {
        for (int j = 0; j < max_num_category; j++)
        {
            num_digits[j] = 0;
        }
        
        for (int j = 0; j < number; j++)
        {
            current_digit = digit(array[j], i);
            num_digits[current_digit]++;
        }
        
        count = 0;
        for (int j = 0; j < max_num_category; j++)
        {
            temp = count;
            count += num_digits[j];
            num_digits[j] = temp;
        }
        
        for (int j = 0; j < number; j++)
        {
            current_digit = digit (array[j], i);
            dist_array[num_digits[current_digit]] = array[j];
            num_digits[current_digit]++;
        }
        
        for (int j = 0; j < number; j++)
        {
            array[j] = dist_array[j];
        }
        
    }
    
    free (num_digits);
    free (dist_array);
}
