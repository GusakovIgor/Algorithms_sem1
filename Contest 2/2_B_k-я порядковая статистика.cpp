#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long int BigInt;

BigInt FindK(BigInt* array, int left, int right, int k);
int partition(BigInt* array, int left, int right);
void Swap(BigInt* first, BigInt* second);


int main() {
    int n = 0, k = 0;
    scanf("%d %d", &n, &k);
    BigInt* array = (BigInt*)calloc(n, sizeof(BigInt));
    scanf("%lld %ldd", array, array + 1);
    for (int i = 2; i < n; i++) {
        array[i] = (array[i - 1] * 123 + array[i - 2] * 45) % (10000000 + 4321);
    }
    BigInt result = FindK (array, 0, n - 1, k - 1);
    printf ("%lld\n", result);
    return 0;
}

BigInt FindK(BigInt* array, int left, int right, int k) {   
    int mid = partition (array, left, right);
    if (k == mid) {
        return array[mid];
    } else if (k < mid) {
        FindK (array, left, mid, k);
    } else {
        FindK (array, mid + 1, right, k);
    }
}

int partition(BigInt* array, int left, int right) {
  Swap((array + left), (array + (left+right)/2));
  int last = left;
  for (int i = left + 1; i <= right; i++) {
    if (array[left] > array[i]) {
      last++;
      Swap((array + last), (array + i));
    }
  }
  Swap((array + left), (array + last));
  return last;
}

void Swap(BigInt* first, BigInt* second) {
  BigInt temp = *second;
  *second = *first;
  *first = temp;
}
