#include <bits/stdc++.h>
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

ll n;
ll a[101010];

ll dfs(ll l,ll r){
  if(l>=r)return -INF;
  if(l+1==r){
    cout<<a[l]<<endl;
    return a[l];
  }
  ll res=max(dfs(l,(l+r)/2),dfs((l+r)/2,r));
  cout<<res<<endl;
  return res;
}

int main(){
	cin>>n;
  rep(i,n)cin>>a[i];
  dfs(0,n);
	return 0;
}