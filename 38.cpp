#include <bits/stdc++.h>
// #include <iostream>
// #include <cstdlib>
// #include <vector> 
// #include <string>
// #include <cmath>
// #include <time.h>
// #include <stack>
// #include <queue>
// #include <array>
// #include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;

#define repl(i,a,b) for(ll i = (ll) (a); i < (ll) (b); i++)
#define rep(i, n) repl(i, 0, n)
#define each(itr, v) for(auto itr : v)
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout << #x"=" << x << endl
#define mmax(x, y) (x > y ? x : y)
#define mmin(x, y) (x < y ? x : y)
#define maxch(x, y) x=mmax(x, y)
#define minch(x, y) x=mmin(x, y)

int dp[21][21];
char a[21][21];
int cal(int w, int h){
  if(a[h][w] == 'X') return 0;
  if(w == 1 || h == 1) return 1;
  dp[h][w] = cal(w, h-1) + cal(w-1, h);
  return dp[h][w];
}
int main(){
  int w,h; 
  cin >> w >> h;
  for(int i = 1;i <= h; i++){
    for(int j = 1;j <= w; j++){
      while(1){
        cin >> a[i][j];
        if(a[i][j]!='\n')break;
      }
    }
  }
  cout << cal(w,h) << endl;
  return 0;
}




