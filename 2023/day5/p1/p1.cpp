#include <algorithm>
#include <bits/stdc++.h>
#include <string>

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
#define SQ(a) (a) * (a)

// balanced binary tree
// search log(n)
// insert log(n)
// delete log(n)
set<ll> seeds;

ll solve() {
    string l;
    // read seeds;
    getline(cin, l);
    int size = -1;
    int start = 0;
    l += ' ';
    while ((size = l.find(' ', start)) != string::npos) {
        string seed = l.substr(start, size - start);
        start = size + 1;
        if (seed == "seeds:")
            continue;
        seeds.insert(stoll(seed));
    }
    // read maps;
    int count = 0;
    ll F[3] = {0, 0, 0};
    vector<ll> newValue;
    while (cin >> l) {
        if (l.size() == 0 || l.find("map") != string::npos ||
            l.find("to") != string::npos) {
            for (auto v : newValue) {
                seeds.insert(v);
            }
            newValue.clear();
            continue;
        }

        // all maps are the same;
        // seed -> soil -> fertilizer -> water -> light -> temperature ->
        // humidity -> location -> you name it
        // read des src range
        F[count] = stoll(l);
        count = (count + 1) % 3;
        if (count == 0) {
            ll des = F[0];
            ll src = F[1];
            ll range = F[2];
            // log(n)
            auto begin = seeds.upper_bound(src - 1);
            // log(n)
            auto end = seeds.upper_bound(src + range - 1);
            // worst case O(n)
            vector<ll> needToUpdate;
            for (auto it = begin; it != end; it++) {
                needToUpdate.push_back(*it);
            }
            for (int i = 0; i < needToUpdate.size(); i++) {
                ll tmp = des + needToUpdate[i] - src;
                seeds.erase(needToUpdate[i]);
                newValue.push_back(tmp);
            }
        }
    }
    for (auto v : newValue) {
        seeds.insert(v);
    }
    return *seeds.begin();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    // O(m*n) -- n: number of seeds, m number of lines in input.txt
    cout << solve() << endl;
    fclose(stdin);

    return 0;
}
