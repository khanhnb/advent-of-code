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
#define SQ(a) (a) * (a)

ll t, d;

ll solveEquation() {
    // 0 > x^2 - t*x + d
    double a = 1, b = -t, c = d, delta = SQ(b) - 4 * a * c;
    if (delta < 0)
        return 0;
    double x1 = (-b + sqrt(delta)) / (2 * a);
    double x2 = (-b - sqrt(delta)) / (2 * a);
    ll min = (x1 < x2) ? floor(x1) : floor(x2);
    ll max = (x1 < x2) ? ceil(x2) : ceil(x1);

    return max - min - 1;
}

int solve() { return solveEquation(); }
void readInput() {
    freopen("input.txt", "r", stdin);
    string l;
    ll *tmp;
    while (cin >> l) {
        if (l == "Time:") {
            tmp = &t;
            continue;
        }
        if (l == "Distance:") {
            tmp = &d;
            continue;
        }
        *tmp = *tmp * pow(10, l.size()) + stoi(l);
    }
    fclose(stdin);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    readInput();
    // O(n) - n: number of races
    cout << solve() << endl;

    return 0;
}
