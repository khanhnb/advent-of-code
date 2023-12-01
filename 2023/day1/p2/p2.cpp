#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

typedef long long ll;

bool isNumber(string &s, int i) {
    switch (s[i]) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return true;
    case 'o':
        // one
        if (i + 2 < s.size() && s.compare(i, 3, "one") == 0) {
            s[i] = '1';
            return true;
        }
    case 't':
        // two
        if (i + 2 < s.size() && s.compare(i, 3, "two") == 0) {
            s[i] = '2';
            return true;
        }
        // three
        if (i + 4 < s.size() && s.compare(i, 5, "three") == 0) {
            s[i] = '3';
            return true;
        }
    case 'f':
        // four
        if (i + 3 < s.size() && s.compare(i, 4, "four") == 0) {
            s[i] = '4';
            return true;
        }
        // five
        if (i + 3 < s.size() && s.compare(i, 4, "five") == 0) {
            s[i] = '5';
            return true;
        }
    case 's':
        // six
        if (i + 2 < s.size() && s.compare(i, 3, "six") == 0) {
            s[i] = '6';
            return true;
        }
        // seven
        if (i + 4 < s.size() && s.compare(i, 5, "seven") == 0) {
            s[i] = '7';
            return true;
        }
    case 'e':
        // eight
        if (i + 4 < s.size() && s.compare(i, 5, "eight") == 0) {
            s[i] = '8';
            return true;
        }
    case 'n':
        // nine
        if (i + 3 < s.size() && s.compare(i, 4, "nine") == 0) {
            s[i] = '9';
            return true;
        }
    default:
        return false;
    }
}

int solve() {
    string s;
    int sum = 0;
    while (cin >> s) {
        if (s.size() == 0)
            continue;
        int i = 0, j = s.size() - 1;
        while (i < s.size() - 1 && !isNumber(s, i)) {
            i++;
        }
        while (j >= 0 && !isNumber(s, j))
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
