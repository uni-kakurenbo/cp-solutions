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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

signed main() {
    int n, q; cin >> n >> q;

    unordered_map<ll,int> parents;
    unordered_map<int,int> boxes(n);

    REP(i, n) {
        boxes[i] = -i;
        parents[i] = i;
    }

    ll cnt = n;
    LOOP(q) {
        int t; cin >> t;
        if(t == 1) {
            int x, y; cin >> x >> y; --x, --y;
            boxes[y] = boxes[x];
            boxes[y] = boxes.size() + 1;
        }
        if(t == 2) {
            int x; cin >> x; --x;
            parents[++cnt] = states[x];
        }
        if(t == 3) {
            int x; cin >> x; --x;
            auto merge = [&](auto &merge, int p) {
                if(states[p] == p) return p;
                return states[p] = merge(merge, states[p]);
            };
            print(boxes[merge(merge, parents[x])] + 1);
        }
    }
    return 0;
}
