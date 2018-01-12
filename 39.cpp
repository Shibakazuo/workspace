#include <bits/stdc++.h>

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

int Z[1002][1002];
char X[1002], Y[1002];

int rec(int i,int j);
int max_z(int x,int y);
int main(){
  int i, j=1;

  cin >> X >> Y;
  dbg(strlen(X));
  dbg(strlen(Y));
  cout << rec(strlen(Y),strlen(X)) << endl;

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


