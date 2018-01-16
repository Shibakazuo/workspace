#include <stdio.h>

int dp[][20];

int comb(int n, int r){
    if(n==r) return 1;
    else if(r==0)return 1;
    else if(r==1)return n;
    else if(dp[r][n]!=0) return dp[r][n];
    else return dp[r][n]=comb(n-1, r-1)+comb(n-1, r);
    
}


int main(){
//Dataの読み込み
    int M,N;
    scanf("%d %d", &M, &N);
    int i, j;
    for(i=0; i<N; i++){
        for(j=0;j<M; j++){
            dp[N][M] = 0;
        }
    }
    printf("%d\n", comb(M+N-1, M));
    return 0;
}
