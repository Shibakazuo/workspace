#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define repl(i,a,b) for(ll i=(ll)(a);i<(ll)(b);i++)
#define rep(i,n) repl(i,0,n)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout<<#x"="<<x<<endl
#define mmax(x,y) (x>y?x:y)
#define mmin(x,y) (x<y?x:y)
#define maxch(x,y) x=mmax(x,y)
#define minch(x,y) x=mmin(x,y)

#define N 8
#define FREE -1
#define NOT_FREE 1



int row[N], col[N], dpos[2 * N - 1], dneg[2 * N - 1], flag = 0;
bool X[N][N];

void init() {
    rep(i,N){
        row[i] = FREE;
        col[i] = FREE;
    }
    rep(i, 2*N-1){
        dpos[i] = FREE;
        dneg[i] = FREE;
    }
}

void solve() {
    rep(i, N){
        rep(j, N) {
            if (X[i][j]) {
                if (row[i] != j) {
                    return;
                }
            }
        }
    }
    cout << "Yes" << endl;
    flag = 1;
}

void rec(int i) {
    if (i == N && flag == 0) {
        solve();
        return;
    }
    rep(j, N) {
        if (NOT_FREE == col[j] || NOT_FREE == dpos[i + j] || NOT_FREE == dneg[i - j + N - 1]) {
            continue;
        }
        row[i] = j;
        col[j] = dpos[i + j] = dneg[i - j + N - 1] = NOT_FREE;
        rec(i + 1);
        row[i] = col[j] = dpos[i + j] = dneg[i - j + N - 1] = FREE;
    }
}

int main() {
    init();
    char k;
    rep(i,N) {
        rep(j,N) {
            cin >> k;
            if (k == 'Q') {
                X[i][j] = true;
            } else {
                X[i][j] = false;
            }
        }
    }
    rec(0);
    if (flag == 0) {
        cout << "No" << endl;
    }
    return 0;
}