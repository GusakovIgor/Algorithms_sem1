#include <stdio.h>
#include <stdlib.h>

const int max_time = 1000000;
const int two = 2;

int FindMinDevices(int* time, const int max_time);
int TimeMarker(int* time, int number);

int main() {
  int N = 0;
  scanf("%d", &N);
  int* time = (int*)calloc(two*max_time, sizeof(int));
  int max_time = TimeMarker(time, N);
  int result = FindMinDevices(time, max_time);
  printf("%d", result);
  return 0;
}

int TimeMarker(int* time, int number) {
  int T = 0; 
  int L = 0;
  int max_time = 0;
  for (int i = 0; i < number; i++) {
    scanf("%d %d", &T, &L);
    time[T] += 1;
    time[T + L] -= 1;
    if (T + L > max_time)
      max_time = T + L;
  }
  return max_time;
}

int FindMinDevices(int* time, const int max_time) {
  int num_devices = 0;
  int sum = 0;
  for (int i = 0; i < max_time; i++) {
    sum += time[i];
    if (sum > num_devices)
      num_devices = sum;
  }
  return num_devices;
}
