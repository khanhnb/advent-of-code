#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool isNumber(char c) { return c >= '0' && c <= '9'; }

int solve() {
    string s;
    int sum = 0;
    while (cin >> s) {
        if (s.size() == 0) continue;
        int i = 0, j = s.size() - 1;
        while (i < s.size() && !isNumber(s[i]))
            i++;
        while (j >= 0 && !isNumber(s[j]))
            j--;
        sum += 10 * (s[i] - '0') + s[j] - '0';
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    cout << solve() << '\n';
    fclose(stdin);

    return 0;
}
