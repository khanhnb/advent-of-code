#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

// Macros
#define PB push_back
#define MP make_pair
#define SQ(a) (a) * (a)

vector<string> hands;
vector<int> bets;

struct player {
    int bet;
    vector<int> hand;
    int score;

    bool operator<(const player &rhs) const {
        if (score != rhs.score) {
            return score < rhs.score;
        } else {
            for (int i = 0; i < 5; i++) {
                if (hand[i] == rhs.hand[i])
                    continue;
                return hand[i] < rhs.hand[i];
            }
            return false;
        }
        return (score == rhs.score) ? hand < rhs.hand : score < rhs.score;
    }
};
vector<player> players;

ll solve() {
    // 1 2 3 4 5 6 7 8 9 T J Q K A
    for (int i = 0; i < hands.size(); ++i) {
        int F[14] = {};
        vector<int> hand;
        // count cards
        for (int j = 0; j < 5; j++) {
            switch (hands[i][j]) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                F[hands[i][j] - '1']++;
                hand.PB(hands[i][j] - '1');
                break;
            case 'T':
                F[9]++;
                hand.PB(9);
                break;
            case 'J':
                F[0]++;
                hand.PB(0);
                break;
            case 'Q':
                F[11]++;
                hand.PB(11);
                break;
            case 'K':
                F[12]++;
                hand.PB(12);
                break;
            case 'A':
                F[13]++;
                hand.PB(13);
            }
        }
        // N[i] number of cards has i occurrences
        int N[6] = {};
        // k != 0 : no need to count J
        for (int k = 13; k > 0; k--) {
            if (F[k] == 0)
                continue;
            N[F[k]]++;
        }
        vector<int> h;
        int score = 0;
        // 5   - 25
        // 4   - 17
        // 3 2 - 13
        // 3   - 11
        // 2 2 - 9
        // 2   - 7
        // 1   - 5

        bool hasJ = (F[0] != 0);

        // add J to card with maxOccurrences
        if (hasJ) {
            int maxOccurrences = 0;
            for(int k=5; k>0; --k) {
                if (N[k] == 0) continue;
                maxOccurrences = k;
                break;
            }
            N[maxOccurrences]--;
            N[F[0] + maxOccurrences]++;
        }
        for (int k = 5; k > 0; --k) {
            if (N[k] == 0)
                continue;
            score += SQ(k) * N[k];
        }
        players.PB({bets[i], hand, score});
    }
    sort(players.begin(), players.end());
    ll ans = 0;
    for (int i = 0; i < players.size(); i++) {
        ans += (i + 1) * players[i].bet;
    }

    return ans;
}

void parse() {
    freopen("input.txt", "r", stdin);
    string l;
    bool hand = true;
    while (cin >> l) {
        if (hand)
            hands.PB(l);
        else
            bets.PB(stoi(l));
        hand ^= 1;
    }
    fclose(stdin);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    parse();
    // O(nlogn)
    cout << solve() << endl;

    return 0;
}
