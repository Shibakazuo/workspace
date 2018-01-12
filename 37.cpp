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

int memo[31];

int cal(int x){
	if(x <= 1) return 1;
	if(memo[x] != 0) return memo[x];
	memo[x] = cal(x-1) + cal(x-2);
	return memo[x];

}
int main() {
	int n;
	cin >> n;
	rep(i,n) memo[i] = 0;
	cal(n);
	for(int i = 0; i < n; i++) cout << cal(i) << " ";
	cout << cal(n) << endl;
}