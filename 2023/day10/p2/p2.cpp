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

vector<vector<char>> g;
unordered_map<int, unordered_set<int>> adj;
pair<int, int> startPos;
vector<bool> visited;
vector<int> group;
int groupIndex = 0;
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
unordered_set<int> mainLoop;

// flatten 2d array
int v(int r, int c) { return r * g[0].size() + c; }

pair<int, int> coordinate(int v) { return {v / g[0].size(), v % g[0].size()}; }

int dfs(int first) {
    int count = 0;
    vector<int> s;
    s.PB(first);
    while (!s.empty()) {
        int v = s.back();
        s.pop_back();
        count++;
        visited[v] = true;
        group[v] = groupIndex;
        // pair<int, int> coordinateV = coordinate(v);
        // if (g[coordinateV.F][coordinateV.S] != '|')
        mainLoop.insert(v);
        for (auto n : adj[v]) {
            if (count > 2 && n == first) {
                return ceil(count / 2.0);
            }
            if (visited[n])
                continue;
            s.PB(n);
        }
    }
    return -1;
}

int dfs2(int first) {
    int count = 0;
    int nCol = g[0].size();
    int dc[4] = {nCol, -nCol, 1, -1};
    vector<int> s;
    s.PB(first);
    while (!s.empty()) {
        int v = s.back();
        s.pop_back();
        count++;
        visited[v] = true;
        group[v] = groupIndex;
        for (int i = 0; i < 4; i++) {
            int neighbor = v + dc[i];
            if (neighbor < 0 || neighbor >= visited.size() || visited[neighbor])
                continue;
            s.PB(neighbor);
        }
    }
    return count;
}

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

bool isInside(int v) {
    // explain
    // https://cses.fi/book/book.pdf III. Advanced Topics > Geometry > Point
    int count = 0;
    int nCol = g[0].size();
    // cout << v / nCol << " " << v % nCol << " "; 
    while (v <= g[0].size()) {
        if (mainLoop.find(v) != mainLoop.end())
            count++;
        v++;
    }
    // cout << count % 2 << endl;
    return count % 2;
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
                startPos.F = r;
                startPos.S = c;
                processAdj(r, c);
                break;
            default:
                throw invalid_argument("Not implemented yet");
            }
        }
    }
    int ans = 0;
    // find main loop aka groupIndex 0
    if (dfs(v(startPos.F, startPos.S)) == -1)
        throw invalid_argument("Cannot find main loop");
    for (int r = 0; r < g.size(); r++) {
        for (int c = 0; c < g[0].size(); c++) {
            if (visited[v(r, c)])
                continue;
            groupIndex++;
            // check inside main loop v(r,c) - first vertice of group
            // find all other groups
            int size = dfs2(v(r, c));
            // if v(r,c) inside main loop
            // ans += size;
            if (isInside(v(r, c))) {
                cout << groupIndex << " inside " << size << endl;
                ans += size;
            }
        }
    }

    // visual
    for (int r = 0; r < g.size(); ++r) {
        for (int c = 0; c < g[0].size(); ++c) {
            if (group[v(r, c)] == 0) {
                cout << '*';
            } else
                cout << group[v(r, c)];
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
    group.resize(g.size() * g[0].size(), -1);
    vector<int> F(100, -1);
    cout << solve() << endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    return 0;
}
