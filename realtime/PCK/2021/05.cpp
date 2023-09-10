#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); ++i)

constexpr int seg[] = {
    0b1110111,
    0b0100100,
    0b1011101,
    0b1101101,
    0b0101110,
    0b1101011,
    0b1111011,
    0b0100111,
    0b1111111,
    0b1101111
};

int main() {
    int h0, m0, h1, m1; cin >> h0 >> m0 >> h1 >> m1;

    int ans = 0;

    while(not (h0 == h1 and m0 == m1)) {
        ans += seg[h0 / 10] ^ seg[]

        m0++;
        if(m0 >= 60) h0++, m0 = 0;
    }
}
