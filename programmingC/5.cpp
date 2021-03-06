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

struct query
{
  string name;
  int rest;
};

void show_query(query q){
  cout<<q.name<<" "<<q.rest<<endl;
}

void show_queue(queue<query> que){
  while(que.size()){
    show_query(que.front()); que.pop();
  }

}

int n,t;
queue<query> q;

int main(){
	cin>>n>>t;
  rep(i,n){
    string a;
    int b;
    cin>>a>>b;
    q.push((query){a,b});
  }
  int nt=0;
  while(q.size()){
    query nq=q.front(); q.pop();
    if(nq.rest<=t){
      nt+=nq.rest;
      cout<<nq.name<<" "<<nt<<endl;
    }else{
      nq.rest-=t;
      nt+=t;
      q.push(nq);
    }
    show_queue(q);
  }

	return 0;
}