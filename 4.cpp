#include <stdc++.h>
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

string s;
ll stoi(string str){
ll ret;
stringstream ss;
ss << str;
ss >> ret;
return ret;
}

void show_stack(stack<ll> st){
  vector<ll> tmp;
  while(st.size()){
    tmp.push_back(st.top());
    st.pop();
  }
  reverse(all(tmp));
  cout<<tmp[0];
  repl(i,1,tmp.size())cout<<" "<<tmp[i];
  cout<<endl;
}

int main(){
	getline(cin,s);
  ll n=s.size();
  stack<ll> st;
  rep(i,n){
    char c=s[i];
    if('0'<=c&&c<='9'){
      int j=i;
      while(j < n && '0' <= s[j] && s[j] <= '9')j++;
      st.push(stoi(s.substr(i,j-i)));
      i=j;
    }else if(c!='='){
      ll l=st.top();
      st.pop();
      ll r=st.top();
      st.pop();
      if(c=='+')st.push(l+r);
      if(c=='-')st.push(r-l);
      if(c=='*')st.push(l*r);
    }else break;
    i++;
    while(i<n&&s[i]==' ')i++;
    i--;
    show_stack(st);
  }
	return 0;
}