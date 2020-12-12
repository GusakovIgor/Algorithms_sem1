#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double GeometricMean(const double* begin, const double* end);

int main () {
  int n = 0;
  scanf ("%d", &n);
  
  double* pref_sum = (double*)calloc(n + 1, sizeof(double));
  pref_sum[0] = 0;
  
  double elem = 0;
  for (int i = 1; i < n + 1; i++) {
    scanf ("%lg", &elem);
    pref_sum[i] = pref_sum[i - 1] + log(elem);
  }
  
  int q = 0;
  scanf ("%d", &q);
  
  int begin = 0;
  int end = 0;
  double result = 0;
  for (int i = 0; i < q; i++) {
    scanf ("%d %d", &begin, &end);
    result = GeometricMean(pref_sum + 1 + begin, pref_sum + 1 + end);
    printf ("%f\n", result);
  }
  
  return 0;
}

double GeometricMean( const double* begin, const double* end)
{
  size_t lenth = end - begin + 1;
  double log_sum = *(end) - *(begin - 1);
  
  return exp(log_sum / lenth);
}
