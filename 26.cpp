ll n;
ll a[201010];


ll f(ll l,ll r,ll& ans){
  if(l+1>=r)return 0;
  f(l,(l+r)/2,ans); f((l+r)/2,r,ans);
  ll mid=(l+r)/2;

  repl(i,l,mid){
    ll idx=upper_bound(a+mid,a+r,a[i])-a;
    ans+=idx-mid;
  }
  sort(a+l,a+r);

  cout<<ans<<endl;
  return ans;
}

int main(){
	cin>>n;
  rep(i,n)cin>>a[i];
  ll res=0;
  f(0,n,res);
	return 0;
}