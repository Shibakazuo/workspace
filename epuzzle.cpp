#include <bits/stdc++.h>

// using namespace std;

struct state {
    int puzzle[9];
    int depth;
    int cost;
    bool operator>(const state &s) const {
        return cost > s.cost;
    }
};

state start = { {2, 5, 3,
                1, 6, 0,
                7, 4, 8},
                0,
                0};
state goal = { {1, 2, 3,
                 8, 0, 4,
                 7, 6, 5}, // puzzle
                0,           // depth
                0};        // cost
std::priority_queue <state, std::vector<state>, std::greater<state> > open;
std::stack<state> open2;
std::vector<state> closed;
int count = 0;
int max = 0;

bool IsFinished(state s)
{
    for (int i = 0; i < 8; i++) {
       if (s.puzzle[i] != goal.puzzle[i]) {
           return false;
       } 
    }
    return true;
}

int ManhattanOne(int n, int place)
{
    if (goal.puzzle[n] == 0) {
        return 0;
    }
    int q, r;
    q = abs(place / 3 - n / 3);
    r = abs(place % 3 - n % 3);
    return q + r;
}

int manhattan(state s)
{
    int eval = 0;
    std::map<int, int> goalplace;
    for (int i = 0; i < 9; i++) {
        goalplace[goal.puzzle[i]] = i;
    }
    for (int i = 0; i < 9; i++) {
        eval += ManhattanOne(goalplace[s.puzzle[i]], i);
    }
    return eval;
}

int SamePuzzleCost(state s)
{
    int eval = 0;
    for (int i = 0; i < 9; i++) {
        if (s.puzzle[i] != 0 and s.puzzle[i] != goal.puzzle[i]) {
            eval++;
        }
    }
    return eval;
}

void PrintState(state s)
{
    std::cout << '|' << s.puzzle[0] << '|' << s.puzzle[1] << '|' << s.puzzle[2] << '|' << ' ' << count << std::endl;
    std::cout << '|' << s.puzzle[3] << '|' << s.puzzle[4] << '|' << s.puzzle[5] << '|' << " f(n) = " << s.cost << std::endl;
    std::cout << '|' << s.puzzle[6] << '|' << s.puzzle[7] << '|' << s.puzzle[8] << '|' << " g(n) = " << s.depth << std::endl << std::endl;
    return;
}

bool IsSamePuzzle(state s1, state s2)
{
    for (int i = 0; i < 9; i++) {
        if (s1.puzzle[i] != s2.puzzle[i]) {
            return false;
        }
    }
    return true;
}

bool InClosed(state s)
{
    for (int i = 0; i < closed.size(); i++) {
        if (IsSamePuzzle(s, closed[i])) {
            return true;
        }
    }
    return false;
}

void shuffle() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 9; i++){
        int k = rand() % 3; 
        std::swap(start.puzzle[i], start.puzzle[k]);
    }
}


void AStar()
{
    if (open.empty()) {
        std::cerr << "Search have mistakenly stopped!" << std::endl;
    }
    if (max < open.size() + closed.size()) {
        max = open.size() + closed.size();
    }
    count++;
    state now = open.top();
    open.pop();
    PrintState(now);
    closed.push_back(now);
    if (IsFinished(now)) {
        std::cout << "Finished!" << std::endl;
        return;
    }
    state s = now;    
    int zero;
    for (int i = 0; i < 9; i++) {
        if (now.puzzle[i] == 0) {
            zero = i;
            break;
        }
    }
    if (zero - 3 >= 0) {
        std::swap(s.puzzle[zero - 3], s.puzzle[zero]);
        if (not InClosed(s)) {
            s.depth++;
            s.cost = SamePuzzleCost(s) + s.depth;
            open.push(s);
        }
        s = now;
    }
    if (zero % 3 != 0) {
        std::swap(s.puzzle[zero - 1], s.puzzle[zero]);
        if (not InClosed(s)) {
            s.depth++;
            s.cost = SamePuzzleCost(s) + s.depth;
            open.push(s);
        }
        s = now;
    }
    if (zero % 3 != 2) {
        std::swap(s.puzzle[zero + 1], s.puzzle[zero]);
        if (not InClosed(s)) {
            s.depth++;
            s.cost = SamePuzzleCost(s) + s.depth;
            open.push(s);
        }
        s = now;
    }
    if (zero + 3 < 9) {
        std::swap(s.puzzle[zero + 3], s.puzzle[zero]);
        if (not InClosed(s)) {
            s.depth++;
            s.cost = SamePuzzleCost(s) + s.depth;
            open.push(s);
        }
    }
    AStar();
    return;
}

// void IDAStar_rep(std::function<int(state)> fun, int c)
// {
//     if (open2.empty()) {
//         std::cout << c << " roop end" << std::endl;
//         c++;
//         open2.push(start);
//         closed.clear();
//         IDAStar_rep(fun, c);
//         return;
//     }
//     if (max < open2.size() + closed.size()) {
//         max = open2.size() + closed.size();
//     }
//     state now = open2.top();
//     closed.push_back(now);
//     open2.pop();
//     count++;
//     if (IsFinished(now)) {
//         PrintState(now);
//         std::cout << "Finished!" << std::endl;
//         return; 
//     }
//     state s = now;
//     PrintState(now);
//     int zero;
//     for (int i = 0; i < 9; i++) {
//         if (now.puzzle[i] == 0) {
//             zero = i;
//             break;
//         }
//     }
//     if (zero - 3 >= 0) {
//         std::swap(s.puzzle[zero - 3], s.puzzle[zero]);
//         if (not InClosed(s)) {
//             s.depth++;
//             s.cost = fun(s) + s.depth;
//             if (s.cost <= c) {
//                 open2.push(s);
//             }
//         }
//         s = now;
//     }
//     if (zero % 3 != 0) {
//         std::swap(s.puzzle[zero - 1], s.puzzle[zero]);
//         if (not InClosed(s)) {
//             s.depth++;
//             s.cost = fun(s) + s.depth;
//             if (s.cost <= c) {
//                 open2.push(s);
//             }
//         }
//         s = now;
//     }
//     if (zero % 3 != 2) {
//         std::swap(s.puzzle[zero + 1], s.puzzle[zero]);
//         if (not InClosed(s)) {
//             s.depth++;
//             s.cost = fun(s) + s.depth;
//             if (s.cost <= c) {
//                 open2.push(s);
//             }
//         }
//         s = now;
//     }
//     if (zero + 3 < 9) {
//         std::swap(s.puzzle[zero + 3], s.puzzle[zero]);
//         if (not InClosed(s)) {
//             s.depth++;
//             s.cost = fun(s) + s.depth;
//             if (s.cost <= c) {
//                 open2.push(s);
//             }
//         }
//         s = now;
//     }
//     IDAStar_rep(fun, c);
//     return;
// }

// void IDAStar(std::function<int(state)> fun)
// {
//     IDAStar_rep(fun, open2.top().cost);
//     return;
// }

int main()
{
    start.cost = SamePuzzleCost(start);
    shuffle();
    PrintState(start);
    open.push(start);
    AStar();
    std::cout << "start from :" << std::endl;
    PrintState(start);
    std::cout << "status: " << max << std::endl;

    return 0;
}