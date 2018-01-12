#include<stdio.h>

int Z[1002][1002];
char X[1002],Y[1002];
int rec(int i,int j);
int max_z(int x,int y);
int main(){
  int i,j=1;
  while(1){
    scanf("%c",&X[i]);
    if(X[i]=='\n'){
      i--;
      break;
    }
    i++;
  }
  while(1){
    scanf("%c",&Y[j]);
    if(Y[j]=='\n'){
      j--;
      break;
    }
    j++;
  }

  printf("%d %d %d\n",rec(i,j), i, j);
  return 0;
}
int rec(int i,int j){
  for(int y=0;y<=j;y++){
    for(int x=0;x<=i;x++){
      if(x==0||y==0){
        Z[x][y]=0;
      }else if(X[x]==Y[y]){
        Z[x][y]=Z[x-1][y-1]+1;
      }else{
        Z[x][y]=max_z(x,y);
      }
    }
  }
  return Z[i][j];
}
int max_z(int x,int y){
  if(Z[x-1][y-1]>=Z[x][y-1]&&Z[x-1][y-1]>=Z[x-1][y]){
    return Z[x-1][y-1];
  }else if(Z[x][y-1]>=Z[x-1][y]){
    return Z[x][y-1];
  }else{
    return Z[x-1][y];
  }
}