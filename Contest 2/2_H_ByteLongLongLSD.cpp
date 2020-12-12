#include <stdio.h>
#include <stdlib.h>

typedef long long int BigInt;
typedef unsigned char BigChar;

int MaxNumDigits(BigInt array[], int number);
int Byte(const BigChar* array, int j, int i);
void LsdSort(BigChar* array, int number);

int main() {
  int number = 0;
  scanf ("%d", &number);
  if (number > 0) {
    BigInt* temp = (BigInt*) calloc (number, sizeof(BigInt));
    for (int i = 0; i < number; i++) {
      scanf("%lld", temp + i);
    }
    BigChar* array = (BigChar*)temp;
    LsdSort(array, number);
    temp = (BigInt*)array;
    for (int i = 0; i < number; i++) {
      printf ("\n%lld", temp[i]);
    }
    free(temp);
  }
  else {
    printf("Incorrect number, please enter something >= 1");
  }
  return 0;
}


int Byte (const BigChar* array, int j, int i) {
  return *(array + j*sizeof(BigInt) + i);
}

void LsdSort (BigChar* array, int number) {
  const int max_num_values = 256;
  const int max_num_bytes = 8;
  int current_byte = 0;
  int temp = 0;
  int count = 0;
  BigChar* dist_array  = (BigChar*) calloc (number, sizeof(BigInt));
  int*  byte_values = (int*)  calloc (max_num_values, sizeof(int));
  for (int i = 0; i < sizeof(BigInt); i++) {
    for (int j = 0; j < max_num_values; j++) {
      byte_values[j] = 0;
    }
    for (int j = 0; j < number; j++) {
      current_byte = Byte(array, j, i);
      byte_values[current_byte]++;
    }
    count = 0;
    for (int j = 0; j < max_num_values; j++) {
      temp = byte_values[j];
      byte_values[j] = count;
      count += temp;
    }
    for (int j = 0; j < number; j++) {
      current_byte = Byte(array, j, i);
      ((BigInt*) dist_array)[byte_values[current_byte]] = ((BigInt*) array)[j];
      byte_values[current_byte]++;
    }
    for (int j = 0; j < number; j++) {
      ((BigInt*) array)[j] = ((BigInt*) dist_array)[j];
    }
  }
  free(byte_values);
  free(dist_array);
}
