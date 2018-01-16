#include <btd/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;

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

#define INF INT_MAX/3

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}


int main () {
	ll n = 1;
	ll s[10000];
	ll res[1000];
	int j;
	
    cin >> n; 

	    while (n > 0){
    		for(ll i = 0 ; i < n ; i++) {
    			cin >> s[i];
    		}
    		qsort(s, n, sizeof(ll), compare); 
    		ll dd = 99999999;
    		for(ll k = 1; k < n; k++){
    			dd = dd > abs(s[k-1]-s[k]) ? abs(s[k-1]-s[k]) : dd;
    		} 
    		cout << dd;
    		cout << endl;
    		cin >> n;
    		j++;
	    }

}