#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;

#define repl(i,a,b) for(ll i = (ll) (a); i < (ll) (b); i++)
#define rep(i, n) repl(i, 0, n)
#define dbg(x) cout << #x"=" << x << endl


struct state{
	int puzzle[9];
	int cost; 
	int depth;
	bool operator>(const state &x) const {
        return cost > x.cost;
    }
};

state start =
{
	{2, 1, 3,
	 6, 8, 0,
	 5, 4, 7},
	 0, //cost
	 0  //depth
};
state goal =
{
	{6, 2, 4,
	 8, 7, 5,
	 1, 0, 3},
	 0,
	 0
};


priority_queue <state, vector<state>, greater<state>> open,tmp;
stack<state> open2;
vector <state> close;
int maxn = 0;


void shuffle() {
	srand((unsigned int)time(NULL));
	rep(i,9){
		int k = rand() % 3; 
		swap(start.puzzle[i], start.puzzle[k]);
	}
}

void output(state a) {
	rep(i, 3){
		rep(j, 3){
			cout << a.puzzle[i*3+j] << " ";
		}
		cout << endl;
	}
    cout << endl;
}

bool isFinished(state x) {
	rep(i, 9){
		if(x.puzzle[i] != goal.puzzle[i]) return false; 
	}
	return true;
}

bool isSamePuzzle(state x1, state x2)
{
    rep(i, 9) {
        if (x1.puzzle[i] != x2.puzzle[i]) {
            return false;
        }
    }
    return true;
}

int h1CalCost(state x) {
	int cost = 0;
	rep(i, 9){
		if(x.puzzle[i] != goal.puzzle[i] && goal.puzzle[i] > 0) cost++;//cnt cost
	} 
	return cost;
}

int funOne(int n, int place)
{
    if (goal.puzzle[n] == 0) {
        return 0;
    }
    int q, r;
    q = abs(place / 3 - n / 3);
    r = abs(place % 3 - n % 3);
    return q + r;
}

int h2CalCost(state x)
{
    int eval = 0;
    map<int, int> goalplace;
    for (int i = 0; i < 9; i++) {
        goalplace[goal.puzzle[i]] = i;
    }
    for (int i = 0; i < 9; i++) {
        eval += funOne(goalplace[x.puzzle[i]], i);
    }
    return eval;
}

bool isClosed(state x)
{
    for (int i = 0; i < close.size(); i++) {
        if (isSamePuzzle(x, close[i])) {
            return true;
        }
    }
    return false;
}


void AStar(function<int(state)> fun)
{
    if (maxn < open.size() + close.size()) {
        maxn = open.size() + close.size();
    }
    state now = open.top();
    open.pop();
    output(now);
    close.push_back(now);
    if (isFinished(now)) {
        cout << "succeed to find goal" << endl;
        return;
    }
    state x = now;    
    int zero;
    for (int i = 0; i < 9; i++) {
        if (now.puzzle[i] == 0) {
            zero = i;
            break;
        }
    }
    if (zero - 3 >= 0) {
        swap(x.puzzle[zero - 3], x.puzzle[zero]);
        if (! isClosed(x)) {
            x.depth++;
            x.cost = fun(x) + x.depth;
            open.push(x);
        }
        x = now;
    }
    if (zero % 3 != 0) {
        swap(x.puzzle[zero - 1], x.puzzle[zero]);
        if (! isClosed(x)) {
            x.depth++;
            x.cost = fun(x) + x.depth;
            open.push(x);
        }
        x = now;
    }
    if (zero % 3 != 2) {
        swap(x.puzzle[zero + 1], x.puzzle[zero]);
        if (! isClosed(x)) {
            x.depth++;
            x.cost = fun(x) + x.depth;
            open.push(x);
        }
        x = now;
    }
    if (zero + 3 < 9) {
        swap(x.puzzle[zero + 3], x.puzzle[zero]);
        if (! isClosed(x)) {
            x.depth++;
            x.cost = fun(x) + x.depth;
            open.push(x);
        }
    }
    AStar(fun);
    return;
}

int main() {
    function< int(state) > fun;

    fun = h2CalCost;

	// shuffle();
	start.cost = fun(start);
	open.push(start);
	
	AStar(fun);
    cout << "start from:" << endl; 
    output(start);
    cout << "Totally moved " << maxn << " times" << endl;
}	
