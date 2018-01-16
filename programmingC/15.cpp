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

int n,m;
int a[2020],b[2020];
bool dp[2020][2020];

int main(){
	cin>>n;
  rep(i,n)cin>>a[i];
  cin>>m;
  rep(i,m)cin>>b[i];
  dp[0][0]=true;
  rep(i,n)rep(j,2001){
    if(dp[i][j])dp[i+1][j]=true;
    if(j+a[i]<2020&&dp[i][j])dp[i+1][j+a[i]]=true;
  }
  rep(i,m){
    if(dp[n][b[i]])cout<<"true"<<endl;
    else cout<<"false"<<endl;
  }
	return 0;
}