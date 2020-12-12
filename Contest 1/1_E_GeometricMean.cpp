#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double GeometricMean(double* begin, double* end);

int main()
{
  int N = 0;
  scanf ("%d", &N);
  
  double* pref_sum = (double*)calloc(N + 1, sizeof(double));
  pref_sum[0] = 0;
  
  double elem = 0;
  for (int i = 1; i < N + 1; i++)
  {
    scanf ("%lg", &elem);
    pref_sum[i] = pref_sum[i - 1] + log(elem);
  }
  
  int Q = 0;
  scanf ("%d", &Q);
  
  int begin = 0;
  int end = 0;
  double result = 0;
  for (int i = 0; i < Q; i++)
  {
    scanf("%d %d", &begin, &end);
    result = GeometricMean(pref_sum + 1 + begin, pref_sum + 1 + end);
    printf ("%f\n", result);
  }
  
  return 0;
}

double GeometricMean(double* begin, double* end)
{
  size_t lenth = end - begin + 1;
  double log_sum = *(end) - *(begin - 1);
  
  return exp(log_sum / lenth);
}
