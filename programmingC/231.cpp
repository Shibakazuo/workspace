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

int n,maxn;
int a[2000001];
int cnt[20000];

int main(){
	cin>>n;
  rep(i,n)cin>>a[i];
  rep(i,n){
    cnt[a[i]]++;
    maxch(maxn,a[i]);
  }
  cout<<cnt[0];
  repl(i,1,maxn+1){
    cout<<" "<<cnt[i];
  }
  cout<<endl;
  sort(a,a+n);
  reverse(a,a+n);
  cout<<a[0];
  repl(i,1,n)cout<<" "<<a[i];
  cout<<endl;
	return 0;
}