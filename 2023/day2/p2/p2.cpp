#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int power(string b) {
    int F[3] = {1, 1, 1};
    vector<string> s;
    int start = 0;
    int size;
    b += ' ';
    while ((size = b.find(' ', start)) != string::npos) {
        string w = b.substr(start, size - start);
        if (w.find("red") != string::npos) {
            F[0] = max(F[0], stoi(s.back()));
        } else if (w.find("green") != string::npos) {
            F[1] = max(F[1], stoi(s.back()));
        } else if (w.find("blue") != string::npos) {
            F[2] = max(F[2], stoi(s.back()));
        } else
            s.push_back(w);
        start = size + 1;
    }
    return F[0] * F[1] * F[2];
}

int solve() {
    string l;
    int ans = 0;
    while (getline(cin, l)) {
        ans += power(l);
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

