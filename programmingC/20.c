#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
  int N, i, j;
  int *A;
  int tmp;
  int flag, ct = 0;
 
  scanf("%d", &N);
 
  A = (int *)malloc(sizeof(int) * N);
 
  for (i = 0; i < N; i++) scanf("%d", &A[i]);
 
  flag = 1;
  while (flag) {
    flag = 0;
    for (j = N - 1; j > 0; j--) {
      if (A[j] > A[j-1]) {
        tmp = A[j];
        A[j] = A[j-1];
        A[j-1] = tmp;
        ct++;
        flag = 1;
      }
    }
  }
 /*
  for (i = 0; i < N; i++) {
    if (i != N - 1) printf("%d ", A[i]);
    else printf("%d\n", A[i]);
  }
  */
  printf("%d\n", ct);
 
  free(A);
 
  return 0;
}