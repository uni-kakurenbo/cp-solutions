/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
#include <bits/stdc++.h>

#include "template.hpp"
#include "output.hpp"

using namespace std;
Output print;

signed main() {
    int q; cin >> q;
    deque<int> a;

    bool rev = 0;
    LOOP(q) {
        int t; cin >> t;
        if (t == 1) {
            int x; cin >> x;
            if(rev) a.push_front(x);
            else a.push_back(x);
        }
        if (t == 2) {
            print(rev ? a.back() : a.front());
            if(rev) a.pop_back();
            else a.pop_front();
        }
        if (t == 3) {
            rev = not rev;
        }
    }

    return 0;
}
