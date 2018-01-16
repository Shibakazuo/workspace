#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define repl(i, a, b) for(ll i=(ll)(a); i<(ll)(b); i++)
#define rep(i, n) repl(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define dbg(x) cout << #x"=" << x << endl
#define mmax(x, y) (x > y ? x : y)
#define mmin(x, y) (x < y ? x : y)
#define maxch(x, y) x = mmax(x, y)
#define minch(x, y) x = mmin(x, y)

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

struct edge{
  ll f,t,c;
};
bool operator<(const edge& a,const edge& b){return a.c < b.c;}

int n;
int m[101][101];
vector<edge> es;

int main(){
	cin >> n;
  rep(i , n) {
      rep(j, n) {
        int c;
        cin >> c;
        if(c == -1) continue;
        es.push_back((edge){i, j, c});
      }
  }
  sort(all(es));
  UnionFind uf(n);
  int res=0;
  rep(i, es.size()){
    edge e = es[i];
    if(uf.same(e.f,e.t)) continue;
    uf.unite(e.f, e.t);
    res += e.c;
  }
  cout << res << endl;
	return 0;
}