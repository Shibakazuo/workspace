#include <stdio.h>
#include <stdlib.h>

int count=0;

int partition(int *A,int p,int r){
 int x,i,temp;
 x=A[r];
 i=p-1;
 for(int j=p;j<=r-1;j++){
  if(A[j]>=x){
   i=i+1;
   temp=A[j];
   A[j]=A[i];
   A[i]=temp;
 }
 }
 temp=A[r];
 A[r]=A[i+1];
 A[i+1]=temp;
 count++;
 return i+1;
}

void quicksort(int *A,int p,int r){
int q;
if(p<r){
 q=partition(A,p,r);
 quicksort(A,p,q-1);
 quicksort(A,q+1,r);
}
}

int main(void){
int N;
int *A;

scanf("%d",&N);
A=(int *)malloc(sizeof(int)*N);

for(int i=0;i<N;i++){
 scanf("%d",&A[i]);
}

quicksort(A,0,N);

printf("%d",A[0]);
for(int i=1;i<N;i++){
printf(" %d",A[i]);
}
printf("\n");
printf("%d\n",count-1);

free(A);
return 0;
}