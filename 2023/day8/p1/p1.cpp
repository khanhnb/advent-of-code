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

int solve() {
    int ans = 0;
    string curr = "AAA";
    int i = 0;
    while (curr != "ZZZ") {
        char instruction = instructions[i];
        curr = (instruction == 'R') ? m[curr].S : m[curr].F;
        i = (i + 1) % instructions.size();
        ans++;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    parse();
    cout << solve() << '\n';

    return 0;
}
