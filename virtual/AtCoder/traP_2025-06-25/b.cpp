/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
namespace rng = std::ranges;

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for (;;) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

// #include "template/warnings.hpp"
void solve() {
    int w, h;
    cin >> w >> h;
    if (w == 0 && h == 0) { exit(0); }
    vector<vector<int>> xl(w, vector<int>()), yl(h, vector<int>());
    for (int i=0; i<w+h-1; i++) {
        int x, y, n;
        cin >> x >> y >> n;
        x--; y--;
        xl[x].push_back(i);
        yl[y].push_back(i);
    }

    atcoder::dsu uf(h+w-1);
    for (const auto& v: xl) {
        if (v.size() == 0) { cout << "NO" << endl; return; }
        for (int i=1; i<(int)v.size(); i++) {
            uf.merge(v[i-1], v[i]);
        }
    }
    for (const auto& v: yl) {
        if (v.size() == 0) { cout << "NO" << endl; return; }
        for (int i=1; i<(int)v.size(); i++) {
            uf.merge(v[i-1], v[i]);
        }
    }


    if (xl[0].size() == 0) { cout << "NO" << endl; return; }
    int i = xl[0][0];
    if (uf.size(i) == w+h-1) { cout << "YES" << endl; } else { cout << "NO" << endl; }
}
