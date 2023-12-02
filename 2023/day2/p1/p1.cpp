#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool isOk(string b) {
    int F[3] = {12, 13, 14};
    b += " ";
    string prev = "";
    int start = 0;
    int size;
    while ((size = b.find(' ', start)) != string::npos) {
        string w = b.substr(start, size - start);
        if (w.find("red") != string::npos) {
            F[0] -= stoi(prev);
            if (F[0] < 0)
                return false;
        } else if (w.find("green") != string::npos) {
            F[1] -= stoi(prev);
            if (F[1] < 0)
                return false;
        } else if (w.find("blue") != string::npos) {
            F[2] -= stoi(prev);
            if (F[2] < 0)
                return false;
        } else
            prev = w;
        start = size + 1;
    }
    return true;
}

int solve() {
    string l;
    int ans = 0;
    int gameId = 0;
    vector<string> s;
    while (getline(cin, l)) {
        int start = 0;
        int size;
        l += ';';
        bool ok = true;
        while ((size = l.find(';', start)) != string::npos) {
            if (!isOk(l.substr(start, size - start))) {
                ok = false;
                break;
            }
            start = size + 1;
        }
        gameId++;
        if (ok)
            ans += gameId;
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
