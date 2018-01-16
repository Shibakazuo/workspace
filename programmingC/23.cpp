#include <iostream>
#include <cstdlib>
#include <vector> 
#include <string>
#include <cmath>
#include <time.h>
#include <stack>
#include <queue>
#include <array>
#include <algorithm>

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

#define INF INT_MAX/3

int A[2000000], B[20000];
int n, maxn;

void csort() {
  rep(i, n) {
    B[A[i]]++;
    maxch(maxn, A[i]);
  }
  cout << B[0];
  repl(i, 1, maxn+1){
    cout << " " << B[i];
  }
  cout << endl;
  sort(A, A+n);
  reverse(A, A+n);
}

int main() {
  cin >> n;
  rep(i, n) cin >> A[i];
  csort();
  cout << A[0];
  repl(i, 1, n) cout << " " << A[i];
  cout << endl;
  return 0;
}