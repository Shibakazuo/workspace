#include <iostream>
#include <cstdlib>
#include <vector> 
#include <cstring>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define repl(i,a,b) for(ll i=(ll)(a);i<(ll)(b);i++)
#define rep(i,n) repl(i,0,n)
#define each(itr,v) for(auto itr:v)
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout<<#x"="<<x<<endl
#define mmax(x,y) (x>y?x:y)
#define mmin(x,y) (x<y?x:y)
#define maxch(x,y) x=mmax(x,y)
#define minch(x,y) x=mmin(x,y)
#define uni(x) x.erase(unique(all(x)),x.end())
#define exist(x,y) (find(all(x),y)!=x.end())

string s;
 
int main(){
	char button[9][5]={
		{'.', ',', '!', '?', ' '},
		{'a', 'b', 'c'},
		{'d', 'e', 'f'},
		{'g', 'h', 'i'},
		{'j', 'k', 'l'},
		{'m', 'n', 'o'},
		{'p', 'q', 'r', 's'},
		{'t', 'u', 'v'},
		{'w', 'x', 'y', 'z'},
	};
    int n;
    cin >> n;
    while(n--){
        cin >> s;
        string res;
        int i = 0;
        while(1){
            while(i < s.length() && s[i] == '0') i++;
            if(i == s.length()) break;
            int cnt = 0;
            while(i < s.length() && s[i] != '0') cnt++, i++;
            int k=s[i - 1] - '1';
            int r;
            if(k == 0) r = 5;
            else if(k == 6 || k == 8) r = 4;
            else r = 3;
            res += button[k][(cnt - 1) % r];
        }
        cout << res << endl;
    }
    return 0;
}

