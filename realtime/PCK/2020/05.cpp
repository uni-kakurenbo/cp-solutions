#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    valarray<string> p(n);
    for(auto& row : p) cin >> row;

    int cnt = 0;

    int q; cin >> q;
    for(int i=0; i<q; ++i) {
        int r; cin >> r;
        cnt -= r;
        cnt += 4;
        cnt %= 4;
    }

    // std::cout << cnt << "\n";

    for(int _=0; _<cnt; ++_) {
        valarray<string> q(string(n, '-'), n);

        for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) {
            q[n-j-1][i] = p[i][j];
        }

        p = move(q);
    }

    for(string& row : p) cout << row << "\n";
}
