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

#define QSIZE 100
#define SIZE 10

int isEmpty(void);
int compare(int y,int x,int cnt);
struct position{
  int horizontal;
  int vertical;
};
void enqueue(struct position data);
struct position dequeue(void);
int front = 0;
int rear = 0;
struct position que[QSIZE];
struct position temp;
int mapn[SIZE+2][SIZE+2];
char a[SIZE+2][SIZE+2];

int main(){
  int sx,sy;
  rep(i, SIZE+2){
    rep(j, SIZE+2){
      if(j==0 || i==0 || i==SIZE+1 || j==SIZE+1){
        a[i][j] = '#';
      }else{
      	cin >> a[i][j];
        if(a[i][j] == '\n') cin >> a[i][j];
        mapn[i][j] = 0;
        if(a[i][j] == 'S'){
          sx = j;
          sy = i;
        }
      }
    }
  }
  mapn[sy][sx]=1;
  temp.vertical=sy;
  temp.horizontal=sx;
  enqueue(temp);
  while(!isEmpty()){
    temp=dequeue();
    int i=temp.vertical;
    int j=temp.horizontal;
    if(compare(i+1,j,mapn[i][j])==0){
      break;
    };
    if(compare(i,j-1,mapn[i][j])==0){
      break;
    };
    if(compare(i,j+1,mapn[i][j])==0){
      break;
    };
    if(compare(i-1,j,mapn[i][j])==0){
      break;
    };
  }
   return 0;
}
void enqueue(struct position data){
  que[rear++]=data;
}
struct position dequeue(void){
  return que[front++];
}
int isEmpty(void){
  return (front==rear);
}
int compare(int y,int x,int cnt){
  if(a[y][x]=='G'){
  	cout << cnt << endl;
    return 0;
  }
  if(a[y][x] != '#' && mapn[y][x] == 0){
    mapn[y][x] = cnt+1;
    temp.vertical = y;
    temp.horizontal = x;
    enqueue(temp);
  }
  return 1;
}