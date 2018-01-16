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

struct UnionFind{
  vector<int> v;
  UnionFind(int n) : v(n, -1) {}
  void init(){ for(int i = 0;i < v.size();i++)v[i]=-1; }
  int find(int x) { return v[x] < 0 ? x : v[x] = find(v[x]); }
  bool unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    if (-v[x] < -v[y]) swap(x, y);
    v[x] += v[y]; v[y] = x;
    return true;
  }
  bool root(int x) { return v[x] < 0; }
  bool same(int x, int y) { return find(x) == find(y); }
  int size(int x) { return -v[find(x)]; }
};


int dd[]={-1,0,1,0,-1};
int h,w;
string s[101];

int main(){
	while(1){
    cin>>w>>h;
    if(h==0)break;
    UnionFind uf(h*w);
    rep(i,h)cin>>s[i];
    rep(i,h)rep(j,w)rep(dir,4){
      int ni=i+dd[dir],nj=j+dd[dir+1];
      if(ni>=h||ni<0||nj>=w||nj<0)continue;
      if(s[i][j]!='#'&&s[ni][nj]!='#')uf.unite(i*w+j,ni*w+nj);
    }
    rep(i,h)rep(j,w){
      if(s[i][j]=='@'){
        cout<<uf.size(i*w+j)<<endl;
        break;
      }
    }
  }
	return 0;
}
