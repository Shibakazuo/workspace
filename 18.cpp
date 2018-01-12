#include <iostream>
#include <cstdlib>
#include <vector> 
#include <string>
#include <cmath>

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

ll n,cnt = 0;
ll A[1000000], L[1000000], R[1000000];



ll merge(ll left,ll mid,ll right){
    ll n1 = mid - left;
    ll n2 = right - mid;
    rep(i, n1){
      L[i] = A[left + i];
    }
    rep(i, n2){
      R[i] = A[mid + i];
    }
    L[n1] = -9999999;
    R[n2] = -9999999;
    int j = 0, i = 0;
    for (int k = left; k < right; k++){
      if (L[i] >= R[j]){
        A[k] = L[i];
        i++;
      } else {
        A[k] = R[j];
        j++;
      }
    }
} 
ll mergeSort(ll left,ll right){
  ll mid;
  if (left+1 < right){
    mid = (left + right)/2;
    mergeSort( left, mid);
    mergeSort( mid, right);
    cnt++;
    merge( left, mid, right);
  }
}

int main(){
  ll left, right;
  cin>>n;
  rep(i,n)cin>>A[i];
  mergeSort(0, n);
  rep(i,n-1) cout << A[i] << ' ';
  cout << A[n-1] <<endl << cnt << endl ;

  return 0;
}