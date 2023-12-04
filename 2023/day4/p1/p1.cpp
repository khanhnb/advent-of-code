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
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORR(i, a, b) for (int i = a; i >= b; i--)

int solve() {
    string l;
    int ans = 0;
    while (getline(cin, l)) {
        l = l.substr(l.find(':') + 1) + ' ';
        int size;
        int start = 0;
        int numOfWinning = 0;
        bool isWinning = true;
        unordered_set<string> winning;
        while ((size = l.find(' ', start)) != string::npos) {
            string s = l.substr(start, size - start);
            start = size + 1;
            if (s.size() == 0)
                continue;
            if (s == "|") {
                isWinning = false;
                continue;
            }
            if (isWinning) {
                winning.insert(s);
            } else if (winning.find(s) != winning.end()) {
                numOfWinning++;
            }
        }
        ans += (numOfWinning == 0) ? 0 : 1 << (numOfWinning - 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    cout << solve() << '\n';
    fclose(stdin);

    return 0;
}
