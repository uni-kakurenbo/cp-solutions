#include <bits/stdc++.h>
using namespace std;

int MOD = 998244353;
struct static_modint {
    int v;

    static_modint(int a) : v(a % MOD) {
        cerr << "constructor\n";
        if(v < 0) v += MOD;
    }

    bool operator==(const static_modint& other) const {
        cerr << "member\n";
        return v == other.v;
    }

    friend bool operator==(int a, const static_modint& b) {
        cerr << "non-member\n";
        return b == a;
    }
};

void solve() {
    static_modint x(2);
    cerr << (x == 2) << "\n";
    cerr << (2 == x) << "\n";
}
