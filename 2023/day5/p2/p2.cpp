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

struct seed {
    ll start;
    ll end;
    bool valid;
};

vector<seed> seeds;

ll solve() {
    string l;
    // read seeds;
    bool isRange = false;
    ll S[2];
    while (cin >> l) {
        if (l.find("soil") != string::npos)
            break;
        if (l == "seeds:")
            continue;
        S[isRange] = stoll(l);
        if (isRange) {
            seeds.push_back({S[0], S[0] + S[1] - 1, true});
        }
        isRange ^= 1;
    }
    // read maps;
    int count = 0;
    ll F[3] = {0, 0, 0};
    vector<seed> newSeeds;
    while (cin >> l) {
        if (l.size() == 0 || l.find("map") != string::npos ||
            l.find("to") != string::npos) {
            for (auto s : newSeeds)
                seeds.push_back(s);
            newSeeds.clear();
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
            vector<seed> leftOvers;
            for (int i = 0; i < seeds.size(); ++i) {
                if (!seeds[i].valid || src > seeds[i].end ||
                    src + range - 1 < seeds[i].start)
                    continue;
                seeds[i].valid = false;
                pair<ll, ll> overlap;
                overlap.first = (src < seeds[i].start) ? seeds[i].start : src;
                overlap.second = (src + range - 1 < seeds[i].end)
                                     ? src + range - 1
                                     : seeds[i].end;
                if (seeds[i].start <= overlap.first - 1) {
                    leftOvers.push_back(
                        {seeds[i].start, overlap.first - 1, true});
                }
                if (seeds[i].end >= overlap.second + 1) {
                    leftOvers.push_back(
                        {overlap.second + 1, seeds[i].end, true});
                }
                newSeeds.push_back({overlap.first - src + des,
                                    overlap.second - src + des, true});
            }
            for (auto lo : leftOvers)
                seeds.push_back(lo);
        }
    }
    for (auto s : newSeeds)
        seeds.push_back(s);
    ll ans = seeds[0].start;
    for (auto s : seeds) {
        if (!s.valid)
            continue;
        ans = (ans < s.start) ? ans : s.start;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    // O(m*n) -- n: number range of seeds, m number of lines in input.txt
    cout << solve() << endl;
    fclose(stdin);

    return 0;
}
