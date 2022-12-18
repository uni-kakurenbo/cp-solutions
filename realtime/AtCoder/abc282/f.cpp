/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print(&std::cout, Output<>::sendl);
#define input _input
#define print _print
/* #endregion */

#include "iterable/inverse.hpp"

signed main() {
    int n; cin >> n;

    vector<pair<int,int>> vals;
    vector<pair<int,int>> inv(n);

    auto gen = [&](auto &gen, int l, int r) -> void {
        if(r - l <= 1) return;
        int mid = (l+r)/2;
        FOR(i, mid+1, r) {
            vals.emplace_back(mid, i);
            inv[mid].emplace_back(i, vals.size());
        }
        FORD(i, mid-1, l) {
            vals.emplace_back(i, mid);
            inv[i].emplace_back(mid, vals.size());
        }
        gen(gen, l, mid), gen(gen, mid, r);
    };


    gen(gen, 1, n);

    print(vals.size());
    ITR(p, vals) { print(p); }

    int q; cin >> q;

    LOOP(q) {
        int l, r; cin >> l >> r;
        auto b = lower_bound(ALL(inv[l]), r);
        if(b == inv[l].end()) {
            auto c = lower_bound(*b, r);
            print(b->second, c->second);
            continue;
        }
        print(b->second, *b);
    }

    return 0;
}
