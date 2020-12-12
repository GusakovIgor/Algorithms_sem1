#include <stdio.h>
#include <stdlib.h>

int MyQuickSort(int* sarray, int left, int right);
void Swap(int* first, int* second);

int main() {
  int N = 0;
  scanf("%d", &N);
  int* array = (int*)calloc (N, sizeof(int));
  for (int i = 0; i < N; i++) {
    scanf ("%d", array + i);
  }
  MyQuickSort (array, 0, N - 1);
  for (int i = 0; i < N; i++) {
    printf ("%d\n", array[i]);
  }
  return 0;
}

int MyQuickSort(int* sarray, int left, int right) {   
  if (right - left <= 0) {
    return 0;
  }
  if (right - left == 1) {
    if (sarray[left] > sarray[right]) {
      Swap(sarray + left, sarray + right);
  }
    return 0;
  }
  Swap((sarray + left), (sarray + (left + right) / 2));
  int last = left;
  for (int i = left + 1; i <= right; i++) {
    if (sarray[left] > sarray[i]) {
      last++;
      Swap((sarray + last), (sarray + i));
  }
  }
  Swap((sarray + left), (sarray + last));
  if (right - left <= 0) {
    return 0;
  }
  if (right - left == 1) {
    if (sarray[left] > sarray[right]) {
      Swap(sarray + left, sarray + right);
  }
    return 0;
  }
  MyQuickSort(sarray, left, last);
  MyQuickSort(sarray, last + 1, right);
}

void Swap(int* first, int* second) {

    printf ("elements:  first[1] = %d\n",  *first);
    printf ("          second[1] = %d\n", *second);
    
  int temp = *second;
  *second  = *first;
  *first   = temp;
}
