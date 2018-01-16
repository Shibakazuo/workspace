#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;

#define repl(i,a,b) for(ll i=(ll)(a);i<(ll)(b);i++)
#define rep(i,n) repl(i,0,n)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout<<#x"="<<x<<endl
#define mmax(x,y) (x>y?x:y)
#define mmin(x,y) (x<y?x:y)
#define maxch(x,y) x=mmax(x,y)
#define minch(x,y) x=mmin(x,y)

ll n;
ll m[100][100];
vector<int> g[100];

int main(){
	cin >> n;

    rep(i, n) {
    	rep(j, n) {
    		cin >> m[i][j];
    	}
    }
    rep(i, n) {
    	rep(j, n) {
    		if(m[i][j]) {
	  	      g[i].push_back(j);
	  	  	}
		}
 	}

    rep(i,n){
	    sort(all(g[i]));
	    cout << i+1 << " " << g[i].size();
	    rep(j, g[i].size()) cout << " " << g[i][j]+1;
	    cout << endl;
  	}
	return 0;
}