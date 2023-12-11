#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

// Macros
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a) * (a)

vector<vector<int>> histories;
/*
     0 1 2 3 4  5
   0 0 3 6 9 12 15 18
   1   3 3 3 3  3  3
   2     0 0 0  0  0
   3       0 0  0
   4         0  0
   5            0  0
 * */
struct hashFunction {
    size_t operator()(const pair<int, int> &x) const {
        return x.first ^ x.second;
    }
};

ll bfs(vector<int> h) {
    // int F[h.size()][h.size()];
    vector<vector<ll>> F(h.size(), vector<ll>(h.size() + 1, 0));
    queue<pair<int, int>> q;
    q.push({0, h.size() - 1});
    unordered_set<pair<int, int>, hashFunction> visited;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        if (visited.find(v) != visited.end())
            continue;
        visited.insert(v);
        if (v.first == 0) {
            F[v.first][v.second] = h[v.second];
        } else {
            F[v.first][v.second] =
                F[v.first - 1][v.second] - F[v.first - 1][v.second - 1];
        }
        if (v.second > v.first) {
            q.push({v.first, v.second - 1});
            q.push({v.first + 1, v.second});
        }
    }
    vector<int> mostLeft(h.size(), 0);
    mostLeft[h.size() - 1]= 0;
    for (int row = h.size()-2; row >= 0; row--) {
        mostLeft[row] = F[row][row] - mostLeft[row + 1];
    }
    return mostLeft[0];
}

ll solve() {
    ll ans = 0;
    for (auto history : histories) {
        // calc history
        ans += bfs(history);
    }
    return ans;
}

void parse() {
    freopen("input.txt", "r", stdin);
    string l;
    while (getline(cin, l)) {
        l += ' ';
        int start = 0;
        int size;
        vector<int> history;
        while ((size = l.find(' ', start)) != string::npos) {
            string h = l.substr(start, size - start);
            history.PB(stoi(h));
            start = size + 1;
        }
        histories.PB(history);
    }
    fclose(stdin);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    parse();
    cout << solve() << endl;

    return 0;
}
