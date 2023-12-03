#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORR(i, a, b) for (int i = a; i >= b; i--)

bool isNumber(char c) { return '0' <= c && c <= '9'; }
bool isSymbol(char c) { return c != '.' && !isNumber(c); }

int solve() {
    int dx[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, -1, 1};
    int ans = 0;
    string l;
    vector<vector<char>> engine;
    vector<pair<int, int>> symbols;
    vector<pair<int, int>> components;
    int r = 0;
    while (getline(cin, l)) {
        vector<char> line;
        FOR(c, 0, l.size() - 1) {
            line.push_back(l[c]);
            if (!isSymbol(l[c]))
                continue;
            symbols.push_back({r, c});
        }
        r++;
        engine.push_back(line);
    }
    // find all numbers which are adjacent or diagonal with a symbol
    for (auto s : symbols) {
        FOR(i, 0, 7) {
            int x = s.first + dx[i];
            int y = s.second + dy[i];
            if (!isNumber(engine[x][y]))
                continue;
            components.push_back({x, y});
        }
    }
    //
    for (auto c : components) {
        // visited
        int number = 0;
        if (engine[c.first][c.second] == '.')
            continue;
        int i = c.second;
        int tenPower = 1;
        // ex: 467: start with 6
        // go left -> number = 4*10 + 6
        // go right -> number = 10*46 + 7 = 467

        // go left
        while (0 <= i && isNumber(engine[c.first][i])) {
            number += tenPower * (engine[c.first][i] - '0');
            engine[c.first][i] = '.';
            i--;
            tenPower *= 10;
            // mark as visited
        }
        i = c.second + 1;
        // go right
        while (i < engine[0].size() && isNumber(engine[c.first][i])) {
            number = number * 10 + engine[c.first][i] - '0';
            engine[c.first][i] = '.';
            i++;
        }
        ans += number;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    // O(n*m)  (n*m: size of engine)
    cout << solve() << '\n';
    fclose(stdin);

    return 0;
}
