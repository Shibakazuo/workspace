#include <iostream>
#include <cstdlib>
#include <vector> 
#include <string>
#include <cmath>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define repl(i,a,b) for(ll i=(ll)(a);i<(ll)(b);i++)
#define rep(i,n) repl(i,0,n)
#define each(itr,v) for(auto itr:v)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout<<#x"="<<x<<endl
#define mmax(x,y) (x>y?x:y)
#define mmin(x,y) (x<y?x:y)
#define maxch(x,y) x=mmax(x,y)
#define minch(x,y) x=mmin(x,y)
#define uni(x) x.erase(unique(all(x)),x.end())
#define exist(x,y) (find(all(x),y)!=x.end())
#define bcnt __builtin_popcount

int cnt = 0, m, n;


int solve(int i, int k, int max){
	// dbg(i);
	if(i > max) max = i;
	// dbg(max);
	if(max == n) {
		cnt += pow(2,m-k);
		max = 0;
		k = m;
		return i;
		// dbg(cnt);
	}
	if(k == m) return i;
	k++;
	solve(0, k, max);
	solve(i+1, k, max);
}

int main() {
	cin >> m >>n;
	solve(0, 0, 0); 
	cout << cnt << endl;
}