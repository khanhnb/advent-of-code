#include <bits/stdc++.h>
#include <stdexcept>
#include <unordered_map>

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

vector<vector<char>> g;
unordered_map<int, unordered_set<int>> adj;
pair<int, int> startPos;

int v(int r, int c) { return r * g[0].size() + c; }

vector<bool> visited;
int start;

int dfs() {
    int count = 0;
    vector<int> s;
    s.PB(start);
    while (!s.empty()) {
        int v = s.back();
        s.pop_back();
        if (visited[v])
            continue;
        count++;
        visited[v] = true;
        for (auto n : adj[v]) {
            if (count > 2 && n == start) {
                return ceil(count / 2.0);
            }
            s.PB(n);
        }
    }
    return -1;
}

unordered_map<char, pair<int, int>> d = {
    {'T', {-1, 0}}, {'B', {1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}};
unordered_map<char, char> opositeDirection = {
    {'T', 'B'}, {'B', 'T'}, {'L', 'R'}, {'R', 'L'}};
unordered_map<char, unordered_set<char>> connected = {
    {'|', {'T', 'B'}},           // '|'
    {'-', {'L', 'R'}},           // '-'
    {'L', {'R', 'T'}},           // 'L'
    {'J', {'L', 'T'}},           // 'J'
    {'7', {'L', 'B'}},           // '7'
    {'F', {'B', 'R'}},           // 'F'
    {'S', {'T', 'B', 'R', 'L'}}, // 'S'
};
void processAdj(int r, int c) {
    // neighbors
    for (auto direction : connected[g[r][c]]) {
        int nr = r + d[direction].F;
        int nc = c + d[direction].S;
        // out of grid range
        if (nr < 0 || nc < 0 || nr >= g.size() || nc >= g[0].size())
            continue;
        char neighborChar = g[nr][nc];
        // not connected
        if (connected[neighborChar].find(opositeDirection[direction]) ==
            connected[neighborChar].end())
            continue;
        // connected
        adj[v(r, c)].insert(v(nr, nc));
        adj[v(nr, nc)].insert(v(r, c));
    }
}
int solve() {
    for (int r = 0; r < g.size(); ++r) {
        for (int c = 0; c < g[0].size(); ++c) {
            switch (g[r][c]) {
            case '|':
            case '-':
            case 'L':
            case 'J':
            case '7':
            case 'F':
                processAdj(r, c);
                break;
            case '.':
                break;
            case 'S':
                start = v(r, c);
                startPos.F = r;
                startPos.S = c;
                processAdj(r, c);
                break;
            default:
                throw invalid_argument("Not implemented yet");
            }
        }
    }
    // return dfs();
    int ans = dfs();
    for (int r = 0; r < g.size(); ++r) {
        for (int c = 0; c < g[0].size(); ++c) {
            if (!visited[v(r,c)]) cout << '.';
            else cout << g[r][c];
        }
        cout << endl;
    }
    return ans;
}

void parse() {
    string l;
    freopen("input.txt", "r", stdin);
    while (getline(cin, l)) {
        vector<char> row;
        for (char c : l) {
            row.PB(c);
        }
        g.PB(row);
    }
    fclose(stdin);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    parse();
    clock_t tStart = clock();
    visited.resize(g.size() * g[0].size(), false);
    cout << solve() << endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    return 0;
}
