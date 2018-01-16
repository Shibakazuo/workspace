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

int n;
vector<int> g[101];
vector<int> x, y;
bool vis[101];

void dfs(int v){
  x.push_back(v+1);
  rep(i, g[v].size()){
    int nv = g[v][i];
    if(vis[nv])continue;
    dfs(nv);
  }
}

int main() {
  cin >> n;
  rep(i, n){
    int k;
    cin >> k;
    cin >> k;
    rep(j, k){
      int v;
      cin >> v;
      v--;
      g[i].push_back(v);
    }
    sort(all(g[i]));
  }

  dfs(0);

  memset(vis, 0, sizeof(vis));
  queue<int> que;
  que.push(0);
  vis[0] = true;
  while(que.size()){
    int v = que.front(); que.pop();
    y.push_back(v+1);
    rep(i, g[v].size()){
      int nv = g[v][i];
      if(vis[nv]) continue;
      vis[nv] = true;
      que.push(nv);
    }
  }

  cout << y[0];
  repl(i, 1, n)cout << " " << y[i];
  cout << endl;

  cout << x[0];
  repl(i, 1, n) cout << " " << x[i];
  cout << endl;

	return 0;
}