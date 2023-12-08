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

string instructions;
unordered_map<string, pair<string, string>> m;

void parse() {
    freopen("input.txt", "r", stdin);
    string l;
    cin >> instructions;

    int count = 0;
    string nodes[3];
    while (cin >> l) {
        if (l == "=")
            continue;
        string node;
        for (int i = 0; i < l.size(); ++i) {
            if (l[i] == '(' || l[i] == ')' || l[i] == ',')
                continue;
            node += l[i];
        }
        nodes[count] = node;
        if (count == 2)
            m[nodes[0]] = {nodes[1], nodes[2]};
        count = (count + 1) % 3;
    }

    fclose(stdin);
}

int solve(string curr) {
    int i = 0;
    int loop = 0;
    do {
        curr = (instructions[i] == 'R') ? m[curr].S : m[curr].F;
        i = (i + 1) % instructions.size();
        if (i == 0)
            loop++;
    } while (curr[2] != 'Z');
    return loop;
}

ll solve() {
    vector<int> loops;
    for (auto node : m) {
        if (node.F[2] != 'A')
        // if (node.F[2] != 'Z')
            continue;
        loops.PB(solve(node.F));
    }
    ll ans = loops[0];
    for (int i = 1; i < loops.size(); i++) {
        ans = lcm(ans, loops[i]);
    }
    return ans * instructions.size();
}

// read this clue
// "You had the camel follow the instructions, but you've barely left your starting position"

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    parse();
    cout << solve() << '\n';

    return 0;
}
