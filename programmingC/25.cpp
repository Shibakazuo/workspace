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

int n;
int a[200000];

int partition(int A[],int p,int r){
  int x = A[0];
  int i = p-1;
  int temp;
  for(int j = p; j < r; j++){
    if(A[j] <= x){
      i++;
      swap(A[i],A[j]);
    }
  }
  swap(A[i],A[0]);
  return i+1;
}

int main(){
  cin >> n;
  rep(i, n) cin >> a[i];
  int res = partition(a, 0, n);
  cout << a[0];
  repl(i, 1, n) cout << " " << a[i];
  cout << endl;
  cout << res << endl;
  return 0;
}